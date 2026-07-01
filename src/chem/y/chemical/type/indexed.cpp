

#include "y/chemical/type/indexed.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        Indexed:: Indexed(const size_t i) :
        Entity(),
        indx()
        {
            setup(i);
        }


        Indexed:: ~Indexed() noexcept
        {
        }

        Indexed:: Indexed(const String &_, const size_t i) :
        Entity(_),
        indx()
        {
            setup(i);
        }

        void Indexed:: setup(const size_t i) noexcept
        {
            assert(i>0);
            size_t * const arr = Coerce(indx);
            memset(arr,0,sizeof(indx));
            //for(unsigned j=0;j<Levels;++j) arr[j] = i;
            arr[0] = i;
        }

        SignType Indexed:: TopLevelCompare(const Indexed &lhs, const Indexed &rhs) noexcept
        {
            return Sign::Of(lhs.indx[TopLevel],rhs.indx[TopLevel]);
        }

    }

}


