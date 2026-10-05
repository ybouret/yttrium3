#include "y/mpi++/carrier/serial.hpp"
#include "y/apex/rational.hpp"

namespace Yttrium
{

    namespace
    {
        static inline void ReadAPQ(apq &q, InputStream &fp)
        {
            static const char * const varName = "apq";
            apq tmp = apq::Read(fp,varName);
            q.xch(tmp);
        }
    }

    template<> MPI::SerialCarrier<apq>::ReadProc const MPI::SerialCarrier<apq>:: Read = ReadAPQ;
}
