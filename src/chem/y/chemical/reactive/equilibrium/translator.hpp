
//! \file

#ifndef Y_Chemical_Equilibrium_Translator_Included
#define Y_Chemical_Equilibrium_Translator_Included 1

#include "y/chemical/reactive/equilibria.hpp"
#include "y/chemical/library.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/chemical/formula/translator.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        class Equilibrium::Translator
        {
        public:
            explicit Translator(const Identifier &);
            virtual ~Translator() noexcept;


            void operator()(AutoPtr<XNode>       & tree,
                            Library              & lib,
                            Equilibria           & eqs,
                            Formula::Translator  & ftr);

            const Identifier lang;

        private:
            Y_Disable_Copy_And_Assign(Translator);
            Actor::List reac;
            Actor::List prod;

            void fill(Actor::List          &,
                      XNode * const         ,
                      Library              &,
                      Formula::Translator  &,
                      const char * const);
        };
    }

}

#endif // !Y_Chemical_Equilibrium_Translator_Included

