
#include "y/mpi++/api.hpp"
#include "y/utest/run.hpp"
#include "y/format/hexadecimal.hpp"
#include "y/check/crc32.hpp"
#include <cstring>

using namespace Yttrium;

namespace
{
    struct Car {
        short   shifts;
        float   topSpeed;

        inline friend
        std::ostream & operator<<(std::ostream &os, const Car &self)
        {
            return os << "{" << self.shifts << "," << self.topSpeed << "}";
        }
    };
}

Y_UTEST(defined)
{
    MPI &             mpi = MPI::Init(&argc,&argv);
    System::WallTime  chrono;


#if 0
    const int    nitems=2;
    int          blocklengths[2] = {1,1};
    MPI_Datatype types[2] = {MPI_SHORT, MPI_FLOAT};
    MPI_Aint     offsets[2];

    offsets[0] = offsetof(Car, shifts);
    offsets[1] = offsetof(Car, topSpeed);
    MPI::DataType dt(mpi,nitems,blocklengths,offsets,types);
    Y_MPI_Trace(mpi,std::cerr << "dt.bytes=" << dt.bytes << std::endl);
#endif

    mpi.declAsPair<Car>(typeid(short), offsetof(Car, shifts),
                        typeid(float), offsetof(Car, topSpeed) );

    const MPI::DataType &dt = mpi.getDataTypeOf<Car>();
    if(mpi.primary) Y_PRINTV(dt.bytes);
    
    static const size_t NCAR = 3;

    if(mpi.primary)
    {
        Car            send[NCAR] = { {4,90.0f}, {6,130.0f}, {3,50.0f} };
        const uint32_t crc        = Y_CRC32(send);
        Core::Display(std::cerr << "cars =",send,NCAR) << " | crc = " << Hexadecimal(crc) << std::endl;
        for(size_t rank=1;rank<mpi.size;++rank)
        {
            mpi.send(send,NCAR,dt.value,NCAR*dt.bytes,rank);
            mpi.syn(rank);
        }
    }
    else
    {
        Car recv[NCAR]; Y_BZero(recv);
        mpi.recv(recv,NCAR,dt.value,NCAR*dt.bytes,0);
        const uint32_t crc = Y_CRC32(recv);

        Core::Display(std::cerr << "@" << mpi << ": ",recv,NCAR) << " | crc = " << Hexadecimal(crc) << std::endl;
        mpi.ack(0);
    }

    Y_MPI_ForEach(mpi,std::cerr << mpi
                  << " | send: " << mpi.sendRate.str(chrono)
                  << " | recv: " << mpi.recvRate.str(chrono)
                  << std::endl);

}
Y_UDONE()
