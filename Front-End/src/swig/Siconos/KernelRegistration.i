// Warning: 
// You have to PY_REGISTER base classe before derivated classes
#undef PY_REGISTER
#define KERNEL_REGISTRATION()                                           \
  PY_REGISTER_WITHOUT_DIRECTOR(SiconosMatrix);                          \
  PY_REGISTER_WITHOUT_DIRECTOR(SimpleMatrix);                           \
  PY_REGISTER_WITHOUT_DIRECTOR(SiconosVector);                          \
  PY_REGISTER_WITHOUT_DIRECTOR(BlockVector);                            \
  PY_REGISTER(NonSmoothLaw);                                            \
  PY_REGISTER(NewtonImpactNSL);                                         \
  PY_REGISTER(NewtonImpactFrictionNSL);                                 \
  PY_REGISTER(MixedComplementarityConditionNSL);                        \
  PY_REGISTER(ComplementarityConditionNSL);                             \
  PY_REGISTER(EqualityConditionNSL);                                    \
  PY_REGISTER(MultipleImpactNSL);                                       \
  PY_REGISTER(RelayNSL);                                                \
  PY_REGISTER(DynamicalSystem);                                         \
  PY_REGISTER(NonSmoothDynamicalSystem);                                \
  PY_REGISTER(Topology);                                                \
  PY_REGISTER(LagrangianDS);                                            \
  PY_REGISTER(LagrangianLinearTIDS);                                    \
  PY_REGISTER(NewtonEulerDS);                                           \
  PY_REGISTER(FirstOrderNonLinearDS);                                   \
  PY_REGISTER(FirstOrderLinearDS);                                      \
  PY_REGISTER(FirstOrderLinearTIDS);                                    \
  PY_REGISTER(Relation);                                                \
  PY_REGISTER(LagrangianR);                                             \
  PY_REGISTER(LagrangianLinearTIR);                                     \
  PY_REGISTER(LagrangianRheonomousR);                                   \
  PY_REGISTER(LagrangianScleronomousR);                                 \
  PY_REGISTER(LagrangianCompliantR);                                    \
  PY_REGISTER(NewtonEulerR);                                            \
  PY_REGISTER(NewtonEulerFrom1DLocalFrameR);                            \
  PY_REGISTER(NewtonEulerFrom3DLocalFrameR);                            \
  PY_REGISTER(FirstOrderR);                                             \
  PY_REGISTER(FirstOrderLinearR);                                       \
  PY_REGISTER(FirstOrderLinearTIR);                                     \
  PY_REGISTER(FirstOrderType1R);                                        \
  PY_REGISTER(FirstOrderType2R);                                        \
  PY_REGISTER_WITHOUT_DIRECTOR(Actuator)                                \
  PY_REGISTER_WITHOUT_DIRECTOR(Sensor)                                  \
  PY_REGISTER(ControlSensor)                                            \
  PY_REGISTER(LinearSensor)                                             \
  PY_REGISTER(SampledPIDActuator)                                       \
  PY_REGISTER(CommonSMC)                                                \
  PY_REGISTER(LinearSMC)                                                \
  PY_REGISTER(LinearChatteringSMC)                                      \
  PY_REGISTER(LinearSMCOT2)                                             \
  PY_REGISTER(LinearSMCimproved)                                        \
  PY_REGISTER(ControlManager)                                           \
  PY_REGISTER(ControlDynamicalSystem)                                   \
  PY_REGISTER(ControlFirstOrderLinearDS)                                \
  PY_REGISTER(Interaction);                                             \
  PY_REGISTER(TimeDiscretisation);                                      \
  PY_REGISTER(OneStepNSProblem);                                        \
  PY_REGISTER(OneStepIntegrator);                                       \
  PY_REGISTER(LinearOSNS);                                              \
  PY_REGISTER(Lsodar);                                                  \
  PY_REGISTER(LCP);                                                     \
  PY_REGISTER(QP);                                                      \
  PY_REGISTER(Relay);                                                   \
  PY_REGISTER(MLCP);                                                    \
  PY_REGISTER(MLCPProjectOnConstraints);                                \
  PY_REGISTER(FrictionContact);                                         \
  PY_REGISTER(Moreau);                                                  \
  PY_REGISTER(ZeroOrderHold);                                           \
  PY_REGISTER(Simulation);                                              \
  PY_REGISTER(TimeStepping);                                            \
  PY_REGISTER(EventDriven);                                             \
  PY_REGISTER(EventsManager);                                           \
  PY_REGISTER(Event);                                                   \
  PY_REGISTER(Model);                                                   \
  PY_REGISTER(InteractionsSet);                                         \
  PY_REGISTER(BoundaryCondition);                                       \
  PY_REGISTER_SICONOS_MECHANICS_MAYBE();                                \
  PY_REGISTER_BULLET_MAYBE();

#ifdef HAVE_SICONOS_MECHANICS
#define PY_REGISTER_SICONOS_MECHANICS_MAYBE()                           \
  PY_REGISTER(KneeJointR)                                               \
  PY_REGISTER(PivotJointR)                                              \
  PY_REGISTER(PrismaticJointR)                                          \
  PY_REGISTER(CircularDS);                                              \
  PY_REGISTER(Disk);                                                    \
  PY_REGISTER(Circle);                                                  \
  PY_REGISTER(ExternalBody);                                            \
  PY_REGISTER(CircularR);                                               \
  PY_REGISTER(DiskDiskR);                                               \
  PY_REGISTER(DiskPlanR);                                               \
  PY_REGISTER(DiskMovingPlanR);                                         \
  PY_REGISTER(SphereLDS);                                               \
  PY_REGISTER(SphereNEDS);                                              \
  PY_REGISTER(SphereLDSPlanR);                                          \
  PY_REGISTER(SphereNEDSPlanR);                                         \
  PY_REGISTER(SphereLDSSphereLDSR);                                     \
  PY_REGISTER(SphereNEDSSphereNEDSR);                                   \
  PY_REGISTER(SiconosBodies);                                           \
  PY_REGISTER(SpaceFilter);                                             
#endif

#ifdef WITH_BULLET
#define PY_REGISTER_BULLET_MAYBE()                                      \
  PY_REGISTER(BulletR);                                                 \
  PY_REGISTER(BulletDS);                                                \
  PY_REGISTER(BulletSpaceFilter);                                       \
  PY_REGISTER(BulletTimeStepping);                                      \
  PY_REGISTER(BulletTimeSteppingProjectOnConstraints);                  \
  PY_REGISTER(BulletWeightedShape);                                     \
  PY_REGISTER(BulletFrom1DLocalFrameR);                                 \
  PY_REGISTER_BULLET_LINEAR_MATH(btVector3)                             \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btCollisionShape)              \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btCollisionMargin)             \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btConvexShape)                 \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btConvexInternalShape)         \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btConvex2dShape)               \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btConvexPointCloudShape)       \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btConvexHullShape)             \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btConvexPolyhedron)            \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btConvexTriangleMeshShape)     \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btPolyhedralConvexShape)       \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btConcaveShape)                \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btEmptyShape)                  \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btCompoundShape)               \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btTriangleShape)               \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btTriangleMesh)                \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btTriangleMeshShape)           \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btBox2dShape)                  \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btBoxShape)                    \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btCapsuleShape)                \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btConeShape)                   \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btCylinderShape)               \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btHeightfieldTerrainShape)     \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btMaterial)                    \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btMinkowskiSumShape)           \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btSphereShape)                 \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btMultiSphereShape)            \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btMultimaterialTriangleMeshShape) \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btOptimizedBvh)                \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btScaledBvhTriangleMeshShape)  \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btShapeHull)                   \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btStaticPlaneShape)            \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btStridingMeshInterface)       \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btTetrahedronShape)            \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btTriangleBuffer)              \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btTriangleCallback)            \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btTriangleIndexVertexArray)    \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btTriangleIndexVertexMaterialArray) \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btTriangleInfoMap)             \
  PY_REGISTER_BULLET_COLLISION_DETECTION(btUniformScalingShape)
#else
#define PY_REGISTER_BULLET_MAYBE()
#endif
