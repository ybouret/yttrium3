
//! \file

#ifndef Y_Hashing_KeyDumper_Included
#define Y_Hashing_KeyDumper_Included 1


#include "y/config/setup.hpp"

namespace Yttrium
{

    namespace Hashing
    {

        template <typename T>
        class KeyDumper
        {
        public:
            inline  KeyDumper() noexcept {}
            inline ~KeyDumper() noexcept {}

            inline size_t operator()(const T &k) noexcept
            {
                return (size_t)k;
            }

        private:
            Y_Disable_Copy_And_Assign(KeyDumper);
        };

    }

}

#endif // !Y_Hashing_KeyDumper_Included
