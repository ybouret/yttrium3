
//! \file

#ifndef Y_Core_CloneList_Included
#define Y_Core_CloneList_Included


#include "y/core/list.hpp"
#include "y/ability/releasable.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //! List of C++ cloneable nodes
    //
    //__________________________________________________________________________
    template <typename NODE>
    class CloneList : public Core::ListOf<NODE>, public Releasable
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        using Core::ListOf<NODE>::size;

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup empty
        inline explicit CloneList() noexcept : Core::ListOf<NODE>(), Releasable()
        {
        }

        //! duplicate \param other another list
        inline CloneList(const CloneList &other) : Core::ListOf<NODE>(), Releasable()
        {
            try
            {
                for(const NODE *node=other.head;node;node=node->next)
                    this->pushTail( node->clone() );
            }
            catch(...) { release_(); throw; }
        }

        //! cleanup
        inline virtual ~CloneList() noexcept { release_(); }

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        inline virtual void release() noexcept { release_(); }

    private:
        Y_Disable_Assign(CloneList); //!< discared

        //! remove all nodes from the tail
        inline void release_() noexcept { while(size>0) delete this->popTail(); }
    };
}

#endif // !Y_Core_CloneList_Included
