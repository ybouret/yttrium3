
//! \file

#ifndef Y_Core_CxxPool_Included
#define Y_Core_CxxPool_Included


#include "y/core/pool.hpp"
#include "y/ability/releasable.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //! Basic C++ pool
    //
    //__________________________________________________________________________
    template <typename NODE>
    class CxxPoolOf : public Core::PoolOf<NODE>, public Releasable
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        using Core::PoolOf<NODE>::size;

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup empty
        inline explicit CxxPoolOf() noexcept : Core::PoolOf<NODE>()
        {
        }

        //! duplicate \param other another pool
        inline CxxPoolOf(const CxxPoolOf &other) : Core::PoolOf<NODE>()
        {
            try {
                for(const NODE *node=other.head;node;node=node->next)
                    this->store( new NODE(*other.head) );
            }
            catch(...) { release_(); throw; }
        }

        //! cleanup
        inline virtual ~CxxPoolOf() noexcept { release_(); }

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        inline virtual void release() noexcept { release_(); }

    private:
        Y_Disable_Assign(CxxPoolOf); //!< discarded

        //! remove all nodes from head
        inline void release_() noexcept { while(size>0) delete this->query(); }
    };

}

#endif // !Y_Core_CxxPool_Included
