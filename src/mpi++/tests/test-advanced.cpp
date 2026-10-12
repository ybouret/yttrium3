#include "y/mpi++/api.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/random/type-gen.hpp"
#include "y/system/rtti.hpp"
#include "y/container/sequence/vector.hpp"

using namespace Yttrium;

namespace
{
    template <typename T>
    static inline void testAdvanced(MPI &mpi, Random::CoinFlip &ran)
    {
        Y_MPI_Trace(mpi,(std::cerr << std::endl << "test<" << RTTI::Name<T>() << ">" << std::endl).flush());
        size_t items = 2 + ran.toss<size_t>(8);
        mpi.bcastSize(items,0);

        Vector<T> vec(WithAtLeast,items);
        if(mpi.primary)
        {
            for(size_t i=items;i>0;--i)
            {
                const T tmp = Random::Gen<T>::Get(ran);
                vec << tmp;
            }
            for(size_t rank=1;rank<mpi.size;++rank)
            {
                mpi.send( vec(), items, rank);
            }
        }
        else
        {
            vec.adjust(items);
            mpi.recv( vec(), items, 0);
        }
        Y_MPI_ForEach(mpi,(std::cerr << "@" << mpi << ": " << vec << std::endl).flush());

    }
}

Y_UTEST(advanced)
{
    MPI &      mpi = MPI::Init(&argc,&argv);
    Core::Rand ran;

    testAdvanced<short int>(mpi,ran);
    testAdvanced<String>(mpi,ran);
    testAdvanced<apn>(mpi,ran);
    testAdvanced<apz>(mpi,ran);
    testAdvanced<apq>(mpi,ran);
    testAdvanced< XReal<float> >(mpi,ran);
    testAdvanced< Complex<double> >(mpi,ran);
    testAdvanced< V3D<float> >(mpi,ran);


    Y_MPI_Trace(mpi,std::cerr << std::endl);
}
Y_UDONE()

