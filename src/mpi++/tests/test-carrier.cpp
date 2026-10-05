
#include "y/mpi++/carrier/scalar.hpp"
#include "y/mpi++/carrier/vector.hpp"

#include "y/mpi++/carrier/serial.hpp"


#include "y/utest/run.hpp"
#include <cstring>



using namespace Yttrium;

namespace Yttrium
{

    


    namespace
    {
        static inline void ReadString(String &s, InputStream &fp)
        {
            static const char * const varName = "String";
            String tmp = String::Read(fp,varName);
            s.xch(tmp);
        }
    }

    template<> MPI::SerialCarrier<String>::ReadProc const MPI::SerialCarrier<String>:: Read = ReadString;


}

#include "y/format/hexadecimal.hpp"

Y_UTEST(carrier)
{
    MPI & mpi = MPI::Init(&argc,&argv);


    MPI::SerialCarrier<String> cr(100);
    String str;
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


}
Y_UDONE()

