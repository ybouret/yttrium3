
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

        //! store named entry point
        struct Proc {
            CFunction    func; //!< entry point function
            const char * name; //!< entry point name
        };

        //______________________________________________________________________
        //
        //
        //
        //! Handle tests
        //
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
            //! setup \param procEntry memory region \param procCount capacity
            explicit Driver(Proc * const procEntry, const size_t procCount) noexcept;
        public:
            //! cleanup
            virtual ~Driver() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! register a new named test
            void operator()(CFunction const, const char * const) noexcept;

            //! forward call from main \return forwarded call
            int  operator()(int,char **);

            //! search proc by name \param name queried name \return matching proc, NULL otherwise
            Proc * search(const char * const name) noexcept;

            //! display registered test
            void   display() const;

            //! count tests containing name in their own name \param name queried name \return possible tests
            size_t countContaining(const char * const name) const noexcept;

            //! prin test containing name in their own name \param name queried name
            void   printContaining(const char * const name) const;

        private:
            Y_Disable_Copy_And_Assign(Driver); //!< discard
            Proc * const proc;     //!< base address for tests
            size_t       size;     //!< active tests
            const size_t capacity; //!< maximum number of tests
            size_t       width;    //!< maximum name length
        };

        //______________________________________________________________________
        //
        //
        //
        //! Data to store named tests
        //
        //
        //______________________________________________________________________
        template <unsigned LN2>
        class DriverData
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const size_t One = 1;          //!< alias
            static const size_t N   = (One<<LN2); //!< capacity

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
        protected:
            //! setup
            inline explicit DriverData() noexcept :
            wksp()
            {
            }

        public:
            //! cleanup
            inline virtual ~DriverData() noexcept
            {
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
        protected:
            char wksp[N*sizeof(Proc)]; //!< internal stack for tests

        private:
            Y_Disable_Copy_And_Assign(DriverData); //!< discard
        };

        //______________________________________________________________________
        //
        //
        //
        //! Self-contained 2^LN2 tests
        //
        //
        //______________________________________________________________________
        template <unsigned LN2>
        class DriverWith : public DriverData<LN2>, public Driver
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            using DriverData<LN2>::wksp;
            using DriverData<LN2>::N;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            inline explicit DriverWith() noexcept :
            DriverData<LN2>(),
            Driver(static_cast<Proc *>(Y_BZero(wksp)), N)
            {
            }

            //! cleanup
            inline virtual ~DriverWith() noexcept {}

        private:
            Y_Disable_Copy_And_Assign(DriverWith); //!< discard
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
/**/    catch(const Yttrium::Exception &e) { e.display(std::cerr); return 1; }\
/**/    catch(const std::exception &e) { std::cerr << "** " << e.what() << std::endl; return 2; }\
/**/    catch(...) { std::cerr << "unhandled exception!" << std::endl; return 3; }\
/**/  }

    //! declare test
#define Y_UTEST(NAME) do { \
/**/ extern int (Y_UTest_##NAME)(int,char **);\
/**/ driver(Y_UTest_##NAME,#NAME);\
/**/ } while(false)



}

#endif // !Y_UTest_Driver_Included

