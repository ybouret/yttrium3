//! \file

#ifndef Y_Coven_Univocal_Included
#define Y_Coven_Univocal_Included 1

#include "y/apex/rational.hpp"

namespace Yttrium
{

    namespace Coven
    {

        namespace Pith
        {
            template <typename T,bool> struct NativeQueryAPI;

            template <typename T> struct NativeQueryAPI<T,true>
            {
                static inline SignType SignOf(const T &x) noexcept
                {
                    return x<0 ? Negative : ( 0< x ? Positive : __Zero__);
                }


                static inline apn AbsOf(const T &x)
                {
                    typedef typename UnsignedFor< sizeof(T) >::Alias::Type UType;
                    return 0<=x ? (UType)x : (UType)-x;
                }

            };

            template <typename T> struct NativeQueryAPI<T,false>
            {
                static inline SignType SignOf(const T &x) noexcept
                {
                    return (0<x) ? Positive : __Zero__;
                }

                static inline apn AbsOf(const T &x) { return x; }

            };

            template <typename T> struct QueryAPI
            {
                static inline SignType SignOf(const T &x) noexcept {
                    return NativeQueryAPI<T, IsSignedInt<T>::Value >::SignOf(x);
                }

                static inline apn AbsOf(const T x)
                {
                    return NativeQueryAPI<T, IsSignedInt<T>::Value >::AbsOf(x);
                }

            };

            template <> struct QueryAPI<apz>
            {
                static inline SignType SignOf(const apz &z) noexcept
                {
                    return z.s;
                }

                static inline apn AbsOf(const apz &z) { return z.n; }
            };

            template <> struct QueryAPI<apn>
            {
                static inline SignType SignOf(const apn &n) noexcept
                {
                    return n.is0() ? __Zero__ : Positive;
                }

                static inline  apn AbsOf(const apn &n)
                {
                    return n;
                }
            };


            template <typename T> inline
            SignType QuerySignOf(const T &x) noexcept { return QueryAPI<T>::SignOf(x); }

            template <typename T> inline
            apn QueryAbsOf(const T &x) noexcept { return QueryAPI<T>::AbsOf(x); }
        }

        struct Colinear
        {

            template <typename LHS, typename RHS> static inline
            bool Test( LHS &lhs, RHS &rhs )
            {
                assert(lhs.size() == rhs.size());

                size_t i = lhs.size();
                while(i>0)
                {
                    typename LHS::ConstType &l  = lhs[i];
                    typename RHS::ConstType &r  = rhs[i];
                    const SignType           ls = Pith::QuerySignOf(l);
                    const SignType           rs = Pith::QuerySignOf(r);

                    std::cerr << l << " / " << r << std::endl;
                    SignType rhoSign = Positive;
                    switch( Sign::Pair(ls,rs) )
                    {
                        case Sign::PZ:
                        case Sign::ZP:
                        case Sign::NZ:
                        case Sign::ZN:
                            return false; // zero against not zero

                        case Sign::ZZ: --i; continue; // zero against zero, shortcut

                        case Sign::PP:
                        case Sign::NN:
                            break;

                        case Sign::PN:
                        case Sign::NP:
                            rhoSign = Negative;
                            break;
                    }
                    assert(l>0);
                    assert(r>0);

                    const apn rhoNumer = Pith::QueryAbsOf(l);
                    const apn rhoDenom = Pith::QueryAbsOf(r);
                    apn::Reduce(Coerce(rhoNumer),Coerce(rhoDenom));
                    std::cerr << "rho: " << rhoSign << " * " << rhoNumer << " / " << rhoDenom << std::endl;

                    while(--i>0)
                    {
                        
                    }


                }


                return true;
            }

        };

    }

}

#endif // !Y_Coven_Univocal_Included
