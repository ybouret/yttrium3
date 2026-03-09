//! \file

#ifndef Y_UTest_Run_Included
#define Y_UTest_Run_Included 1

#include "y/exception.hpp"
#include <iostream>

namespace Yttrium
{

#define Y_UTEST(NAME) \
/**/    extern "C" int Y_UTest_##NAME(int argc, char **argv) {\
/**/        (void)argc; (void)argv; \
/**/        static const char * const test = #NAME; (void)test; do

#define Y_UDONE() while(false); return 0; }

}

#endif // !Y_UTest_Run_Included

