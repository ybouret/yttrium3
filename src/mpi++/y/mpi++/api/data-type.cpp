
#include "y/mpi++/api.hpp"




namespace Yttrium
{


    MPI:: DataType:: ~DataType() noexcept
    {
    }

    MPI::DataType:: DataType(const MPI_Datatype datatype, const size_t datasize) noexcept :
    CountedObject(),
    dt(datatype),
    sz(datasize)
    {

    }


}
