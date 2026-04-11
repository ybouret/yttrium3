#include "y/apex/n/code.hpp"
#include "y/system/exception.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Apex
    {
        void Natural:: Division(Natural * const quot,
                                Natural * const rem,
                                const Natural & numer,
                                const Natural & denom)
        {

            const KegType &D = *static_cast<const KegType *>(denom.code);
            switch( Cmp(numer,denom) )
            {
                case Negative:
                    assert(numer<denom);
                    if(quot) quot->ldz();
                    if(rem)  *rem = numer;
                    break;

                case __Zero__:
                    if(D.words<=0) throw Libc::Exception(EDOM,"%s 0/0", CallSign);
                    if(quot) *quot =   1;
                    if(rem)   rem->ldz();
                    return;
            }
        }
    }
}
