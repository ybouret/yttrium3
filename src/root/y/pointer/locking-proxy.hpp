

//! \file

#ifndef Y_Pointer_Locking_Proxy_Included
#define Y_Pointer_Locking_Proxy_Included 1

#include "y/type/args.hpp"
#include <cassert>

namespace Yttrium
{

    namespace Smart
    {
        //______________________________________________________________________
        //
        //
        //
        //! helper for operator->
        //
        //
        //______________________________________________________________________
        template <class T> class LockingProxy
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Expose(T,Type); //!< aliases

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! initialize \param ptr object that shall be locked
            inline LockingProxy(T * const ptr) : pointee((MutableType*)ptr)
            {
                assert(0!=pointee);
                pointee->lock();
            }

            //! cleanup, unlock object
            inline ~LockingProxy() noexcept {
                assert(0!=pointee);
                pointee->unlock();
            }

            //! \return locked object address
            inline Type * operator->() noexcept {
                assert(0!=pointee);
                return pointee;
            }

            //! \return locked object address
            inline ConstType * operator->() const noexcept {
                assert(0!=pointee);
                return pointee;
            }

            //! duplicate \param other
            inline LockingProxy(const LockingProxy &other) noexcept :
            pointee(other.pointee)
            {
            }

        private:
            Y_Disable_Assign(LockingProxy); //!< discarding
            MutableType * const pointee;    //!< object address
        };
    }
}
 

#endif // !Y_Pointer_Locking_Proxy_Included

