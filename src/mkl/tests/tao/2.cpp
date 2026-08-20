
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
                    typedef Cameo::Addition<U> XAdd;

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

                        const Tile1D &tile = (*tiles1d)[ctx.indx];
                        XAdd &       xadd  = *tile.as<XAdd *>();
                        //{ Y_Lock(ctx.sync); std::cerr << "in " << ctx << " => " << tile << std::endl; }

                        for(size_t irow=tile.offset,count=tile.length;count>0;--count,++irow)
                            (*target)[irow] = matrix->mul_(irow,xadd,*source);

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
                typedef Pith::MulOps<TARGET,T,SOURCE,U> MulOps;
                MulOps ops =
                {
                    & target, & matrix, & source , & device.tiles1d
                };

                // apply ops on each tile
                (*device)( ops, & MulOps :: set);
            }


        }

    }
}


#include "y/container/cxx/array.hpp"
#include "y/core/rand.hpp"
#include "y/random/type-gen.hpp"

using namespace Yttrium;

Y_UTEST(tao2)
{
    Concurrent::Engine seqEngine = Concurrent::SIMD::Sequential();
    Concurrent::Engine parEngine = Concurrent::SIMD::InParallel(0);

    MKL::Tao::Device seq(seqEngine);
    MKL::Tao::Device par(parEngine);
    Core::Rand       ran;

    const size_t nr = 4;
    const size_t nc = 3;
    Matrix<double>         A(nr,nc);
    CxxArray<double>       lhs(nr);
    CxxArray<double>       lhsSeq(nr);
    CxxArray<double>       lhsPar(nr);
    CxxArray<double>       rhs(nc);
    Cameo::Addenda<double> addenda;

    Random::Generate::Array(ran,rhs);
    Random::Generate::Matrix(ran,A);

    std::cerr << "A=" << A << std::endl;
    std::cerr << "rhs=" << rhs << std::endl;
    std::cerr << std::endl;

    lhs.ld(0); A.mul(lhs,rhs);
    std::cerr << "lhs   =" << lhs << std::endl;

    lhsSeq.ld(0); MKL::Tao::Mul(seq,lhsSeq,A,rhs,addenda); std::cerr << "lhsSeq=" << lhsSeq << std::endl;
    lhsPar.ld(0); MKL::Tao::Mul(par,lhsPar,A,rhs,addenda); std::cerr << "lhsPar=" << lhsPar << std::endl;


}
Y_UDONE()

