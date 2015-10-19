/* Siconos-sample , Copyright INRIA 2005-2011.
 * Siconos is a program dedicated to modeling, simulation and control
 * of non smooth dynamical systems.
 * Siconos is a free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * Siconos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Siconos; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Contact: Vincent ACARY vincent.acary@inrialpes.fr
 */

/*!\file NE....cpp
  \brief \ref EMNE_MULTIBODY - C++ input file, Time-Stepping version - O.B.

  A multibody example.
  Direct description of the model.
  Simulation with a Time-Stepping scheme.
*/

#include "SiconosKernel.hpp"
#include "KneeJointR.hpp"
#include "PrismaticJointR.hpp"
#include <boost/math/quaternion.hpp>
using namespace std;

/* Given a position of a point in the Inertial Frame and the configuration vector q of a solid
 * returns a position in the spatial frame.
 */
void fromInertialToSpatialFrame(double *positionInInertialFrame, double *positionInSpatialFrame, SP::SiconosVector  q  )
{
double q0 = q->getValue(3);
double q1 = q->getValue(4);
double q2 = q->getValue(5);
double q3 = q->getValue(6);

::boost::math::quaternion<double>    quatQ(q0, q1, q2, q3);
::boost::math::quaternion<double>    quatcQ(q0, -q1, -q2, -q3);
::boost::math::quaternion<double>    quatpos(0, positionInInertialFrame[0], positionInInertialFrame[1], positionInInertialFrame[2]);
::boost::math::quaternion<double>    quatBuff;

//perform the rotation
quatBuff = quatQ * quatpos * quatcQ;

positionInSpatialFrame[0] = quatBuff.R_component_2()+q->getValue(0);
positionInSpatialFrame[1] = quatBuff.R_component_3()+q->getValue(1);
positionInSpatialFrame[2] = quatBuff.R_component_4()+q->getValue(2);

}
void tipTrajectories(SP::SiconosVector  q, double * traj, double length)
{
  double positionInInertialFrame[3];
  double positionInSpatialFrame[3];
  // Output the position of the tip of beam1
  positionInInertialFrame[0]=length/2;
  positionInInertialFrame[1]=0.0;
  positionInInertialFrame[2]=0.0;

  fromInertialToSpatialFrame(positionInInertialFrame, positionInSpatialFrame, q  );
  traj[0] = positionInSpatialFrame[0];
  traj[1] = positionInSpatialFrame[1];
  traj[2] = positionInSpatialFrame[2];


  // std::cout <<  "positionInSpatialFrame[0]" <<  positionInSpatialFrame[0]<<std::endl;
  // std::cout <<  "positionInSpatialFrame[1]" <<  positionInSpatialFrame[1]<<std::endl;
  // std::cout <<  "positionInSpatialFrame[2]" <<  positionInSpatialFrame[2]<<std::endl;

  positionInInertialFrame[0]=-length/2;
  fromInertialToSpatialFrame(positionInInertialFrame, positionInSpatialFrame, q  );
  traj[3]= positionInSpatialFrame[0];
  traj[4] = positionInSpatialFrame[1];
  traj[5] = positionInSpatialFrame[2];
}





int main(int argc, char* argv[])
{
  try
  {


    // ================= Creation of the model =======================

    // User-defined main parameters
    unsigned int nDof = 3;
    unsigned int qDim = 7;
    unsigned int nDim = 6;
    double t0 = 0;                   // initial computation time
    double T = 10.0;                  // final computation time
    double h = 0.01;                // time step
    int N = 1000;
    double L1 = 1.0;
    double theta = 1.0;              // theta for MoreauJeanOSI integrator
    double g = 9.81; // Gravity
    double m = 1.;

    // -------------------------
    // --- Dynamical systems ---
    // -------------------------

    FILE * pFile;
    pFile = fopen("data.h", "w");
    if (pFile == NULL)
    {
      printf("fopen exampleopen filed!\n");
      fclose(pFile);
    }


    cout << "====> Model loading ..." << endl << endl;

    // -- Initial positions and velocities --

    //First DS
    SP::SiconosVector q10(new SiconosVector(qDim));
    SP::SiconosVector v10(new SiconosVector(nDim));
    SP::SimpleMatrix I1(new SimpleMatrix(3, 3));
    v10->zero();
    (*v10)(0)=1000;
    I1->eye();
    I1->setValue(0, 0, 0.1);
    I1->setValue(0, 1, 0.1);
    I1->setValue(1, 0, 0.1);
    // Initial position of the center of gravity CG1
    (*q10)(0) = 0.5 * L1 / sqrt(2.0);
    (*q10)(1) = 0;
    (*q10)(2) = -0.5 * L1 / sqrt(2.0);
    // Initial orientation (a quaternion that gives the rotation w.r.t the spatial frame)
    // angle of the rotation Pi/4
    double angle = M_PI / 4;
    SiconosVector V1(3);
    V1.zero();
    // vector of the rotation (Y-axis)
    V1.setValue(0, 0);
    V1.setValue(1, 1);
    V1.setValue(2, 0);
    // construction of the quaternion
    q10->setValue(3, cos(angle / 2));
    q10->setValue(4, V1.getValue(0)*sin(angle / 2));
    q10->setValue(5, V1.getValue(1)*sin(angle / 2));
    q10->setValue(6, V1.getValue(2)*sin(angle / 2));

    // -- The dynamical system --
    SP::NewtonEulerDS beam1(new NewtonEulerDS(q10, v10, m, I1));
    // -- Set external forces (weight) --
    SP::SiconosVector weight(new SiconosVector(nDof));
    (*weight)(2) = -m * g;
    beam1->setFExtPtr(weight);

    // --------------------
    // --- Interactions ---
    // --------------------
    SP::NonSmoothLaw nslaw1(new EqualityConditionNSL(KneeJointR::numberOfConstraints()));

    SP::SiconosVector P(new SiconosVector(3));
    P->zero();
    // Building the first knee joint for beam1
    // input  - the concerned DS : beam1
    //        - a point in the spatial frame (absolute frame) where the knee is defined P
    SP::NewtonEulerR relation1(new KneeJointR(beam1, P));

    SP::Interaction inter1(new Interaction(KneeJointR::numberOfConstraints(), nslaw1, relation1));

    // -------------
    // --- Model ---
    // -------------
    SP::Model myModel(new Model(t0, T));
    // add the dynamical system in the non smooth dynamical system
    myModel->nonSmoothDynamicalSystem()->insertDynamicalSystem(beam1);
    // link the interaction and the dynamical system
    myModel->nonSmoothDynamicalSystem()->link(inter1, beam1);
    // ------------------
    // --- Simulation ---
    // ------------------

    // -- (1) OneStepIntegrators --
    SP::MoreauJeanOSI OSI1(new MoreauJeanOSI(theta));
    OSI1->insertDynamicalSystem(beam1);

    // -- (2) Time discretisation --
    SP::TimeDiscretisation t(new TimeDiscretisation(t0, h));

    // -- (3) one step non smooth problem
    SP::OneStepNSProblem impact(new MLCP());

    // -- (4) Simulation setup with (1) (2) (3)
    SP::TimeStepping s(new TimeStepping(t));
    s->insertIntegrator(OSI1);
    s->insertNonSmoothProblem(impact, SICONOS_OSNSP_TS_VELOCITY);



    // =========================== End of model definition ===========================

    // ================================= Computation =================================

    // --- Simulation initialization ---

    cout << "====> Initialisation ..." << endl << endl;
    myModel->initialize(s);


    // --- Get the values to be plotted ---
    // -> saved in a matrix dataPlot
    unsigned int outputSize = 15 + 7;
    SimpleMatrix dataPlot(N, outputSize);
    SimpleMatrix beam1Plot(2,3*N);

    SP::SiconosVector q1 = beam1->q();
    SP::SiconosVector y= inter1->y(0);
    SP::SiconosVector ydot= inter1->y(1);


    // --- Time loop ---
    cout << "====> Start computation ... " << endl << endl;
    // ==== Simulation loop - Writing without explicit event handling =====
    int k = 0;
    boost::progress_display show_progress(N);

    boost::timer time;
    time.restart();
    SP::SiconosVector yAux(new SiconosVector(3));
    yAux->setValue(0, 1);
    SP::SimpleMatrix Jaux(new SimpleMatrix(3, 3));
    Index dimIndex(2);
    Index startIndex(4);
    fprintf(pFile, "double T[%d*%d]={", N + 1, outputSize);
    double beamTipTrajectories[6];

    for (k = 0; k < N; k++)
    {
      // solve ...
      //s->newtonSolve(1e-4, 50);

      s->advanceToEvent();
      // --- Get values to be plotted ---
      dataPlot(k, 0) =  s->nextTime();

      dataPlot(k, 1) = (*q1)(0);
      dataPlot(k, 2) = (*q1)(1);
      dataPlot(k, 3) = (*q1)(2);
      dataPlot(k, 4) = (*q1)(3);
      dataPlot(k, 5) = (*q1)(4);
      dataPlot(k, 6) = (*q1)(5);
      dataPlot(k, 7) = (*q1)(6);
      dataPlot(k, 8) = y->norm2();
      dataPlot(k, 9) = ydot->norm2();


      tipTrajectories(q1,beamTipTrajectories,L1);
      beam1Plot(0,3*k) = beamTipTrajectories[0];
      beam1Plot(0,3*k+1) = beamTipTrajectories[1];
      beam1Plot(0,3*k+2) = beamTipTrajectories[2];
      beam1Plot(1,3*k) = beamTipTrajectories[3];
      beam1Plot(1,3*k+1) = beamTipTrajectories[4];
      beam1Plot(1,3*k+2) = beamTipTrajectories[5];


      for (unsigned int jj = 0; jj < outputSize; jj++)
      {
        if ((k || jj))
          fprintf(pFile, ",");
        fprintf(pFile, "%f", dataPlot(k, jj));
      }
      fprintf(pFile, "\n");
      // s->nextStep();
      s->processEvents();
      ++show_progress;
    }
    fprintf(pFile, "};");
    cout << endl << "End of computation - Number of iterations done: " << k - 1 << endl;
    cout << "Computation Time " << time.elapsed()  << endl;

    // --- Output files ---
    cout << "====> Output file writing ..." << endl;
    ioMatrix::write("NE_1DS_1Knee_MLCP.dat", "ascii", dataPlot, "noDim");
    ioMatrix::write("NE_1DS_1Knee_MLCP_beam1.dat", "ascii", beam1Plot, "noDim");

    // SimpleMatrix dataPlotRef(dataPlot);
    // dataPlotRef.zero();
    // ioMatrix::read("NE_1DS_1Knee_1Prism_MLCP.ref", "ascii", dataPlotRef);
    // if ((dataPlot - dataPlotRef).normInf() > 1e-7)
    // {
    //   (dataPlot - dataPlotRef).display();
    //   std::cout << "Warning. The results is rather different from the reference file." << std::endl;
    //   return 1;
    // }

    fclose(pFile);
  }

  catch (SiconosException e)
  {
    cout << e.report() << endl;
  }
  catch (...)
  {
    cout << "Exception caught in NE_...cpp" << endl;
  }

}