
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
            //__________________________________________________________________
            //
            //
            //
            //! Inner Scanner code
            //
            //
            //__________________________________________________________________
            class Scanner:: Code : public Object
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Code(const Identifier &); //!< setup
                virtual ~Code() noexcept;          //!< cleanup

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                void add(Rule * const); //!< add and dispatch new rule

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Identifier name;  //!< from scanner
                Rule::List       rlist; //!< list of rules
                Action::List     alist; //!< list of actions
                MetaTable        table; //!< table of list or rules

            private:
                Y_Disable_Copy_And_Assign(Code);     //!< discarded
                void noMultiple(const Rule &) const; //!< check no multiple name
            };

          

        }
    }

}

#endif // !Y_Jive_Lexical_Scanner_Code_Included

