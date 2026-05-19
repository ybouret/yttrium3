//! \file

#ifndef Y_Jive_Lexical_Unit_Included
#define Y_Jive_Lexical_Unit_Included 1

#include "y/jive/lexical/unit.hpp"
#include "y/jive/lexical/rule.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            //__________________________________________________________________
            //
            //
            //
            //! Produce units with a set of rules
            //
            //
            //__________________________________________________________________
            class Scanner
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                class Code;

                template <typename SID> inline
                explicit Scanner(const SID &sid) :
                name(sid),
                code( CreateCode(sid) )
                {

                }



                virtual ~Scanner() noexcept; //!< cleanup

                const Identifier name;

            private:
                Y_Disable_Copy_And_Assign(Scanner); //!< discarded
                Code * const code;
                static Code * CreateCode(const Identifier &);
            };
        }

    }

}

#endif // !Y_Jive_Lexical_Unit_Included

