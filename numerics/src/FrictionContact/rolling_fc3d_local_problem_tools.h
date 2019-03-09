/* Siconos is a program dedicated to modeling, simulation and control
 * of non smooth dynamical systems.
 *
 * Copyright 2018 INRIA.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/
#ifndef ROLLINGFRICTIONCONTACT3D_local_problem_tools_H
#define ROLLINGFRICTIONCONTACT3D_local_problem_tools_H

/*!\file

 */
#include "FrictionContactProblem.h"

#if defined(__cplusplus) && !defined(BUILD_AS_CPP)
extern "C"
{
#endif
  FrictionContactProblem* rolling_fc3d_local_problem_allocate(FrictionContactProblem* problem);
  void rolling_fc3d_local_problem_free(FrictionContactProblem* localproblem,
                               FrictionContactProblem* problem);
  void rolling_fc3d_local_problem_compute_q(FrictionContactProblem * problem, FrictionContactProblem * localproblem, double *reaction, int contact);
  void rolling_fc3d_local_problem_fill_M(FrictionContactProblem * problem, FrictionContactProblem * localproblem, int contact);


#if defined(__cplusplus) && !defined(BUILD_AS_CPP)
}
#endif

#endif