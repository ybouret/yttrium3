
//! \file

#ifndef Y_Apex_KegCmp_Included
#define Y_Apex_KegCmp_Included 1

#include "y/apex/k/keg.hpp"


namespace Yttrium
{
    namespace Apex
    {

        //! comparison algorithm
        struct KegCmp
        {
            //! compare two arrays of valid words
            /**
             \param lhs lhs words
             \param nl  lhs count
             \param rhs rhs words
             \param nr  rhs count
             \return comparison result
             */
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

            //! helper
            /**
             \param lhs compatible object
             \param rhs compatible object
             \return comparison
             */
            template <typename LHS, typename RHS> static inline
            SignType ResultFor(LHS &lhs, RHS &rhs) noexcept
            {
                return Result(lhs.word,lhs.words,rhs.word,rhs.words);
            }

        };

    }

}

#endif // !Y_Apex_KegCmp_Included

