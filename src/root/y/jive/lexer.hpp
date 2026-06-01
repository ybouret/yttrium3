
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

        namespace Lexical { class AdvancedPlugin; }

        //______________________________________________________________________
        //
        //
        //
        //! Lexer
        //
        //
        //______________________________________________________________________
        class Lexer : public Lexical::Scanner, public Lexical::Stack
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef Lexical::Scanner               Scanner;        //!< alias
            typedef Lexical::Plugin                Plugin;         //!< alias
            typedef Lexical::AdvancedPlugin        AdvancedPlugin; //!< alias
            typedef Keyed<String,ArcPtr<Scanner>>  PScanner;       //!< alias
            typedef HashSet<String,PScanner>       Scanners;       //!< alias
            typedef Handy::PlainLightList<Scanner> History;        //!< alias

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
            // Interface
            //
            //__________________________________________________________________
            virtual void push(Lexeme * const) noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            Lexeme * pull(Source&);


            //! plugin with no argument
            template <typename PLUGIN, typename PID> inline
            const Lexical:: Rule & load(const TypeToType<PLUGIN>,
                                        const PID & pid)
            {
                return makeCall( record( new PLUGIN(pid) ) );
            }

            //! plugin with 1 argument
            template <typename PLUGIN, typename PID, typename XPR> inline
            const Lexical:: Rule & load(const TypeToType<PLUGIN>,
                                        const PID & pid,
                                        const XPR & xpr)
            {
                return makeCall( record( new PLUGIN(pid,xpr) ) );
            }

            //! advanced plugin with no argument
            template <typename PLUGIN, typename PID> inline
            const Lexical::Rule & dial(const TypeToType<PLUGIN>,
                                       const PID & pid)
            {
                return makeDial( record( new PLUGIN(pid,*this) ) );
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
            const Lexical::Rule & makeDial(AdvancedPlugin &);


        };

        
    }

}

#endif // !Y_Jive_Lexer_Included

