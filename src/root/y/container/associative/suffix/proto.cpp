
#include "y/container/associative/suffix/proto.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Core
    {
        void SuffixCommon:: InsertFailureException()
        {
            throw Specific::Exception("Associative Suffix Container", "Unexpected insertion failure");
        }
    }
}
