
//! \file

#ifndef Y_Concurrent_Threaded_Included
#define Y_Concurrent_Threaded_Included 1

#include "y/concurrent/thread.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Concurrent
    {

        //______________________________________________________________________
        //
        //
        //
        //! Wrapper for calls
        //
        //
        //______________________________________________________________________
        class ThreadSkin
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef void (ThreadSkin::*Meth)(void); //!< alias


            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup for no argument method
            /**
             \param userHost PERSISTENT object reference
             \param userMeth method pointer for object
             */
            template <typename OBJECT, typename METHOD> inline
            explicit ThreadSkin(OBJECT & userHost, METHOD const userMeth) noexcept :
            call( Launch0<OBJECT,METHOD> ),
            host( &userHost ),
            meth( MethodToMeth<METHOD>(userMeth) ),
            arg1(0)
            {

            }


            //! setup for no 1-argument method
            /**
             \param userHost PERSISTENT object reference
             \param userMeth method pointer for object
             \param u        argument for method
             */
            template <typename OBJECT, typename METHOD, typename U> inline
            explicit ThreadSkin(OBJECT &     userHost,
                                METHOD const userMeth,
                                U &          u) noexcept :
            call( Launch1<OBJECT,METHOD,U> ),
            host( &userHost ),
            meth( MethodToMeth<METHOD>(userMeth) ),
            arg1( (void*) &u)
            {

            }

            //! cleanup
            virtual ~ThreadSkin() noexcept;



        protected:
            ThreadSkin * data() noexcept; //!< for threaded \return this

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            Thread::Proc const call; //!< alias
            void *       const host; //!< alias
            Meth         const meth; //!< alias
            void *       const arg1; //!< alias

        private:
            Y_Disable_Copy_And_Assign(ThreadSkin); //!< discardded


#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
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
                ThreadSkin    &self = *static_cast<ThreadSkin *>(args);  assert(self.host);
                OBJECT &       host = *static_cast<OBJECT *>(self.host); assert(self.meth);
                METHOD   const func = MethToMethod<METHOD>(self.meth);
                (host.*func)();
            }

            template <typename OBJECT, typename METHOD, typename U> static inline
            void Launch1(void * const args)
            {
                assert(args);
                ThreadSkin    &self = *static_cast<ThreadSkin *>(args);    assert(self.host);
                OBJECT &       host = *static_cast<OBJECT *>(self.host);   assert(self.meth);
                METHOD   const func = MethToMethod<METHOD>(self.meth);     assert(self.arg1);
                U &            arg1 = *static_cast<U *>(self.arg1);
                (host.*func)(arg1);
            }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        };

        //______________________________________________________________________
        //
        //
        //
        //! Object + Method in a thread
        //
        //
        //______________________________________________________________________
        class Threaded : public ThreadSkin, public Thread
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! start object.method(void)
            /**
             \param userHost PERSISTENT object reference
             \param userMeth method pointer for object
             */
            template <typename OBJECT,typename METHOD>
            explicit Threaded(OBJECT &     userHost,
                              METHOD const userMeth) :
            ThreadSkin(userHost,userMeth),
            Thread(call,data())
            {

            }
            
            //! start object.method(u)
            /**
             \param userHost PERSISTENT object reference
             \param userMeth method pointer for object
             \param u        argument for method
             */
            template <typename OBJECT,typename METHOD,typename U>
            explicit Threaded(OBJECT &     userHost,
                              METHOD const userMeth,
                              U           &u) :
            ThreadSkin(userHost,userMeth,u),
            Thread(call,data())
            {

            }

            //! cleanup
            virtual ~Threaded() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Threaded); //!< discarded
        };

    }

}

#endif // !Y_Concurrent_Threaded_Included

