
//! \file

#ifndef Y_Jive_Token_Included
#define Y_Jive_Token_Included 1

#include "y/jive/char.hpp"
#include "y/core/list/cxx.hpp"

namespace Yttrium
{
    namespace Jive
    {

        class Token : public CxxList<Char>
        {
        public:
            explicit Token() noexcept;
            virtual ~Token() noexcept;
            Token(const Token &);
            Y_OSTREAM_PROTO(Token);

            Token & operator<<(Char * const) noexcept;
            Token & operator>>(Char * const) noexcept;
            


        private:
            Y_Disable_Assign(Token);
        };

    }

}

#endif // !Y_Jive_Token_Included

