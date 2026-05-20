
//! \file

#ifndef Y_Jive_Lexer_Included
#define Y_Jive_Lexer_Included 1

#include "y/jive/lexical/scanner.hpp"
#include "y/pointer/keyed.hpp"
#include "y/pointer/arc.hpp"
#include "y/container/associative/hash/set.hpp"

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
            typedef Lexical::Scanner              Scanner;
            typedef Keyed<String,ArcPtr<Scanner>> SPtr;
            typedef HashSet<String,SPointer>      

            //__________________________________________________________________
            //
            //
            // C++
            //
            //___________________________________________________________________

            //! initialize \param id lexer name
            template <typename ID> inline
            explicit Lexer(const ID &id) :
            Scanner(id,Lexical::AcceptEOS),
            buffer()
            {
            }

            //! cleanup
            virtual ~Lexer() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Lexer); //!< discarded
            Lexemes buffer;

        };

    }

}

#endif // !Y_Jive_Lexer_Included

