
//! \file

#ifndef Y_Apex_Simplify_Included
#define Y_Apex_Simplify_Included 1

#include "y/apex/integer.hpp"
#include "y/container/cxx/light-array.hpp"
namespace Yttrium
{
    namespace Apex
    {
        inline const Natural &GetN(const Natural &n) noexcept { return   n; } //!< \return natural part \param n natural
        inline const Natural &GetN(const Integer &z) noexcept { return z.n; } //!< \return natural part \param z integer


        //______________________________________________________________________
        //
        //
        //! Simplification of data over denominator
        //
        //______________________________________________________________________
        struct Simplify
        {
            //! \param array array of apn or apz \param denom apn or apz
            template <typename ARRAY, typename T> static
            inline void Array( ARRAY &array, T & denom )
            {
                const size_t   l = array.size();
                const Natural &D = GetN(denom); if(D.bits()<=1) return;
                Natural        G = 0;

                for(size_t i=l;i>0;--i)
                {
                    const Natural &N = GetN(array[i]);
                    if(N.is0()) continue;
                    Natural g = Natural::GCD(N,D);
                    if(g.bits()>0)
                    {
                        if(G.is0())
                            G.xch(g);
                        else
                        {
                            if(g<G) G.xch(g);
                        }
                    }
                }

                if(G>1)
                {
                    Coerce(D) /= G;
                    for(size_t i=l;i>0;--i)
                    {
                        const Natural &N = GetN(array[i]);
                        if(N.is0()) continue;
                        Coerce(N) /= G;
                    }
                }
            }

            //! \param M matrix of apn or apz \param denom apn or apz
            template <typename MATRIX, typename T> static
            inline void Matrix( MATRIX &M, T & denom)
            {
                LightArray<typename MATRIX::Type> array = M.asArray();
                Array(array,denom);
            }

        };

    }
}

#endif // !Y_Apex_Simplify_Included

