
#include "y/mpi++/api.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/random/fill.hpp"
#include "y/format/hexadecimal.hpp"
#include <cstring>

using namespace Yttrium;

namespace
{
    struct car {
        int   shifts;
        float topSpeed;

        inline friend
        std::ostream & operator<<(std::ostream &os, const car &self)
        {
            return os << "{" << self.shifts << "," << self.topSpeed << "}";
        }
    };
}

Y_UTEST(struct)
{
    MPI & mpi = MPI::Init(&argc,&argv);
    System::WallTime chrono;

    /* create a type for struct car */
    const int    nitems=2;
    int          blocklengths[2] = {1,1};
    MPI_Datatype types[2] = {MPI_INT, MPI_FLOAT};
    MPI_Datatype mpi_car_type;
    MPI_Aint     offsets[2];

    offsets[0] = offsetof(car, shifts);
    offsets[1] = offsetof(car, topSpeed);

    MPI_Type_create_struct(nitems, blocklengths, offsets, types, &mpi_car_type);
    MPI_Type_commit(&mpi_car_type);

    if(mpi.primary)
    {
        car send[2] = { {4,90.0f}, {6,130.0f} };
        Core::Display(std::cerr << "cars=",send,2) << std::endl;
        for(size_t rank=1;rank<mpi.size;++rank)
        {
            mpi.send(send,2,mpi_car_type,2*sizeof(car),rank);
            mpi.syn(rank);
        }
    }
    else
    {
        car recv[2];
        mpi.recv(recv,2,mpi_car_type,2*sizeof(car),0);
        Core::Display(std::cerr << "@" << mpi << ": ",recv,2) << std::endl;
        mpi.ack(0);
    }



    MPI_Type_free(&mpi_car_type);

    Y_MPI_ForEach(mpi,std::cerr << mpi
                  << " | send: " << mpi.sendRate.str(chrono)
                  << " | recv: " << mpi.recvRate.str(chrono)
                  << std::endl);

}
Y_UDONE()

