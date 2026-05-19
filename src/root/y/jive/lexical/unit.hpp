
//! \file

#ifndef Y_Jive_Lexical_Unit_Included
#define Y_Jive_Lexical_Unit_Included 1

#include "y/jive/token.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            class Unit : public Object, public Spot, public Token
            {
            public:

                explicit Unit(const Spot &spot, const Identifier &uid) noexcept;
                virtual ~Unit() noexcept;

                const Identifier name; //!< identifier
                Unit *           next; //!< for list
                Unit *           prev; //!< for list
            private:
                Y_Disable_Copy_And_Assign(Unit);
            };
        }
    }

}

#endif // !Y_Jive_Lexical_Unit_Included
