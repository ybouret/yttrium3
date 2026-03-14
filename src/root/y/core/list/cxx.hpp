

//! \file

#ifndef Y_Core_CxxList_Included
#define Y_Core_CxxList_Included


#include "y/core/list.hpp"

namespace Yttrium
{

    template <typename NODE>
    class CxxList : public Core::ListOf<NODE>
    {
    public:
        using Core::ListOf<NODE>::size;

        inline explicit CxxList() noexcept : Core::ListOf<NODE>()
        {
        }

        inline CxxList(const CxxList &other) : Core::ListOf<NODE>()
        {
            try
            {
                for(const NODE *node=other.head;node;node=node->next)
                    this->pushTail( new NODE(*node) );
            }
            catch(...) { free_(); throw; }
        }

        inline virtual ~CxxList() noexcept
        {
            free_();
        }

        inline virtual void free() noexcept
        {
            free_();
        }

    private:
        Y_Disable_Assign(CxxList);
        inline void free_() noexcept { while(size>0) delete this->popTail(); }
    };

}

#endif // !Y_Core_CxxList_Included
