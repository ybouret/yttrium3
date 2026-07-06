
#include "y/chemical/plexus/conservation/adjudicator.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        namespace Conservation
        {


            Adjudicator:: ~Adjudicator() noexcept
            {
            }

            Adjudicator:: Adjudicator(const Canon &source) :
            canon(source),
            n(canon.laws->size),
            m(canon.species->list->size),
            C(n,m)
            {
                
            }

        }
    }
}


