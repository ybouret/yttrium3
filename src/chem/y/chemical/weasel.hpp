//! \file

#ifndef Y_Chemical_Weasel_Included
#define Y_Chemical_Weasel_Included 1

#include "y/singleton.hpp"
#include "y/chemical/library.hpp"
#include "y/chemical/reactive/equilibria.hpp"
#include "y/jive/module.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        //______________________________________________________________________
        //
        //
        //
        //! Weasel Equilibria And Species Elementary Language
        //
        //
        //______________________________________________________________________
        class Weasel : public Singleton<Weasel,ClassLockPolicy>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            class Parser;
            class Code;
            static const char * const CallSign;     //!< "Weasel"
            static const Longevity    LifeTime = 0; //!< life time

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \return AST from a given module
            XNode * parse(Jive::Module * const);

            //! parse and populate from a given module
            void operator()(Jive::Module * const,
                            Library    &,
                            Equilibria &);


            
        private:
            friend class Singleton<Weasel,ClassLockPolicy>;
            Y_Disable_Copy_And_Assign(Weasel); //!< discarde
            explicit Weasel();                 //!< setup
            virtual ~Weasel() noexcept;        //!< cleanup
            Code * const code;                 //!< inner code
        public:
            const Identifier      lang;              //!< inner lang
            const Identifier      formula;           //!< inner formula identifier
            const Identifier      equilibrium;       //!< inner equilibrium identifier
            const Identifier      alias;             //!< inner alias identifier
            Formula::Translator & formulaTranslator; //!< inner translator

        private:
            void onAlias(const String &, Library &, Equilibria &); //!< find alias in inner database

        };

    }
}

#endif // !Y_Chemical_Weasel_Included

