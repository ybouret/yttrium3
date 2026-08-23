
//! \file

#ifndef Y_MKL_Tao3_Included
#define Y_MKL_Tao3_Included 1

#include "y/mkl/tao/device.hpp"
#include "y/container/matrix.hpp"

namespace Yttrium
{
    namespace MKL
    {

        namespace Tao
        {

            namespace Pith
            {
                template <
                typename T,
                typename LHS,
                typename RHS,
                typename U> struct MMulOps
                {
                    typedef Cameo::Addition<U> XAdd;    //!< alias
                    
                    Matrix<T>                * target;  //!< target matrix
                    LHS                      * lhs;     //!< lhs matrix
                    RHS                      * rhs;     //!< rhs matrix
                    Tiles2D                  * tiles2d; //!< device tiles2d address

                    inline void straight(Concurrent::Context &ctx)
                    {
                        assert(target); assert(lhs); assert(rhs); assert(tiles2d);
                        const Tile2D &tile = (*tiles2d)[ctx.indx];
                        XAdd &       xadd  = *tile.as<XAdd *>();
                        for(size_t k=tile.span;k>0;--k)
                        {
                            const Segment s = tile[k];
                        }

                    }

                };
            }


            template <
            typename T,
            typename LHS,
            typename RHS,
            typename U> inline
            void MMul(Device    &         device,
                      Matrix<T> &         target,
                      LHS       &         lhs,
                      RHS       &         rhs,
                      Cameo::Addenda<U> & addenda)
            {
                assert(lhs.rows==target.rows);
                assert(rhs.cols==target.cols);
                assert(lhs.cols==rhs.rows);
                const size_t nr = target.rows; assert(nr>0);
                const size_t nc = target.cols; assert(nc>0);
                const size_t nx = lhs.cols;
                device.remap2d(target).attach(addenda,nx);

                typedef Pith::MMulOps<T, LHS, RHS, U> MulOps;
                MulOps ops = {
                    &target, &lhs, &rhs, & device.tiles2d
                };

                (*device)( ops, & MulOps::straight );
                

#if 0
                const size_t nx   = lhs.cols;
                xadd.ldz();
                for(size_t k=nx;k>0;--k)
                    xadd.addProd(lhs[i][k], rhs[k][j]);
                return xadd();
#endif
            }

        }

    }

}

#endif // !Y_MKL_Tao3_Included

