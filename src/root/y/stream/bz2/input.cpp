#include "y/stream/bz2/input.hpp"
#include "y/type/destroy.hpp"

namespace Yttrium
{
    namespace BZ2
    {

        class Input:: Code
        {
        public:
            

            inline virtual ~Code() noexcept {}

        private:
            Y_Disable_Copy_And_Assign(Code);
        };

        Input:: ~Input() noexcept
        {
            assert(code);
            Destroy(code);
        }

        

    }

}


