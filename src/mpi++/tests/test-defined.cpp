
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



    mpi.declAsPair<Car>(typeid(short), offsetof(Car, shifts),
                        typeid(float), offsetof(Car, topSpeed) );

    const MPI::DataType &dt = mpi.getDataTypeOf<Car>();
    Y_MPI_Trace(mpi,Y_PRINTV(dt.bytes));

    static const size_t NCAR = 3;

    if(mpi.primary)
    {
        Car            send[NCAR] = { {4,90.0f}, {6,130.0f}, {3,50.0f} };
        const uint32_t crc        = Y_CRC32(send);
        (Core::Display(std::cerr << "cars =",send,NCAR) << " | crc = " << Hexadecimal(crc) << std::endl).flush();
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

        (Core::Display(std::cerr << "@" << mpi << ": ",recv,NCAR) << " | crc = " << Hexadecimal(crc) << std::endl).flush();
        mpi.ack(0);
    }

    Y_MPI_PrintAll(mpi,std::cerr,mpi
                  << " | send: " << mpi.sendRate.str(chrono)
                  << " | recv: " << mpi.recvRate.str(chrono)
                  );

}
Y_UDONE()
