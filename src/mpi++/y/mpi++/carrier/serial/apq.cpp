#include "y/mpi++/api.hpp"
#include "y/apex/rational.hpp"

namespace Yttrium
{

    namespace
    {
        static inline void ReadAPQ(apq &q, InputStream &fp)
        {
            apq tmp = apq::Read(fp,apq::CallSign);
            q.xch(tmp);
        }
    }

    template<> MPI::SerialCarrier<apq>::ReadProc const MPI::SerialCarrier<apq>:: Read = ReadAPQ;
}
