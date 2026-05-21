
//! \file

#ifndef Y_Jive_Lexer_Included
#define Y_Jive_Lexer_Included 1

#include "y/jive/lexical/plugin.hpp"
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
            typedef Lexical::Plugin                Plugin;
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
                return makeCall( record( new PLUGIN(pid,*this) ) );
            }



        private:
            Y_Disable_Copy_And_Assign(Lexer); //!< discarded
            Scanner * curr;                   //!< current scanner
            Scanners  psdb;                   //!< set of scanners/plugins
            Lexemes   lexemes;                //!< buffer of lexemes
            History   history;                //!< call stack

            void      initialize();

            template <typename PLUGIN> inline
            PLUGIN &  record(PLUGIN * const plugin) { insert(plugin); return *plugin; }
            void      insert(Scanner * const);
            void      remove(const Identifier &) noexcept;


            const Lexical::Rule & makeCall(Plugin &);


        };

    }

}

#endif // !Y_Jive_Lexer_Included

