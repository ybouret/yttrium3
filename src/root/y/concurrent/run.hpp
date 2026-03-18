
//! \file

#ifndef Y_Concurrent_Run_Included
#define Y_Concurrent_Run_Included 1

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
        //! Data to run object.method(...) in a thread
        //
        //
        //______________________________________________________________________

        class RunData
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef void (RunData::*Meth)(void); //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
        protected:
            //! setup
            /**
             \param object PERSISTENT object
             \param method OBJECT::*METHOD()
             */
            template <typename OBJECT, typename METHOD> inline
            explicit RunData(OBJECT &object, METHOD method) noexcept :
            host( &object ),
            meth( GetMeth(method) ),
            arg1(0)
            {
            }

            //! setup
            /**
             \param object PERSISTENT object
             \param method OBJECT::*METHOD(arg1)
             \param arg1   first argument
             */
            template <typename OBJECT, typename METHOD, typename ARG1> inline
            explicit RunData(OBJECT &object, METHOD method, ARG1 &arg1 ) noexcept :
            host( &object ),
            meth( GetMeth(method) ),
            arg1( (void*) &arg1 )
            {
            }


            //! cleanup
            virtual ~RunData() noexcept;

        private:
            Y_Disable_Copy_And_Assign(RunData); //!< discarded
            void * const host; //!< host address
            Meth         meth; //!< anonymous method
            void * const arg1; //!< optional arg1 address

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            template <typename METHOD> static inline
            Meth GetMeth(METHOD method) noexcept
            {
                assert(sizeof(METHOD) == sizeof(Meth));
                union  {
                    METHOD M;
                    Meth   m;
                } alias = { method };
                return alias.m;
            }

            template <typename METHOD> inline
            METHOD getMethod() noexcept
            {
                assert(sizeof(METHOD) == sizeof(Meth));
                union  {
                    Meth   m;
                    METHOD M;
                } alias = { meth };
                return alias.M;
            }

        protected:
            template <typename OBJECT, typename METHOD> static inline
            void Launch0(void * const addr)
            {
                assert(addr);
                RunData  &p = *static_cast<RunData *>(addr);
                OBJECT   &o = *static_cast<OBJECT *>(p.host);
                METHOD    m = p.getMethod<METHOD>();
                (o.*m)();
            }

            template <typename OBJECT, typename METHOD, typename ARG1> static inline
            void Launch1(void * const addr)
            {
                assert(addr);
                RunData  & p = *static_cast<RunData *>(addr);
                OBJECT   & o = *static_cast<OBJECT *>(p.host);
                METHOD     m = p.getMethod<METHOD>();
                ARG1     & a = *static_cast<ARG1 *>(p.arg1);
                (o.*m)(a);
            }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        };

        //______________________________________________________________________
        //
        //
        //
        //! Threaded object.method(...)
        //
        //
        //______________________________________________________________________
        class  Run : public RunData, public Thread
        {
        public:
            //! setup and Launch0
            /**
             \param object PERSISTENT object
             \param method OBJECT::*METHOD()
             */
            template <typename OBJECT, typename METHOD> inline
            explicit Run(OBJECT &object, METHOD method) noexcept :
            RunData(object,method),
            Thread( Launch0<OBJECT,METHOD>, self() )
            {
            }

            //! setup and Launch1
            /**
             \param object PERSISTENT object
             \param method OBJECT::*METHOD(arg1)
             \param arg1   first argument
             */
            template <typename OBJECT, typename METHOD, typename ARG1> inline
            explicit Run(OBJECT &object, METHOD method, ARG1 &arg1) noexcept :
            RunData(object,method,arg1),
            Thread( Launch1<OBJECT,METHOD,ARG1>, self() )
            {
            }

            //! cleanup
            virtual ~Run() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Run); //!< discarded
            RunData * self() noexcept;      //!< helper for Launch \return this
        };

    }

}




#endif // !Y_Concurrent_Run_Included

