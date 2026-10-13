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
        Vector<T> here(WithAtLeast,items);
        if(mpi.primary)
        {
            for(size_t i=items;i>0;--i)
            {
                const T tmp = Random::Gen<T>::Get(ran);
                here << tmp;
            }
            for(size_t rank=1;rank<mpi.size;++rank)
            {
                mpi.send( here(), items, rank);
            }
        }
        else
        {
            here.adjust(items);
            mpi.recv( here(), items, 0);
        }
        Y_MPI_ForEach(mpi,(std::cerr << "@" << mpi << ": " << here << std::endl).flush());

        for(size_t i=1;i<=items;++i)
            here[i]  = Random::Gen<T>::Get(ran);

        Vector<T> peer(WithAtLeast,items);
        peer.adjust(items);
        mpi.sendrecv(here(),items,mpi.prevRank(),
                     peer(),items,mpi.nextRank());

        Y_MPI_ForEach(mpi,(std::cerr << "@" << mpi << ": " << here << " | " << peer << std::endl).flush());



    }
}

Y_UTEST(advanced)
{
    MPI &      mpi = MPI::Init(&argc,&argv);
    Core::Rand ran;

    testAdvanced<short int>(mpi,ran);
    testAdvanced< XReal<float> >(mpi,ran);
    testAdvanced< Complex<double> >(mpi,ran);
    testAdvanced< V3D<float> >(mpi,ran);
    
    Y_MPI_Trace(mpi,std::cerr << std::endl);
    return 0;

    testAdvanced<String>(mpi,ran);
    testAdvanced<apn>(mpi,ran);
    testAdvanced<apz>(mpi,ran);
    testAdvanced<apq>(mpi,ran);


}
Y_UDONE()

