
#include "y/mpi++/api.hpp"




namespace Yttrium
{
    MPI::DataType:: DataType(const DataType &other) noexcept :
    dt(other.dt),
    sz(other.sz)
    {
        
    }

    MPI:: DataType:: ~DataType() noexcept
    {
    }

    MPI::DataType:: DataType(const MPI_Datatype datatype, const size_t datasize) noexcept :
    dt(datatype),
    sz(datasize)
    {

    }


}
