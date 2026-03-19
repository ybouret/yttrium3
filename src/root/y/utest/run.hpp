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
        //! helper to pretty print info
        struct Display
        {
            static size_t Width; //!< default justification width

            //! print justified fields
            /**
             \param os   output stream
             \param pfx  optional prefix
             \param name optional name
             \param sfx  optional suffix
             \return os
             */
            static std::ostream & Print(std::ostream &     os,
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
Yttrium::UTest::Display::Print(std::cerr,"       ",#FIELD," ") << " = " << (FIELD) << std::endl

    //! local silent assertion
#define Y_ASSERT(EXPR) \
/**/    do { \
/**/        const bool __OK__ = (EXPR);\
/**/        if(!__OK__) throw Yttrium::Specific::Exception(Core::Failure,"line %d: %s",__LINE__,#EXPR);\
/**/    } while(false)

    //! local explicit check
#define Y_CHECK(EXPR) \
/**/    do { \
/**/        const bool __OK__   = (EXPR);\
/**/        const char __XP__[] = #EXPR; \
/**/        Yttrium::UTest::Display::Print(std::cerr,"[",__XP__,"]") << " : " << (__OK__ ? Core::Success : Core::Failure) << std::endl;\
/**/        if(!__OK__) throw Yttrium::Specific::Exception(Core::Failure,"line %d: %s",__LINE__,__XP__);\
/**/    } while(false)

}

#endif // !Y_UTest_Run_Included

