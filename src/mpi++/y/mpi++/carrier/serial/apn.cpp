

#include "y/mpi++/api.hpp"
#include "y/apex/natural.hpp"

namespace Yttrium
{

    namespace
    {
        static inline void ReadAPN(apn &n, InputStream &fp)
        {
            apn tmp = apn::Read(fp,apn::CallSign);
            n.xch(tmp);
        }
    }

    template<> MPI::SerialCarrier<apn>::ReadProc const MPI::SerialCarrier<apn>:: Read = ReadAPN;
}
