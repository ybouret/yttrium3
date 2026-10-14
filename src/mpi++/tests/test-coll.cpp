#include "y/mpi++/api.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/random/fill.hpp"
#include "y/format/hexadecimal.hpp"
#include <cstring>

using namespace Yttrium;

Y_UTEST(coll)
{
    Core::Rand ran;
    MPI & mpi = MPI::Init(&argc,&argv);


    {
        int value = 0;
        if(mpi.primary)
            value = 7;
        Y_MPI_PrintAll(mpi,std::cerr,mpi << ": value=" << value);

        mpi.bcastScalar(value,0);
        Y_MPI_PrintAll(mpi,std::cerr,mpi << ": value=" << value);
        Y_MPI_Endl(mpi,std::cerr);
    }

    {
        char buffer[16];
        if(mpi.primary) Random::FillWith(ran,buffer,sizeof(buffer)); else memset(buffer,0,sizeof(buffer));
        Y_MPI_ForEach(mpi, (Hexadecimal::Display(std::cerr << mpi << ":" ,buffer,sizeof(buffer)) << std::endl).flush());
        mpi.bcastBytes(buffer,sizeof(buffer),0);
        Y_MPI_PrintOne(mpi,std::cerr,"broadcasting bytes...");
        Y_MPI_ForEach(mpi, (Hexadecimal::Display(std::cerr << mpi << ":" ,buffer,sizeof(buffer)) << std::endl).flush() );
        Y_MPI_Endl(mpi,std::cerr);
    }

    {
        size_t sz = 00;
        if(mpi.primary) sz = 1001;
        Y_MPI_PrintAll(mpi,std::cerr,mpi << ": sz=" << sz);
        Y_MPI_PrintOne(mpi,std::cerr,"broadcasting size...");
        mpi.bcastSize(sz,0);
        Y_MPI_PrintAll(mpi,std::cerr,mpi << ": sz=" << sz);
        Y_MPI_Endl(mpi,std::cerr);
    }


    Y_MPI_Endl(mpi,std::cerr);


}
Y_UDONE()

