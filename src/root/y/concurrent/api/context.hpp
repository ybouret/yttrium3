//! \file

#ifndef Y_Concurrent_Context_Included
#define Y_Concurrent_Context_Included 1


#include "y/concurrent/member.hpp"
#include "y/ability/lockable.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        //______________________________________________________________________
        //
        //
        //
        //! Member with persistent synchronization object
        //
        //
        //______________________________________________________________________
        class Context : public Member
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            //! setup
            /**
             \param sz sz>0
             \param rk   0<=rk<sz
             \param lk  PERSISTENT lockable
             */
            explicit Context(const size_t sz,
                             const size_t rk,
                             Lockable &   lk) noexcept;
            explicit Context(Lockable &)      noexcept; //!< setup with PERSISTENT lockable
            virtual ~Context() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            Lockable &sync; //!< PERSISTENT lockable
            
        private:
            Y_Disable_Copy_And_Assign(Context); //!< discarded
        };
    }
}


#endif // !Y_Concurrent_Context_Included
