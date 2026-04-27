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

                //! setup with one argument
                /**
                \param user function address
                \param usr1 first argument
                 */
                template <typename ARG1> inline
                Arguments(void * const user, ARG1 &usr1) noexcept :
                addr(user),
                arg1( (void*)&usr1 ),
                arg2(0)
                {
                }

                //! setup with one argument
                /**
                 \param user function address
                 \param usr1 first argument
                 \param usr2 second argument
                 */
                template <typename ARG1,typename ARG2> inline
                Arguments(void * const user, ARG1 &usr1, ARG2 &usr2) noexcept :
                addr(user),
                arg1( (void*)&usr1 ),
                arg2( (void*)&usr2 )
                {
                }

                //______________________________________________________________
                //
                // Members
                //______________________________________________________________
                void * const addr; //!< anonymous address
                void * const arg1; //!< first  argument address
                void * const arg2; //!< second argument address


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

            //! execute func(ctx,arg1) for each context
            /**
             \param func function
             \param arg1 first argument
             */
            template <typename ARG1> inline
            void operator()( void (*func)(Context &, ARG1 &), ARG1 &arg1 )
            {
                assert(!procedure);
                assert(!arguments);
                assert(func);
                Arguments                    args((void*)func,arg1);
                const Temporary<Arguments *> tmpArgs(arguments,&args);
                const Temporary<Procedure>   tmpProc(procedure,CallFunc1<ARG1>);
                run();
            }

            //! execute func(ctx,arg1,arg2) for each context
            /**
             \param func function
             \param arg1 first argument
             \param arg2 first argument
             */
            template <typename ARG1, typename ARG2> inline
            void operator()( void (*func)(Context &, ARG1 &, ARG2 &), ARG1 &arg1, ARG2 &arg2 )
            {
                assert(!procedure);
                assert(!arguments);
                assert(func);
                Arguments                    args((void*)func,arg1,arg2);
                const Temporary<Arguments *> tmpArgs(arguments,&args);
                const Temporary<Procedure>   tmpProc(procedure,CallFunc2<ARG1,ARG2>);
                run();
            }


        protected:
            virtual void run() = 0; //!< run procederue on each context with arugment
            Procedure  procedure;   //!< temporary procedure
            Arguments *arguments;   //!< temporary arguments

        private:
            Y_Disable_Copy_And_Assign(SIMD); //!< discarded

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            static void CallFunc0(Context &ctx, Arguments &args);

            template <typename ARG1> static
            void CallFunc1(Context &ctx, Arguments &args)
            {
                assert(args.addr);
                assert(args.arg1);
                union {
                    void * addr;
                    void (*func)(Context &, ARG1 &);
                } alias = { args.addr };
                assert(alias.func);
                alias.func(ctx, *static_cast<ARG1*>(args.arg1) );
            }

            template <typename ARG1, typename ARG2> static
            void CallFunc2(Context &ctx, Arguments &args)
            {
                assert(args.addr);
                assert(args.arg1);
                assert(args.arg2);
                union {
                    void * addr;
                    void (*func)(Context &, ARG1 &, ARG2 &);
                } alias = { args.addr };
                assert(alias.func);
                alias.func(ctx, *static_cast<ARG1*>(args.arg1), *static_cast<ARG2*>(args.arg2) );
            }

#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        };
    }
}

#endif // !Y_Concurrent_SIMD_Included
