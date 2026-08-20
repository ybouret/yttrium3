
#include "y/mkl/tao/device.hpp"
#include "y/utest/run.hpp"

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
                typename TARGET,
                typename T,
                typename SOURCE,
                typename U>
                struct MulOps
                {
                    TARGET          * target;
                    const Matrix<T> * matrix;
                    SOURCE          * source;
                    Tiles1D         * tiles1d;

                    inline void set(Concurrent::Context &ctx)
                    {
                        assert(target);
                        assert(matrix);
                        assert(source);
                        assert(tiles1d);
                        
                        Y_Lock(ctx.sync);
                        std::cerr << "in " << ctx << std::endl;
                    }
                };

            }

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
                assert(target.size() == matrix.rows);
                assert(source.size() == matrix.cols);

                // get metrics
                const size_t nr = matrix.rows;
                const size_t nc = matrix.cols;

                // prepare device
                device.remap1d(nr).attach(addenda,nc);

                // prepare ops
                typedef Pith::MulOps<TARGET,T,SOURCE,U> Ops;
                Ops ops =
                {
                    & target, & matrix, & source , & device.tiles1d
                };

                (*device)( ops, & Ops :: set);


            }


        }

    }
}


#include "y/container/cxx/array.hpp"

using namespace Yttrium;

Y_UTEST(tao2)
{
    Concurrent::Engine seqEngine = Concurrent::SIMD::Sequential();
    Concurrent::Engine parEngine = Concurrent::SIMD::InParallel(0);

    MKL::Tao::Device seq(seqEngine);
    MKL::Tao::Device par(parEngine);

    const size_t nr = 4;
    const size_t nc = 3;
    Matrix<double>         A(nr,nc);
    CxxArray<double>       lhs(nr);
    CxxArray<double>       rhs(nc);
    Cameo::Addenda<double> addenda;

    MKL::Tao::Mul(seq,lhs,A,rhs,addenda);
    MKL::Tao::Mul(par,lhs,A,rhs,addenda);


}
Y_UDONE()

