
#include "y/mpi++/carrier/scalar.hpp"
#include "y/mpi++/carrier/vector.hpp"

#include "y/mpi++/carrier/serial.hpp"

#include "y/random/type-gen.hpp"

#include "y/utest/run.hpp"
#include <cstring>



using namespace Yttrium;

#include "y/format/hexadecimal.hpp"
#include "y/core/rand.hpp"
#include "y/system/rtti.hpp"

namespace
{
    template <typename T> static inline
    void testSerial(MPI &mpi, Random::CoinFlip &ran)
    {
        Y_MPI_Trace(mpi, std::cerr << std::endl << "testSerial<" << RTTI::Name<T>() << ">" << std::endl);
        size_t       items = 5 + ran.toss<size_t>(5);
        mpi.bcastSize(items,0);

        Vector<T>             vec(WithAtLeast,items);
        MPI::SerialCarrier<T> cr(1024);
        if(mpi.primary)
        {
            for(size_t i=items;i>0;--i)
            {
                const T tmp  = Random::Gen<T>::Get(ran);
                vec << tmp;
            }
            Y_ASSERT(items==vec.size());
            for(size_t i=1;i<mpi.size;++i)
            {
                cr.send(mpi,vec(),items,i,0x07);
            }
        }
        else
        {
            const T      empty;
            vec.adjust(items,empty);
            Y_ASSERT(items==vec.size());
            cr.recv(mpi,vec(),items,0,0x07);
        }

        Y_MPI_ForEach(mpi, std::cerr << "@" << mpi << ": " << vec << std::endl);
    }
}


Y_UTEST(carrier)
{
    MPI &      mpi = MPI::Init(&argc,&argv);
    Core::Rand ran;

#if 0
    MPI::SerialCarrier<String> cr(100);
    String                     str;
    if(mpi.primary)
    {
        str = "Hello, World!";
        for(size_t rank=1;rank<mpi.size;++rank)
        {
            cr.send(mpi,&str,1,rank,7);
        }
    }
    else
    {
        cr.recv(mpi,&str,1,0,7);
    }

    Y_MPI_ForEach(mpi, std::cerr << "@" << mpi << " : length=" << cr.buffer.length() << " | crc " << Hexadecimal(cr.buffer.crc()) << " => '" << str << "'" << std::endl );
#endif


    testSerial<String>(mpi,ran);
    testSerial<apn>(mpi,ran);
    testSerial<apz>(mpi,ran);
    testSerial<apq>(mpi,ran);


}
Y_UDONE()

