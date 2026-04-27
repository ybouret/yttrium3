//! \file

#ifndef Y_Concurrent_SIMD_Included
#define Y_Concurrent_SIMD_Included 1

#include "y/concurrent/api/context.hpp"
#include "y/type/copy-of.hpp"
#include "y/type/temporary.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        //______________________________________________________________________
        //
        //
        //
        //! Single Instruction Multiple Data interface
        //
        //
        //______________________________________________________________________
        class SIMD
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________

            //__________________________________________________________________
            //
            //
            //! Holding arguments
            //
            //__________________________________________________________________
            class Arguments
            {
            public:
                //______________________________________________________________
                //
                // C++
                //______________________________________________________________
                Arguments(const CopyOf_ &, void * const) noexcept; //!< setup with arg1 as copy of address
                ~Arguments() noexcept;  //!< cleanup

                //! setup with one argument \param usr1 argument no. 1
                template <typename ARG1> inline
                Arguments(ARG1 &usr1) noexcept : arg1( (void*)&usr1 )
                {
                }

                //______________________________________________________________
                //
                // Members
                //______________________________________________________________
                void * const addr; //!< anonymous address
                void * const arg1; //!< first argument address

            private:
                Y_Disable_Copy_And_Assign(Arguments); //!< discarded
            };

            typedef void (*Procedure)(Context &, Arguments &); //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit SIMD() noexcept; //!< setup
            virtual ~SIMD() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            void operator()( void (*)(Context &) ); //!< execute function on each context


        protected:
            virtual void run() = 0; //!< run procederue on each context with arugment
            Procedure  procedure;   //!< temporary procedure
            Arguments *arguments;   //!< temporary arguments

        private:
            Y_Disable_Copy_And_Assign(SIMD); //!< discarded

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            static void CallFunc0(Context &ctx, Arguments &args);

#endif

        };
    }
}

#endif // !Y_Concurrent_SIMD_Included
