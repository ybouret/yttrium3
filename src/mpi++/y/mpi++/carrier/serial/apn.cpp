

#include "y/mpi++/carrier/serial.hpp"
#include "y/apex/natural.hpp"

namespace Yttrium
{

    namespace
    {
        static inline void ReadAPN(apn &n, InputStream &fp)
        {
            static const char * const varName = "apn";
            apn tmp = apn::Read(fp,varName);
            n.xch(tmp);
        }
    }

    template<> MPI::SerialCarrier<apn>::ReadProc const MPI::SerialCarrier<apn>:: Read = ReadAPN;
}
