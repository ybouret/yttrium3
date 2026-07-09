
#include "y/stream/bz2/error.hpp"

#if defined(_MSC_VER)
#pragma warning ( disable : 4668 )
#endif

#include "y/bzip2/bzlib.h"

namespace Yttrium
{
    namespace BZ2
    {

        const char * Error:: Get(const int bzerror) noexcept
        {

            switch(bzerror)
            {
                    Y_Return_Named_Case(BZ_OK);
                    Y_Return_Named_Case(BZ_RUN_OK);
                    Y_Return_Named_Case(BZ_FLUSH_OK);
                    Y_Return_Named_Case(BZ_FINISH_OK);
                    Y_Return_Named_Case(BZ_STREAM_END);
                    Y_Return_Named_Case(BZ_SEQUENCE_ERROR);
                    Y_Return_Named_Case(BZ_PARAM_ERROR);
                    Y_Return_Named_Case(BZ_MEM_ERROR);
                    Y_Return_Named_Case(BZ_DATA_ERROR);
                    Y_Return_Named_Case(BZ_DATA_ERROR_MAGIC);
                    Y_Return_Named_Case(BZ_IO_ERROR);
                    Y_Return_Named_Case(BZ_UNEXPECTED_EOF);
                    Y_Return_Named_Case(BZ_OUTBUFF_FULL);
                    Y_Return_Named_Case(BZ_CONFIG_ERROR);
                default:
                    break;
            }
            return Core::Unknown;
        }
    }

}


