
//! \file

#ifndef Y_Core_CxxPool_Included
#define Y_Core_CxxPool_Included


#include "y/core/pool.hpp"

namespace Yttrium
{

    template <typename NODE>
    class CxxPool : public Core::PoolOf<NODE>
    {
    public:
        using Core::PoolOf<NODE>::size;

        inline explicit CxxPool() noexcept : Core::PoolOf<NODE>()
        {
        }

        inline CxxPool(const CxxPool &other) : Core::PoolOf<NODE>()
        {
            try {
                for(const NODE *node=other.head;node;node=node->next)
                    this->store( new NODE(*other.head) );
            }
            catch(...) { free_(); throw; }
        }

        inline virtual ~CxxPool() noexcept
        {
            free_();
        }

        inline virtual void free() noexcept
        {
            free_();
        }

    private:
        Y_Disable_Assign(CxxPool);
        inline void free_() noexcept { while(size>0) delete this->query(); }
    };

}

#endif // !Y_Core_CxxPool_Included
