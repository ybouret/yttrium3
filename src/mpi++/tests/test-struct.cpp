
#include "y/mpi++/api.hpp"
#include "y/utest/run.hpp"
#include "y/format/hexadecimal.hpp"
#include "y/check/crc32.hpp"
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
    MPI_Datatype mpi_car_type;

    {
        const int    nitems=2;
        int          blocklengths[2] = {1,1};
        MPI_Datatype types[2] = {MPI_INT, MPI_FLOAT};
        MPI_Aint     offsets[2];

        offsets[0] = offsetof(car, shifts);
        offsets[1] = offsetof(car, topSpeed);

        Y_MPI_Call( MPI_Type_create_struct(nitems, blocklengths, offsets, types, &mpi_car_type) );
        Y_MPI_Call( MPI_Type_commit(&mpi_car_type) );

        Y_BZero(blocklengths);
        Y_BZero(types);
        Y_BZero(offsets);

    }
    
    static const size_t NCAR = 3;

    if(mpi.primary)
    {
        car            send[NCAR] = { {4,90.0f}, {6,130.0f}, {3,50.0f} };
        const uint32_t crc        = Y_CRC32(send);
        Core::Display(std::cerr << "cars =",send,NCAR) << " | crc = " << Hexadecimal(crc) << std::endl;
        for(size_t rank=1;rank<mpi.size;++rank)
        {
            mpi.send(send,NCAR,mpi_car_type,NCAR*sizeof(car),rank);
            mpi.syn(rank);
        }
    }
    else
    {
        car recv[NCAR];
        mpi.recv(recv,NCAR,mpi_car_type,NCAR*sizeof(car),0);
        const uint32_t crc = Y_CRC32(recv);

        Core::Display(std::cerr << "@" << mpi << ": ",recv,NCAR) << " | crc = " << Hexadecimal(crc) << std::endl;
        mpi.ack(0);
    }



    (void) MPI_Type_free(&mpi_car_type);

    Y_MPI_ForEach(mpi,std::cerr << mpi
                  << " | send: " << mpi.sendRate.str(chrono)
                  << " | recv: " << mpi.recvRate.str(chrono)
                  << std::endl);

}
Y_UDONE()

