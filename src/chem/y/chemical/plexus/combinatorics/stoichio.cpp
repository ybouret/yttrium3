
#include "y/chemical/plexus/combinatorics/stoichio.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        Stoichio:: ~Stoichio() noexcept
        {}

        Stoichio:: Stoichio(const iArray &arr) :
        Object(),
        iArray(CopyOf,arr),
        next(0),
        prev(0)
        {
        }

        StoichioDB:: ~StoichioDB() noexcept
        {
        }


        StoichioDB:: StoichioDB() noexcept : list()
        {
        }

        Y_Proxy_Impl(StoichioDB,list)

        bool StoichioDB:: mayUse(const iArray &rhs)  
        {
            for(const Stoichio *node=list.head;node;node=node->next)
            {
                const Stoichio &lhs = *node;
                if( lhs == rhs )
                    return false;
            }

            list.pushTail(new Stoichio(rhs));
            return true;
        }

    }

}
