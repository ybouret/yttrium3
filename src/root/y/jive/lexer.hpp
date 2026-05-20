
//! \file

#ifndef Y_Jive_Lexer_Included
#define Y_Jive_Lexer_Included 1

#include "y/jive/lexical/scanner.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //
        //! Lexer
        //
        //
        //______________________________________________________________________
        class Lexer : public Lexical::Scanner
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //___________________________________________________________________

            //! initialize \param id lexer name
            template <typename ID> inline
            explicit Lexer(const ID &id) :
            Lexical::Scanner(id)
            {
            }

            //! cleanup
            virtual ~Lexer() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Lexer); //!< discarded
        };

    }

}

#endif // !Y_Jive_Lexer_Included

