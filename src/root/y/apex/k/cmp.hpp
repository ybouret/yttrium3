
//! \file

#ifndef Y_Apex_KegCmp_Included
#define Y_Apex_KegCmp_Included 1

#include "y/apex/k/keg.hpp"


namespace Yttrium
{
    namespace Apex
    {

        struct KegCmp
        {

            template <typename WORD> static inline
            SignType Result(const WORD * const lhs,
                            const size_t       nl,
                            const WORD * const rhs,
                            const size_t       nr) noexcept
            {
                if(nl<=0)
                {
                    if(nr<=0)
                    {
                        return __Zero__;
                    }
                    else
                    {
                        assert(rhs); assert(rhs[nr-1]>0);
                        return Negative;
                    }
                }
                else
                {
                    assert(nl>0); assert(lhs); assert(lhs[nl-1]>0);
                    if(nr<=0)
                    {
                        return Positive;
                    }
                    else
                    {
                        assert(rhs); assert(rhs[nr-1]>0);
                        switch( Sign::Of(nl,nr) )
                        {
                            case Negative: return Negative;
                            case Positive: return Positive;
                            case __Zero__:
                                break;
                        }
                        assert(nl==nr);
                        size_t       n = nl;
                        const WORD * l = lhs+n;
                        const WORD * r = rhs+n;
                        for(;n>0;--n)
                        {
                            switch( Sign::Of(*(--l),*(--r)) )
                            {
                                case __Zero__: continue;
                                case Positive: return Positive;
                                case Negative: return Negative;
                            }
                        }
                        return __Zero__;
                    }

                }
            }

        };

    }

}

#endif // !Y_Apex_KegCmp_Included

