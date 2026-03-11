//! \file

#ifndef Y_UTest_Run_Included
#define Y_UTest_Run_Included 1

#include "y/exception.hpp"
#include <iostream>
#include <iomanip>

namespace Yttrium
{

    namespace UTest
    {
        struct Display
        {
            static size_t Width;
            static std::ostream & Print(std::ostream &,
                                        const char * const pfx,
                                        const char * const name,
                                        const char * const sfx);
        };
    }

    //! create entry point for a test
#define Y_UTEST(NAME)                               \
/**/    int Y_UTest_##NAME(int argc, char **argv) { \
/**/        (void)argc; (void)argv;                 \
/**/        static const char * const test = #NAME; \
/**/        (void)test; do

    //! finish test
#define Y_UDONE() while(false); return 0; }

    //! display justified sizeof
#define Y_SIZEOF(CLASS) \
Yttrium::UTest::Display::Print(std::cerr,"sizeof(",#CLASS,")") << " = " << sizeof(CLASS) << std::endl

    //! display justified field value
#define Y_PRINTV(FIELD) \
Yttrium::UTest::Display::Print(std::cerr,0,#FIELD,0) << " = " << (FIELD) << std::endl


#define Y_ASSERT(EXPR) \
/**/    do { \
/**/        const bool __OK__ = (EXPR);\
/**/        if(!__OK__) throw Yttrium::Specific::Exception(Core::Failure,"%s:%d: %s",test,__LINE__,#EXPR);\
/**/    } while(false)

}

#endif // !Y_UTest_Run_Included

