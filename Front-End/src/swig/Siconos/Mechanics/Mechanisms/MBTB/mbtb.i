/* mbtb.i this file contains exported API of the MBTB library.*/
%module mbtb

%include start.i
#undef WITH_IO
#undef WITH_SERIALIZATION

%include path.i

%{
#include <SiconosKernel.hpp>
#include <MBTB_DATA.hpp>
#include <MBTB_internalTool.hpp>
#include <MBTB_PYTHON_API.hpp>
#include <ace.h>

  unsigned int sUseGravity = 0;
%}

%include handleException.i
%include sharedPointers.i
%include KernelTypes.i

%import Kernel/Kernel.i

%include <MBTB_DATA.hpp>
%include <MBTB_internalTool.hpp>
%include <MBTB_PYTHON_API.hpp>
%include <ace.h>

 //%include "MBTB_Body.hpp"