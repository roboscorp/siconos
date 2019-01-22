/* Siconos is a program dedicated to modeling, simulation and control
 * of non smooth dynamical systems.
 *
 * Copyright 2016 INRIA.
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

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
char *** test_collection(int, char **);

char *** test_collection(int n_data_1, char ** data_collection_1)
{
  int n_test=200;
  int n_entry = 50;
  char *** test_nsn = (char ***)malloc(n_test*sizeof(char **));

  for (int n =0 ; n <n_test ; n++)
  {
    test_nsn[n] = (char **)malloc(n_entry*sizeof(char *));
  }

  int n =0;
  int d= 7;

  int e=0;
  test_nsn[n][e++] = data_collection_1[d];
  test_nsn[n][e++] = "0";
  test_nsn[n][e] = (char *)malloc(50*sizeof(char));
  sprintf(test_nsn[n][e++], "%d", SICONOS_FRICTION_3D_NSN_AC);
  test_nsn[n][e++] = "5e-2";
  test_nsn[n][e++] = "1000";
  test_nsn[n][e++] = "---";
  n++;

  e=0;
  test_nsn[n][e++] = data_collection_1[d];
  test_nsn[n][e++] = "1";
  test_nsn[n][e] = (char *)malloc(50*sizeof(char));
  sprintf(test_nsn[n][e++], "%d", SICONOS_FRICTION_3D_NSN_AC_TEST);
  test_nsn[n][e++] = "5e-2";
  test_nsn[n][e++] = "1000";
  test_nsn[n][e++] = "---";
  n++;

  e=0;
  test_nsn[n][e++] = data_collection_1[d];
  test_nsn[n][e++] = "0";
  test_nsn[n][e] = (char *)malloc(50*sizeof(char));
  sprintf(test_nsn[n][e++], "%d", SICONOS_FRICTION_3D_NSN_FB);
  test_nsn[n][e++] = "5e-2";
  test_nsn[n][e++] = "1000";
  test_nsn[n][e++] = "---";
  n++;

  e=0;
  test_nsn[n][e++] = data_collection_1[d];
  test_nsn[n][e++] = "0";
  test_nsn[n][e] = (char *)malloc(50*sizeof(char));
  sprintf(test_nsn[n][e++], "%d", SICONOS_FRICTION_3D_NSN_NM);
  test_nsn[n][e++] = "5e-2";
  test_nsn[n][e++] = "1000";
  test_nsn[n][e++] = "---";
  n++;

  d=8;
  e=0;
  test_nsn[n][e++] = data_collection_1[d];
  test_nsn[n][e++] = "0";
  test_nsn[n][e] = (char *)malloc(50*sizeof(char));
  sprintf(test_nsn[n][e++], "%d", SICONOS_FRICTION_3D_NSN_AC);
  test_nsn[n][e++] = "1e-5";
  test_nsn[n][e++] = "100";
  test_nsn[n][e++] = "0";
  test_nsn[n][e++] = "0";
  test_nsn[n][e++] = "0";
  test_nsn[n][e++] = "iparam";
  test_nsn[n][e++] = "1";
  test_nsn[n][e++] = "1";
  
  e=0;
  test_nsn[n][e++] = data_collection_1[d];
  test_nsn[n][e++] = "1";
  test_nsn[n][e] = (char *)malloc(50*sizeof(char));
  sprintf(test_nsn[n][e++], "%d", SICONOS_FRICTION_3D_NSN_AC_TEST);
  test_nsn[n][e++] = "1e-5";
  test_nsn[n][e++] = "100";
  test_nsn[n][e++] = "0";
  test_nsn[n][e++] = "0";
  test_nsn[n][e++] = "0";
  test_nsn[n][e++] = "iparam";
  test_nsn[n][e++] = "1";
  test_nsn[n][e++] = "1";
  test_nsn[n][e++] = "---";
  n++;

  e=0;
  test_nsn[n][e++] = data_collection_1[d];
  test_nsn[n][e++] = "0";
  test_nsn[n][e] = (char *)malloc(50*sizeof(char));
  sprintf(test_nsn[n][e++], "%d", SICONOS_FRICTION_3D_NSN_AC);
  test_nsn[n][e++] = "5e-2";
  test_nsn[n][e++] = "1000";
  test_nsn[n][e++] = "---";
  n++;


  e=0;
  test_nsn[n][e++] = data_collection_1[d];
  test_nsn[n][e++] = "1";
  test_nsn[n][e] = (char *)malloc(50*sizeof(char));
  sprintf(test_nsn[n][e++], "%d", SICONOS_FRICTION_3D_NSN_AC_TEST);
  test_nsn[n][e++] = "1e-3";
  test_nsn[n][e++] = "10";
  test_nsn[n][e++] = "---";
  n++;


  e=0;
  test_nsn[n][e++] = data_collection_1[d];
  test_nsn[n][e++] = "0";
  test_nsn[n][e] = (char *)malloc(50*sizeof(char));
  sprintf(test_nsn[n][e++], "%d", SICONOS_FRICTION_3D_NSN_FB);
  test_nsn[n][e++] = "1e-3";
  test_nsn[n][e++] = "1000";
  test_nsn[n][e++] = "---";
  n++;


  e=0;
  test_nsn[n][e++] = data_collection_1[d];
  test_nsn[n][e++] = "0";
  test_nsn[n][e] = (char *)malloc(50*sizeof(char));
  sprintf(test_nsn[n][e++], "%d", SICONOS_FRICTION_3D_NSN_NM);
  test_nsn[n][e++] = "1e-3";
  test_nsn[n][e++] = "1000";
  test_nsn[n][e++] = "---";
  n++;


#ifdef WITH_UMFPACK
  test_nsn[5][1] = "1";
  test_nsn[8][1] = "1";
#endif



  
  test_nsn[n][0] ="---";
  return test_nsn;

}