
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
                //______________________________________________________________
                //
                //
                //
                //! embedding data to invoke matrix multiplications
                //
                //
                //______________________________________________________________
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

                    //! lhs*rhs on given tile \param ctx contex to fetch tile
                    inline void straight(Concurrent::Context &ctx)
                    {
                        assert(target); assert(lhs); assert(rhs); assert(tiles2d);

                        const Tile2D &tile = (*tiles2d)[ctx.indx];
                        XAdd &       xadd  = *tile.as<XAdd *>();
                        const size_t nx    = lhs->cols;
                        for(size_t t=tile.span;t>0;--t)
                        {
                            const Tile2D::Segment s  = tile[t];
                            const size_t          i  = s.start.y;
                            Writable<T>          &Ai = (*target)[i];
                            for(size_t j=s.start.x,n=s.width;n>0;--n,++j)
                            {
                                xadd.ldz();
                                for(size_t k=nx;k>0;--k)
                                    xadd.addProd( (*lhs)[i][k], (*rhs)[k][j] );
                                Ai[j] =  xadd();
                            }
                        }
                    }

                };
            }

            //__________________________________________________________________
            //
            //! Matrix/Matrix multiplication
            /**
             \param device  tiles and parallelism management
             \param target  target matrix
             \param lhs     lhs matrix
             \param rhs     rhs matrix
             \param addenda Cameo::Addenda for tiles
             */
             //__________________________________________________________________
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
                //--------------------------------------------------------------
                //
                // sanity check
                //
                //--------------------------------------------------------------
                assert(lhs.rows==target.rows);
                assert(rhs.cols==target.cols);
                assert(lhs.cols==rhs.rows);
                assert(target.rows>0);
                assert(target.cols>0);
                assert(lhs.cols>0);

                //--------------------------------------------------------------
                //
                // prepare tiles
                //
                //--------------------------------------------------------------
                device.remapT2D(target).attach(addenda,lhs.cols);

                //--------------------------------------------------------------
                //
                // prepare ops and use device
                //
                //--------------------------------------------------------------
                typedef Pith::MMulOps<T, LHS, RHS, U> MulOps;
                MulOps ops = {
                    &target, &lhs, &rhs, & device.tiles2d
                };
                (*device)( ops, & MulOps::straight );
            }

        }


        namespace Tao
        {
            namespace Pith
            {
                //______________________________________________________________
                //
                //
                //
                //! embedding data to invoke Gram matrix
                //
                //
                //______________________________________________________________
                template <
                typename T,
                typename U,
                typename V> struct GramOps
                {
                    typedef Cameo::Addition<V> XAdd; //!< alis

                    Matrix<T>       * target; //!< target squared matrix
                    const Matrix<U> * source; //!< source matrix
                    UDTS            * udts;   //!< tiles

                    //! source*source' on given tile \param ctx contex to fetch tile
                    inline void run(Concurrent::Context &ctx)
                    {
                        assert(target); assert(source); assert(udts);

                        const UDT &udt  = (*udts)[ctx.indx];
                        XAdd      &xadd = *udt.as<XAdd *>();
                        for(size_t i=1;i<=udt.span;++i)
                        {

                            const UDT::Segment s = udt[i];
                            MatrixCoord        p = s.start;
                            Writable<T>       &Ai = (*target)[p.r];
                            for(size_t jj=s.width;jj>0;--jj,++p.c)
                            {
                                const T & Aij = (Ai[p.c] = xadd.dot((*source)[p.r],(*source)[p.c]));
                                if(p.c!=p.r)
                                    (*target)[p.c][p.r] = Aij;
                            }

                        }
                    }

                };
            }

            //__________________________________________________________________
            //
            //! Gram Matrix computation
            /**
             \param device  tiles and parallelism management
             \param target  target square matrix
             \param source  source matrix
             \param addenda Cameo::Addenda for tiles
             */
            //__________________________________________________________________
            template <
            typename T,
            typename U,
            typename V> inline
            void Gram(Device            & device,
                      Matrix<T>         & target,
                      const Matrix<U>   & source,
                      Cameo::Addenda<V> & addenda)
            {
                assert(target.isSquare());
                assert(source.rows == target.rows);

                device.remapUDT(target.rows).attach(addenda,source.cols);

                typedef Pith::GramOps<T,U,V> GramOps;
                GramOps ops = { & target, & source, & device.udts };
                (*device)( ops, & GramOps:: run );
            }
        }

    }

}

#endif // !Y_MKL_Tao3_Included

