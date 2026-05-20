
//! \file

#ifndef Y_Jive_Lexical_Scanner_Code_Included
#define Y_Jive_Lexical_Scanner_Code_Included 1

#include "y/jive/lexical/scanner.hpp"
#include "y/jive/lexical/scanner/meta-table.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            class Scanner:: Code : public Object
            {
            public:
                explicit Code(const Identifier &);
                virtual ~Code() noexcept;

                void add(Rule * const rule);

                const Identifier name;  //!< from scanner
                CxxListOf<Rule>  rlist; //!< list of rules
                MetaTable        table; //!< table of list or rules

            private:
                Y_Disable_Copy_And_Assign(Code); //!< discarded
                void noMultiple(const Rule & rule) const;
            };

          

        }
    }

}

#endif // !Y_Jive_Lexical_Scanner_Code_Included

