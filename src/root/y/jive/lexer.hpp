
//! \file

#ifndef Y_Jive_Lexer_Included
#define Y_Jive_Lexer_Included 1

#include "y/jive/lexical/scanner.hpp"
#include "y/pointer/keyed.hpp"
#include "y/pointer/arc.hpp"
#include "y/container/associative/hash/set.hpp"
#include "y/handy/plain/light/list.hpp"
#include "y/type-to-type.hpp"

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
            curr(this),
            psdb(),
            lexemes(),
            history()
            {
                initialize();
            }

            //! cleanup
            virtual ~Lexer() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            Lexeme * get(Source&);
            void     unget(Lexeme * const) noexcept;


            //! plugin with no arguments
            template <typename PLUGIN, typename PID> inline
            const Lexical:: Rule & load(const TypeToType<PLUGIN> &,
                                        const PID                &pid)
            {
                const PScanner ps( new PLUGIN(pid,*this) );
                const Scanner &sc = record(ps);
                //call(sc.name)
            }



        private:
            Y_Disable_Copy_And_Assign(Lexer); //!< discarded
            Scanner * curr;
            Scanners  psdb;
            Lexemes   lexemes;                  //!< buffer of lexemes
            History   history;                  //!< call stack

            void      initialize();
            Scanner & record(const PScanner &);
        };

    }

}

#endif // !Y_Jive_Lexer_Included

