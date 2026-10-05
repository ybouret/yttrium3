
#include "y/mpi++/carrier/scalar.hpp"

namespace Yttrium
{

    MPI::ScalarCarrier:: ScalarCarrier(const MPI::DataType &mdt) noexcept :
    Carrier(),
    dataType(mdt)
    {}

    MPI::ScalarCarrier:: ~ScalarCarrier() noexcept
    {

    }

    void MPI::ScalarCarrier:: send(MPI &              mpi,
                                   const void * const entry,
                                   const size_t       items,
                                   const size_t       target,
                                   const int          tag)
    {
        mpi.send(entry,items,dataType.value,dataType.bytes*items,target,tag);
    }

    void MPI::ScalarCarrier:: recv(MPI &         mpi,
                                   void * const  entry,
                                   const size_t  items,
                                   const size_t  source,
                                   const int     tag)
    {
        mpi.recv(entry,items,dataType.value,dataType.bytes*items,source,tag);
    }

}
