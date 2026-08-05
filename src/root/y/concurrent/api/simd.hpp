//! \file

#ifndef Y_Concurrent_SIMD_Included
#define Y_Concurrent_SIMD_Included 1

#include "y/concurrent/api/context.hpp"
#include "y/type/va/args.hpp"
#include "y/type/copy-of.hpp"
#include "y/type/temporary.hpp"
#include "y/container/writable.hpp"
#include "y/object/counted.hpp"
#include "y/ability/identifiable.hpp"

#if defined(_MSC_VER)
#pragma warning ( disable : 4371 ) // layout of class may have changed
#endif

namespace Yttrium
{
    namespace Concurrent
    {

        class Venue;

        //______________________________________________________________________
        //
        //
        //
        //! Single Instruction Multiple Data interface
        //
        //
        //______________________________________________________________________
        class SIMD : public CountedObject, public Writable<Context>, public Identifiable
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef VaList Arguments;
            typedef void (*Procedure)(Context &, Arguments &); //!< alias
            typedef void (*Proc0)(Context &);


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
            // Interface
            //
            //__________________________________________________________________
            virtual Lockable & sync() noexcept = 0; //!< \return internal synchronisation lock

            //__________________________________________________________________
            //
            //
            // Helper to create dynamic SIMD
            //
            //__________________________________________________________________
            static SIMD * Sequential();             //!< \return new sequential SIMD
            static SIMD * InParallel(const Venue);  //!< \return new parallel SIMD

            //__________________________________________________________________
            //
            //
            // Methods to call functions
            //
            //__________________________________________________________________

            void operator()(Proc0); //!< execute procedure on each context


            template <typename ARG1> static
            void Call1(Context &ctx, Arguments &args)
            {
                typedef void (*LocalProc)(Context &, ARG1 &);
                VaArgs ap(args);
                ap.func<LocalProc>()(ctx,ap.as<ARG1>());
            }

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
                Arguments                    args(func); args << arg1;
                const Temporary<Arguments *> tmpArgs(arguments,&args);
                const Temporary<Procedure>   tmpProc(procedure,Call1<ARG1>);
                run();
            }

            template <typename ARG1, typename ARG2> static
            void Call2(Context &ctx, Arguments &args)
            {
                typedef void (*LocalProc)(Context &, ARG1 &, ARG2 &);
                VaArgs ap(args);
                ap.func<LocalProc>()(ctx,ap.as<ARG1>(),ap.as<ARG2>());
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
                Arguments                    args(func); args << arg1 << arg2;
                const Temporary<Arguments *> tmpArgs(arguments,&args);
                const Temporary<Procedure>   tmpProc(procedure,Call2<ARG1,ARG2>);
                run();
            }


            //__________________________________________________________________
            //
            //
            // Methods to invoke methods
            //
            //__________________________________________________________________

            template <typename OBJECT, typename METHOD> static inline
            void Invoke0(Context &ctx, Arguments &args)
            {
                VaArgs ap(args);
                OBJECT &host = ap.as<OBJECT>();
                METHOD  meth = ap.meth<METHOD>();
                (host.*meth)(ctx);
            }

            //! invoke object.method(context) \param object host \param method to invoke
            template <typename OBJECT,typename METHOD> inline
            void operator()(OBJECT &object, METHOD method)
            {
                assert(!procedure);
                assert(!arguments);
                assert(method);
                Arguments                    args(object,method);
                const Temporary<Arguments *> tmpArgs(arguments,&args);
                const Temporary<Procedure>   tmpProc(procedure,Invoke0<OBJECT,METHOD>);
                run();
            }



            template <typename OBJECT, typename METHOD, typename ARG1> static inline
            void Invoke1(Context &ctx, Arguments &args)
            {
                VaArgs ap(args);
                OBJECT &host = ap.as<OBJECT>();
                METHOD  meth = ap.meth<METHOD>();
                (host.*meth)(ctx,ap.as<ARG1>());
            }

            //! invoke object.method(context,arg1)
            /**
             \param object host
             \param method to invoke
             \param arg1   first argument
             */
            template <typename OBJECT,typename METHOD, typename ARG1> inline
            void operator()(OBJECT &object, METHOD method, ARG1 &arg1)
            {
                assert(!procedure);
                assert(!arguments);
                assert(method);
                Arguments                    args(object,method); args << arg1;
                const Temporary<Arguments *> tmpArgs(arguments,&args);
                const Temporary<Procedure>   tmpProc(procedure,Invoke1<OBJECT,METHOD,ARG1>);
                run();
            }


            template <typename OBJECT, typename METHOD, typename ARG1, typename ARG2> static inline
            void Invoke2(Context &ctx, Arguments &args)
            {
                VaArgs ap(args);
                OBJECT &host = ap.as<OBJECT>();
                METHOD  meth = ap.meth<METHOD>();
                (host.*meth)(ctx,ap.as<ARG1>(),ap.as<ARG2>());
            }

            //! invoke object.method(context,arg1,arg2)
            /**
             \param object host
             \param method to invoke
             \param arg1   first  argument
             \param arg2   second argument
             */
            template <typename OBJECT,typename METHOD, typename ARG1, typename ARG2> inline
            void operator()(OBJECT &object, METHOD method, ARG1 &arg1, ARG2 &arg2)
            {
                assert(!procedure);
                assert(!arguments);
                assert(method);
                Arguments                    args(object,method); args << arg1 << arg2;
                const Temporary<Arguments *> tmpArgs(arguments,&args);
                const Temporary<Procedure>   tmpProc(procedure,Invoke2<OBJECT,METHOD,ARG1,ARG2>);
                run();
            }
            

#if 0
            //__________________________________________________________________
            //
            //
            // Methods to invoke methods
            //
            //__________________________________________________________________

            //! invoke object.method(context) \param object host \param method to invoke
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

            //! invoke object.method(context,arg1)
            /**
             \param object host
             \param method to invoke
             \param arg1   first argument
             */
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

            //! invoke object.method(context,arg1,arg2)
            /**
             \param object host
             \param method to invoke
             \param arg1   first argument
             \param arg2   second argument
             */
            template <typename OBJECT,typename METHOD, typename ARG1, typename ARG2> inline
            void operator()(OBJECT &object, METHOD method, ARG1 &arg1, ARG2 &arg2)
            {
                assert(!procedure);
                assert(!arguments);
                assert(method);
                Arguments                    args(object,method,arg1,arg2);
                const Temporary<Arguments *> tmpArgs(arguments,&args);
                const Temporary<Procedure>   tmpProc(procedure,CallMeth2<OBJECT,METHOD,ARG1,ARG2>);
                run();
            }

#endif

        protected:
            virtual void run() = 0; //!< run procedure on each context with optional argument(s)
            Procedure  procedure;   //!< temporary procedure
            Arguments *arguments;   //!< temporary arguments



        private:
            Y_Disable_Copy_And_Assign(SIMD); //!< discarded

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            static void CallFunc0(Context &ctx, Arguments &args);

#if 0
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

            template <typename OBJECT, typename METHOD, typename ARG1, typename ARG2> static
            void CallMeth2(Context &ctx, Arguments &args)
            {
                assert(args.addr);
                assert(args.meth);
                assert(args.arg1);
                assert(args.arg2);
                OBJECT & object = *static_cast<OBJECT *>(args.addr);
                union {
                    Meth   m;
                    METHOD M;
                } alias = { args.meth };
                (object.*alias.M)(ctx,
                                  *static_cast<ARG1 *>(args.arg1),
                                  *static_cast<ARG2 *>(args.arg2));
            }
#endif


#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        };


    }




}

#endif // !Y_Concurrent_SIMD_Included
