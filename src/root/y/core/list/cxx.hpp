

//! \file

#ifndef Y_Core_CxxList_Included
#define Y_Core_CxxList_Included


#include "y/core/list.hpp"
#include "y/ability/releasable.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //! Basic C++ list
    //
    //__________________________________________________________________________
    template <typename NODE>
    class CxxList : public Core::ListOf<NODE>, public Releasable
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
        inline explicit CxxList() noexcept : Core::ListOf<NODE>(), Releasable()
        {
        }

        //! duplicate \param other another list
        inline CxxList(const CxxList &other) : Core::ListOf<NODE>(), Releasable()
        {
            try
            {
                for(const NODE *node=other.head;node;node=node->next)
                    this->pushTail( new NODE(*node) );
            }
            catch(...) { release_(); throw; }
        }

        //! cleanup
        inline virtual ~CxxList() noexcept { release_(); }

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        inline virtual void release() noexcept { release_(); }

    private:
        Y_Disable_Assign(CxxList); //!< discared

        //! remove all nodes from the tail
        inline void release_() noexcept { while(size>0) delete this->popTail(); }
    };

}

#endif // !Y_Core_CxxList_Included
