
//! \file

#ifndef Y_Concurrent_Threaded_Included
#define Y_Concurrent_Threaded_Included 1

#include "y/concurrent/thread.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Concurrent
    {

        class ThreadingData
        {
        public:
            typedef void (ThreadingData::*Meth)(void);


            template <typename OBJECT, typename METHOD> inline
            explicit ThreadingData(OBJECT & userHost, METHOD const userMeth) noexcept :
            call( Launch0<OBJECT,METHOD> ),
            host( &userHost ),
            meth( MethodToMeth<METHOD>(userMeth) ),
            arg1(0)
            {

            }

            template <typename OBJECT, typename METHOD, typename U> inline
            explicit ThreadingData(OBJECT &     userHost,
                                   METHOD const userMeth,
                                   U &          u) noexcept :
            call( Launch1<OBJECT,METHOD,U> ),
            host( &userHost ),
            meth( MethodToMeth<METHOD>(userMeth) ),
            arg1( (void*) &u)
            {

            }




            virtual ~ThreadingData() noexcept;

            Thread::Proc const call;
            void *       const host;
            Meth         const meth;
            void *       const arg1;

        protected:
            ThreadingData * data() noexcept;

        private:
            Y_Disable_Copy_And_Assign(ThreadingData);

            template <typename METHOD> static inline
            Meth MethodToMeth(METHOD const userMeth) noexcept
            {
                union
                {
                    METHOD M;
                    Meth   m;
                } alias = { userMeth };
                return alias.m;
            }

            template <typename METHOD> static inline
            METHOD MethToMethod(Meth mine) noexcept
            {
                union
                {
                    Meth   m;
                    METHOD M;
                } alias = { mine };
                return alias.M;
            }


            template <typename OBJECT, typename METHOD> static inline
            void Launch0(void * const args)
            {
                assert(args);
                ThreadingData &self = *static_cast<ThreadingData *>(args); assert(self.host);
                OBJECT &       host = *static_cast<OBJECT *>(self.host);   assert(self.meth);
                METHOD   const func = MethToMethod<METHOD>(self.meth);
                (host.*func)();
            }

            template <typename OBJECT, typename METHOD, typename U> static inline
            void Launch1(void * const args)
            {
                assert(args);
                ThreadingData &self = *static_cast<ThreadingData *>(args); assert(self.host);
                OBJECT &       host = *static_cast<OBJECT *>(self.host);   assert(self.meth);
                METHOD   const func = MethToMethod<METHOD>(self.meth);     assert(self.arg1);
                U &            arg1 = *static_cast<U *>(self.arg1);
                (host.*func)(arg1);
            }

        };


        class Threaded : public ThreadingData, public Thread
        {
        public:

            template <typename OBJECT,typename METHOD>
            explicit Threaded(OBJECT &     userHost,
                              METHOD const userMeth) :
            ThreadingData(userHost,userMeth),
            Thread(call,data())
            {

            }

            template <typename OBJECT,typename METHOD,typename U>
            explicit Threaded(OBJECT &     userHost,
                              METHOD const userMeth,
                              U           &u) :
            ThreadingData(userHost,userMeth,u),
            Thread(call,data())
            {

            }

            virtual ~Threaded() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Threaded);
        };

    }

}

#endif // !Y_Concurrent_Threaded_Included

