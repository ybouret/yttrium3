
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
            //__________________________________________________________________
            //
            //
            //
            //! Unit: named, localized token
            //
            //
            //__________________________________________________________________
            class Unit : public Object, public Spot, public Token
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param spot localisation \param uid identifier
                explicit Unit(const Spot &spot, const Identifier &uid) noexcept;
                virtual ~Unit() noexcept; //!< cleanup
                Y_OSTREAM_PROTO(Unit);    //!< display

                //! add description to exception
                /**
                 \param excp exception
                 \param full if true, append content
                 \return modified excp
                 */
                Exception & addTo(Exception &excp, const bool full) const noexcept;


                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Identifier name; //!< identifier
                Unit *           next; //!< for list
                Unit *           prev; //!< for list
            private:
                Y_Disable_Copy_And_Assign(Unit); //!< discarded
            };
        }

        typedef Lexical::Unit     Lexeme;  //!< alias
        typedef CxxListOf<Lexeme> Lexemes; //!< alias
    }

}

#endif // !Y_Jive_Lexical_Unit_Included
