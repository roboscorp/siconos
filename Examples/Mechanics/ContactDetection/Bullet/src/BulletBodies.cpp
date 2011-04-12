#include "BulletBodies.hpp"
#include <BulletSpaceFilter.hpp>
#include <BulletTimeStepping.hpp>
#include <BulletDS.hpp>

#define NDOF 3

void BulletBodies::init()
{
  SP::TimeDiscretisation timedisc;
  SP::BulletTimeStepping simulation;
  SP::FrictionContact osnspb;

  // User-defined main parameters


  double t0 = 0;                   // initial computation time

  double T = 0.02;

  double h = 0.01;                // time step


  // -----------------------------------------
  // --- Dynamical systems && interactions ---
  // -----------------------------------------

  try
  {

    // ------------
    // --- Init ---
    // ------------

    std::cout << "====> Model loading ..." << std::endl << std::endl;


    SP::SimpleVector shapeParams(new SimpleVector(3));
    (*shapeParams)(0) = 4.;
    (*shapeParams)(1) = 2;
    (*shapeParams)(2) = 7.;

    double theta = acos(1 / sqrt(3)) + 0.10;

    double a = 1;
    double b = 1;
    double c = 0;
    double k = (sin(theta / 2)) / sqrt(a * a + b * b + c * c);

    SP::SimpleVector position(new SimpleVector(7));
    SP::SimpleVector velocity(new SimpleVector(6));
    position->zero();
    (*position)(1) = 0.;
    (*position)(2) = 20.;
    (*position)(3) = cos(theta / 2);
    (*position)(4) = a * k;
    (*position)(5) = b * k;
    (*position)(6) = c * k;

    velocity->zero();
    (*velocity)(3) = 0.;
    (*velocity)(4) = 0.;
    (*velocity)(5) = 0.;

    SP::BulletDS body(new BulletDS(BOX_SHAPE_PROXYTYPE, shapeParams, position, velocity, 1.0));
    SP::SimpleVector FExt;
    FExt.reset(new SimpleVector(6)); //
    FExt->zero();
    FExt->setValue(2, -9.81);
    body->setFExtPtr(FExt);

    /* a second body : not yet
        SP::SimpleVector shapeParams2(new SimpleVector(3));
        (*shapeParams2)(0)=4.;
        (*shapeParams2)(1)=2;
        (*shapeParams2)(2)=7.;

        double theta2 = acos(1/sqrt(3))+0.10;

        double a2 = 1;
        double b2 = 1;
        double c2 = 0;
        double k2 = (sin(theta2/2))/sqrt(a2*a2+b2*b2+c2*c2);

        SP::SimpleVector position2(new SimpleVector(7));
        SP::SimpleVector velocity2(new SimpleVector(6));
        position2->zero();
        (*position2)(1) =10.;
        (*position2)(2) = 40.;
        (*position2)(3) =cos(theta2/2);
        (*position2)(4) =a2*k2;
        (*position2)(5) =b2*k2;
        (*position2)(6) =c2*k2;

        velocity2->zero();
        (*velocity2)(3) = 0.;
        (*velocity2)(4) = 0.;
        (*velocity2)(5) = 0.;

        SP::BulletDS body2(new BulletDS(BOX_SHAPE_PROXYTYPE, shapeParams2, position2, velocity2, 1.0));
        body2->setFExtPtr(FExt);
    */

    SP::btCollisionObject ground(new btCollisionObject());
    SP::btCollisionShape groundShape(new btBoxShape(btVector3(50, 50, 3)));
    btMatrix3x3 basis;
    basis.setIdentity();
    ground->getWorldTransform().setBasis(basis);
    ground->setCollisionShape(&*groundShape);

    ground->getWorldTransform().getOrigin().setZ(-3);

    // -------------
    // --- Model ---
    // -------------
    _model.reset(new Model(t0, T));

    // -- OneStepIntegrators --
    SP::OneStepIntegrator osi;
    osi.reset(new Moreau(0.5));


    _model->nonSmoothDynamicalSystem()->insertDynamicalSystem(body);
    //    _model->nonSmoothDynamicalSystem()->insertDynamicalSystem(body2);

    osi->insertDynamicalSystem(body);
    //    osi->insertDynamicalSystem(body2);


    // ------------------
    // --- Simulation ---
    // ------------------

    // -- Time discretisation --
    timedisc.reset(new TimeDiscretisation(t0, h));

    simulation.reset(new BulletTimeStepping(timedisc));

    osnspb.reset(new FrictionContact(3));

    osnspb->numericsSolverOptions()->iparam[0] = 1000; // Max number of
    // iterations
    osnspb->numericsSolverOptions()->iparam[1] = 20; // compute error
    // iterations
    osnspb->numericsSolverOptions()->dparam[0] = 1e-7; // Tolerance

    osnspb->setMaxSize(16384);
    osnspb->setMStorageType(1);
    osnspb->setNumericsVerboseMode(0);
    osnspb->setKeepLambdaAndYState(true);
    simulation->insertIntegrator(osi);
    simulation->insertNonSmoothProblem(osnspb);

    //simulation_->setCheckSolverFunction(localCheckSolverOuput);

    // --- Simulation initialization ---

    std::cout << "====> Simulation initialisation ..." << std::endl << std::endl;

    SP::NonSmoothLaw nslaw(new NewtonImpactFrictionNSL(0, 0, 0, 3));

    _playground.reset(new BulletSpaceFilter(_model->nonSmoothDynamicalSystem(),
                                            nslaw));

    ask<ForCollisionWorld>(*_playground)->addCollisionObject(&*ground);

    ask<ForStaticObjects>(*_playground)->push_back(ground);

    ask<ForStaticShapes>(*_playground)->push_back(groundShape);

    SP::DynamicalSystemsGraph dsGraph = model()->nonSmoothDynamicalSystem()->dynamicalSystems();

    _model->initialize(simulation);

    simulation->updateWorldFromDS();
    _playground->buildInteractions(_model->currentTime());

    std::cout << "====> End of initialisation ..." << std::endl << std::endl;

  }

  catch (SiconosException e)
  {
    std::cout << e.report() << std::endl;
    exit(1);
  }
  catch (...)
  {
    std::cout << "Exception caught in BulletBodies::init()" << std::endl;
    exit(1);
  }

}

