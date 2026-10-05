


#include "y/mpi++/carrier/serial.hpp"
#include "y/apex/integer.hpp"

namespace Yttrium
{

    namespace
    {
        static inline void ReadAPZ(apz &z, InputStream &fp)
        {
            static const char * const varName = "apz";
            apz tmp = apz::Read(fp,varName);
            z.xch(tmp);
        }
    }

    template<> MPI::SerialCarrier<apz>::ReadProc const MPI::SerialCarrier<apz>:: Read = ReadAPZ;
}
