
//! \file

#ifndef Y_Jive_Lexer_Included
#define Y_Jive_Lexer_Included 1

#include "y/jive/lexical/scanner.hpp"
#include "y/pointer/keyed.hpp"
#include "y/pointer/arc.hpp"
#include "y/container/associative/hash/set.hpp"
#include "y/handy/plain/light/list.hpp"

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
            // Definitions
            //
            //__________________________________________________________________
            typedef Lexical::Scanner               Scanner;  //!< alias
            typedef Keyed<String,ArcPtr<Scanner>>  PScanner; //!< alias
            typedef HashSet<String,PScanner>       Scanners; //!< alias
            typedef Handy::PlainLightList<Scanner> History;  //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! initialize \param id lexer name
            template <typename ID> inline
            explicit Lexer(const ID &id) :
            Scanner(id,Lexical::AcceptEOS),
            lexemes(),
            history()
            {
            }

            //! cleanup
            virtual ~Lexer() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Lexer); //!< discarded
            Lexemes lexemes;                  //!< buffer of lexemes
            History history;                  //!< call stack
        };

    }

}

#endif // !Y_Jive_Lexer_Included

