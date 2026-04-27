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
            typedef void (SIMD::*Meth)(void);

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
                arg2(0),
                meth(0)
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


                //! setup with object and method
                template <typename OBJECT, typename METHOD> inline
                Arguments(OBJECT &object, METHOD method) noexcept :
                addr( (void*)&object ),
                arg1(0), arg2(0),
                meth( MethodToMeth(method) )
                {

                }

                //! setup with object, method and argument
                template <typename OBJECT, typename METHOD, typename ARG1> inline
                Arguments(OBJECT &object, METHOD method, ARG1 &usr1) noexcept :
                addr( (void*)&object ),
                arg1( (void*) &usr1 ),
                arg2(0),
                meth( MethodToMeth(method) )
                {

                }




                //______________________________________________________________
                //
                // Members
                //______________________________________________________________
                void * const addr; //!< anonymous address
                void * const arg1; //!< first  argument address
                void * const arg2; //!< second argument address
                Meth   const meth; //!< method pointer

            private:
                Y_Disable_Copy_And_Assign(Arguments); //!< discarded

                template <typename METHOD> inline
                Meth MethodToMeth(METHOD method) noexcept
                {
                    union {
                        METHOD M;
                        Meth   m;
                    } alias =  { method };
                    return alias.m;
                }
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
            // Methods to run functions
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

            //__________________________________________________________________
            //
            //
            // Methods to run objects
            //
            //__________________________________________________________________

            template <typename OBJECT,typename METHOD> inline
            void operator()(OBJECT &object, METHOD method)
            {
                assert(!procedure);
                assert(!arguments);
                assert(method);
                Arguments                    args(object,method);
                const Temporary<Arguments *> tmpArgs(arguments,&args);
                const Temporary<Procedure>   tmpProc(procedure,CallMeth0<OBJECT,METHOD>);
                run();
            }

            template <typename OBJECT,typename METHOD, typename ARG1> inline
            void operator()(OBJECT &object, METHOD method, ARG1 &arg1)
            {
                assert(!procedure);
                assert(!arguments);
                assert(method);
                Arguments                    args(object,method,arg1);
                const Temporary<Arguments *> tmpArgs(arguments,&args);
                const Temporary<Procedure>   tmpProc(procedure,CallMeth1<OBJECT,METHOD,ARG1>);
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


            template <typename OBJECT, typename METHOD> static
            void CallMeth0(Context &ctx, Arguments &args)
            {
                assert(args.addr);
                assert(args.meth);
                OBJECT & object = *static_cast<OBJECT *>(args.addr);
                union {
                    Meth   m;
                    METHOD M;
                } alias = { args.meth };
                (object.*alias.M)(ctx);
            }

            template <typename OBJECT, typename METHOD, typename ARG1> static
            void CallMeth1(Context &ctx, Arguments &args)
            {
                assert(args.addr);
                assert(args.meth);
                assert(args.arg1);
                OBJECT & object = *static_cast<OBJECT *>(args.addr);
                union {
                    Meth   m;
                    METHOD M;
                } alias = { args.meth };
                (object.*alias.M)(ctx,*static_cast<ARG1 *>(args.arg1));
            }



#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        };
    }
}

#endif // !Y_Concurrent_SIMD_Included
