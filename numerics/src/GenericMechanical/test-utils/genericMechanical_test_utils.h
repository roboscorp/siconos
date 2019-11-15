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
#ifndef GENERICMECHANICAL_TEST_UTILS_H
#define GENERICMECHANICAL_TEST_UTILS_H

#include "SiconosConfig.h" // for BUILD_AS_CPP
#include <stdio.h>
#include "test_utils.h"

#if defined(__cplusplus) && !defined(BUILD_AS_CPP)
extern "C"
{
#endif

  TestCase * build_test_collection(int n_data, const char ** data_collection, int*);
  
  int gmp_test_function(TestCase*);

#if defined(__cplusplus) && !defined(BUILD_AS_CPP)
}
#endif

#endif


