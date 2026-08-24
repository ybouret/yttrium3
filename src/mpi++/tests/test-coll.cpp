

#include "y/mpi++/api.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/random/fill.hpp"
#include "y/format/hexadecimal.hpp"

using namespace Yttrium;

Y_UTEST(coll)
{
    Core::Rand ran;
    MPI & mpi = MPI::Init(&argc,&argv);


    {
        int value = 0;
        if(mpi.primary)
            value = 7;
        Y_MPI_ForEach(mpi,std::cerr << mpi << ": value=" << value << std::endl);
        mpi.bcast1(value,0);
        Y_MPI_ForEach(mpi,std::cerr << mpi << ": value=" << value << std::endl);
        Y_MPI_Trace(mpi,std::cerr << std::endl);
    }

    {
        char buffer[16];
        if(mpi.primary) Random::FillWith(ran,buffer,sizeof(buffer)); else memset(buffer,0,sizeof(buffer));
        Y_MPI_ForEach(mpi, Hexadecimal::Display(std::cerr << mpi << ":" ,buffer,sizeof(buffer)) << std::endl);
        mpi.bcastBytes(buffer,sizeof(buffer),0);
        Y_MPI_Trace(mpi,std::cerr << "bcast..." << std::endl);
        Y_MPI_ForEach(mpi, Hexadecimal::Display(std::cerr << mpi << ":" ,buffer,sizeof(buffer)) << std::endl);
        Y_MPI_Trace(mpi,std::cerr << std::endl);
    }

    {
        size_t sz = 00;
        if(mpi.primary) sz = 1001;
        Y_MPI_ForEach(mpi,std::cerr << mpi << ": sz=" << sz << std::endl);
        mpi.bcastSize(sz,0);
        Y_MPI_Trace(mpi,std::cerr << "bcastSize..." << std::endl);
        Y_MPI_ForEach(mpi,std::cerr << mpi << ": sz=" << sz << std::endl);
        Y_MPI_Trace(mpi,std::cerr << std::endl);
    }


    if(mpi.primary)
    {
        std::cerr << std::endl;
    }

}
Y_UDONE()

