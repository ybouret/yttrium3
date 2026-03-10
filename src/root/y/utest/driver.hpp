
//! \file

#ifndef Y_UTest_Driver_Included
#define Y_UTest_Driver_Included 1

#include "y/exception.hpp"
#include "y/libc/bzero.h"
#include <iostream>

namespace Yttrium
{

    namespace UTest
    {
        //! entry point alias
        typedef int (*CFunction)(int,char **);

        //! store named entry poin
        struct Proc {
            CFunction    func; //!< entry point function
            const char * name; //!< entry point name
        };

        //______________________________________________________________________
        //
        //
        //! Handle tests
        //
        //______________________________________________________________________
        class Driver
        {
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
        protected:
            explicit Driver(Proc * const procEntry, const size_t procCount) noexcept;
        public:
            virtual ~Driver() noexcept;

            void operator()(CFunction const, const char * const) noexcept;
            int  operator()(int,char **);

            Proc * search(const char * const name) noexcept;
            void   display() const;
            size_t countContaining(const char * const name) const noexcept;
            void   printContaining(const char * const name) const;

        private:
            Y_Disable_Copy_And_Assign(Driver);
            Proc * const proc;
            size_t       size;
            const size_t pmax;
            size_t       width;
        };

        template <unsigned LN2>
        class DriverData
        {
        protected:
            static const size_t one = 1;
            static const size_t N   = (1<<LN2);
            inline explicit DriverData() noexcept :
            wksp()
            {
            }

        public:

            inline virtual ~DriverData() noexcept
            {
            }

        protected:
            char wksp[N*sizeof(Proc)];

        private:
            Y_Disable_Copy_And_Assign(DriverData);
        };

        template <unsigned LN2>
        class DriverWith : public DriverData<LN2>, public Driver
        {
        public:
            using DriverData<LN2>::wksp;
            using DriverData<LN2>::N;

            inline explicit DriverWith() noexcept :
            DriverData<LN2>(),
            Driver(static_cast<Proc *>(Y_BZero(wksp)), N)
            {
            }

            inline virtual ~DriverWith() noexcept {}

        private:
            Y_Disable_Copy_And_Assign(DriverWith);
        };


    }

    //! prepare driver
#define Y_UTEST_DECL(LN2) \
/**/  using namespace Yttrium;\
/**/  int main(int argc, char **argv) \
/**/  {\
/**/    UTest::DriverWith<LN2> driver;\
/**/    try {\

    //! run driver
#define Y_UTEST_EXEC() \
/**/      return driver(argc,argv);\
/**/    }\
/**/    catch(...) { std::cerr << "unhandled exception!" << std::endl; return 2; }\
/**/  }

    //! declare test
#define Y_UTEST(NAME) do { \
/**/ extern int (Y_UTest_##NAME)(int,char **);\
/**/ driver(Y_UTest_##NAME,#NAME);\
/**/ } while(false)



}

#endif // !Y_UTest_Driver_Included

