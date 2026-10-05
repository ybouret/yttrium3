
#include "y/mpi++/carrier/serial.hpp"

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
