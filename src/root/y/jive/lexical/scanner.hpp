//! \file

#ifndef Y_Jive_Lexical_Scanner_Included
#define Y_Jive_Lexical_Scanner_Included 1

#include "y/jive/lexical/unit.hpp"
#include "y/jive/lexical/rule.hpp"
#include "y/jive/lexical/command.hpp"
#include "y/jive/regexp.hpp"

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

                //! setup \param sid name
                template <typename SID> inline
                explicit Scanner(const SID &sid) :
                name(sid),
                code( CreateCode(sid) )
                {

                }

                //! cleanup
                virtual ~Scanner() noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                void  add(Rule * const); //!< add newly created rule
                Unit *get(Source &source, Command &command);


                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Identifier name; //!< identifier

            private:
                Y_Disable_Copy_And_Assign(Scanner); //!< discarded
                Code * const code;                  //!< inner code

                //! \return code instance
                static Code * CreateCode(const Identifier &);
            };
        }

    }

}

#endif // !Y_Jive_Lexical_Scanner_Included

