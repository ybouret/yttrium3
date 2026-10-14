
#include "y/mpi++/api.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(init)
{
    MPI & mpi = MPI::Init(&argc,&argv);
    if(mpi.primary)
    {
        std::cerr << "initialized from primary: " << mpi << std::endl;
        std::cerr << std::endl;
        
        try
        {
            throw MPI::Exception(MPI_ERR_IO, "test from %s", test);
        }
        catch(const Exception &excp)
        {
            excp.display(std::cerr);
        }
        std::cerr.flush();
    }

    mpi.barrier();
    Y_MPI_PrintAll(mpi,std::cerr,mpi);

    if(mpi.primary)
    {
        std::cerr << "Table:" << std::endl;
        for(MPI::DataType::Table::ConstIterator it=mpi.dataTypes.begin();it!=mpi.dataTypes.end();++it)
        {
            std::cerr << it->key() << " : sizeof=" << (**it).bytes << std::endl;
        }
    }


}
Y_UDONE()

