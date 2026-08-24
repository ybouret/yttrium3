//! \file

#ifndef Y_MKL_Tao2_Included
#define Y_MKL_Tao2_Included 1

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
                //! Handle Matrix/Vector common operations
                //
                //
                //______________________________________________________________
                template <
                typename TARGET,
                typename T,
                typename SOURCE,
                typename U>
                struct MulOps
                {
                    typedef Cameo::Addition<U> XAdd;    //!< alias
                    
                    TARGET                   * target;  //!< target vector address
                    const Matrix<T>          * matrix;  //!< matrix address
                    SOURCE                   * source;  //!< source vector address
                    Tiles1D                  * tiles1d; //!< device tiles1d address

                    //! target = matrix*source \param ctx context to fetch tile1d
                    inline void set(Concurrent::Context &ctx)
                    {
                        assert(target);
                        assert(matrix);
                        assert(source);
                        assert(tiles1d);

                        const Tile1D &tile = (*tiles1d)[ctx.indx];
                        XAdd &       xadd  = *tile.as<XAdd *>();

                        for(size_t irow=tile.offset,count=tile.length;count>0;--count,++irow)
                            (*target)[irow] = matrix->mul_(irow,xadd,*source);

                    }

                    //! target = matrix*source + rhs \param ctx context to fetch tile1d \param rhs to add
                    template <typename RHS>
                    inline void add(Concurrent::Context &ctx, RHS &rhs)
                    {
                        assert(target);
                        assert(matrix);
                        assert(source);
                        assert(tiles1d);

                        const Tile1D &tile = (*tiles1d)[ctx.indx];
                        XAdd &       xadd  = *tile.as<XAdd *>();
                        for(size_t irow=tile.offset,count=tile.length;count>0;--count,++irow)
                            (*target)[irow] = matrix->muladd_(irow,xadd,*source,rhs);

                    }

                    //! target = matrix*source-rhs \param ctx context to fetch tile1d \param rhs to sub
                    template <typename RHS>
                    inline void sub(Concurrent::Context &ctx, RHS &rhs)
                    {
                        assert(target);
                        assert(matrix);
                        assert(source);
                        assert(tiles1d);

                        const Tile1D &tile = (*tiles1d)[ctx.indx];
                        XAdd &       xadd  = *tile.as<XAdd *>();
                        for(size_t irow=tile.offset,count=tile.length;count>0;--count,++irow)
                            (*target)[irow] = matrix->mulsub_(irow,xadd,*source,rhs);

                    }

                };


            }

            //! helper code to prepare tiles for MulOps
#define Y_MKL_TAO2_SETUP( CODE )                        \
/**/    assert(target.size() == matrix.rows);           \
/**/    assert(source.size() == matrix.cols);           \
/*      ** get metric                                */ \
/**/    const size_t nr = matrix.rows;                  \
/**/    const size_t nc = matrix.cols;                  \
/*      **  prepare device                           */ \
/**/    device.remap1d(nr).attach(addenda,nc);          \
/*      ** prepare ops                               */ \
/**/    typedef Pith::MulOps<TARGET,T,SOURCE,U> MulOps; \
/**/    MulOps ops =  {                                 \
/**/        &target, &matrix, &source, &device.tiles1d  \
/**/    };                                              \
/**/    (*device) CODE


            //__________________________________________________________________
            //
            //
            //
            //! Matrix/Vector thru Concurrent::SIMD
            /**
             \param device  handle parallelism
             \param target  target vector
             \param matrix  matrix
             \param source  source vector
             \param addenda collection of Cameo::Addition to populate Device
             */
            //
            //__________________________________________________________________
            template <
            typename TARGET,
            typename T,
            typename SOURCE,
            typename U>
            inline void Mul(Device            & device,
                            TARGET            & target,
                            const Matrix<T>   & matrix,
                            SOURCE            & source,
                            Cameo::Addenda<U> & addenda)
            {
                Y_MKL_TAO2_SETUP( (ops, & MulOps::set) );
            }


            //__________________________________________________________________
            //
            //
            //
            //! Matrix/Vector multiplication and addition thru Concurrent::SIMD
            /**
             \param device  handle parallelism
             \param target  target vector
             \param matrix  matrix
             \param source  source vector
             \param rhs     vector to add
             \param addenda collection of Cameo::Addition to populate Device
             */
            //
            //__________________________________________________________________
            template <
            typename TARGET,
            typename T,
            typename SOURCE,
            typename U,
            typename RHS>
            inline void MulAdd(Device            & device,
                               TARGET            & target,
                               const Matrix<T>   & matrix,
                               SOURCE            & source,
                               RHS               & rhs,
                               Cameo::Addenda<U> & addenda)
            {
                Y_MKL_TAO2_SETUP(( ops, & MulOps :: template add<RHS>, rhs) );
            }

            //__________________________________________________________________
            //
            //
            //
            //! Matrix/Vector multiplication and subtraction thru Concurrent::SIMD
            /**
             \param device  handle parallelism
             \param target  target vector
             \param matrix  matrix
             \param source  source vector
             \param rhs     vector to sub
             \param addenda collection of Cameo::Addition to populate Device
             */
            //
            //__________________________________________________________________
            template <
            typename TARGET,
            typename T,
            typename SOURCE,
            typename U,
            typename RHS>
            inline void MulSub(Device            & device,
                               TARGET            & target,
                               const Matrix<T>   & matrix,
                               SOURCE            & source,
                               RHS               & rhs,
                               Cameo::Addenda<U> & addenda)
            {
                Y_MKL_TAO2_SETUP(( ops, & MulOps :: template sub<RHS>, rhs) );
            }



        }

    }
}

#endif // !Y_MKL_Tao2_Included

