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

        class Weasel : public Singleton<Weasel,ClassLockPolicy>
        {
        public:
            class Parser;
            class Code;
            static const char * const CallSign; //!< "Weasel";
            static const Longevity    LifeTime = 0;

            XNode * parse(Jive::Module * const);


            void operator()(Jive::Module * const,
                            Library    &,
                            Equilibria &);


            
        private:
            Y_Disable_Copy_And_Assign(Weasel);
            friend class Singleton<Weasel,ClassLockPolicy>;
            
            explicit Weasel();
            virtual ~Weasel() noexcept;
            Code * const code;
        public:
            const Identifier      lang;
            const Identifier      formula;
            const Identifier      equilibrium;
            const Identifier      alias;
            Formula::Translator & formulaTranslator;

        private:
            void onAlias(const String &, Library &lib, Equilibria &eqs);
            
        };

    }
}

#endif // !Y_Chemical_Weasel_Included

