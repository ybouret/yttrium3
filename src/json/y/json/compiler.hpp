//! \file

#ifndef Y_JSON_Compiler_Included
#define Y_JSON_Compiler_Included 1

#include "y/json/value.hpp"
#include "y/jive/module.hpp"

namespace Yttrium
{

    namespace JSON
    {
        class Compiler
        {
        public:
            static const char * const CallSign;
            class Code;

            explicit Compiler();
            virtual ~Compiler() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Compiler);
            Code * const code;
        };
    }

}


#endif // !Y_JSON_Compiler_Included

