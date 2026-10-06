#include "y/mpi++/api.hpp"
#include "y/apex/integer.hpp"

namespace Yttrium
{

    namespace
    {
        static inline void ReadAPZ(apz &z, InputStream &fp)
        {
            apz tmp = apz::Read(fp,apz::CallSign);
            z.xch(tmp);
        }
    }

    template<> MPI::SerialCarrier<apz>::ReadProc const MPI::SerialCarrier<apz>:: Read = ReadAPZ;
}
