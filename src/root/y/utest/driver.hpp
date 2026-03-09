
//! \file

#ifndef Y_UTest_Driver_Included
#define Y_UTest_Driver_Included 1

#include "y/exception.hpp"
#include "y/libc/memory.h"
#include <cassert>

namespace Yttrium
{
    class UTest
    {
    public:
        static const char * const CallSign; //!< "UTest"
        typedef int (*Proc)(int,char **);   //!< entry point alias

        UTest(const char * const, Proc const) noexcept;
        ~UTest()                              noexcept;

        const char * const name;
        Proc         const proc;

        static const UTest * Search(const char * const  name,
                                    const UTest * const test,
                                    const size_t        size) noexcept;

    private:
        Y_Disable_Copy_And_Assign(UTest);
    };


    template <unsigned p>
    class UTestDriver
    {
    public:
        static const unsigned long N = (1<<p);

        inline UTestDriver() noexcept :
        test(0),
        size(0),
        wksp()
        {
            UTest * const addr = static_cast<UTest *>( Y_BZero(wksp) );
            Coerce(test) = addr;
        }

        inline ~UTestDriver() noexcept
        {
            while(size>0) {

            }
        }

        void operator()(const char * const name,
                        UTest::Proc const  proc)
        {
            assert(0!=name);
            assert(0!=proc);
            if(size>=N) throw Exception();
            if(UTest::Search(name,test,size)) throw Exception();
            new (test+size) UTest(name,proc);
        }



    private:
        Y_Disable_Copy_And_Assign(UTestDriver);
        UTest * const       test;
        const unsigned long size;
        char                wksp[N*sizeof(UTest)];
    };
}

#endif // !Y_UTest_Driver_Included

