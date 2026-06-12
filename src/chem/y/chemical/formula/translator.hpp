
//! \file

#ifndef Y_Chemical_Formula_Translator_Included
#define Y_Chemical_Formula_Translator_Included 1

#include "y/chemical/formula.hpp"
#include "y/jive/editor.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        class Formula:: Translator : public Jive::Editor
        {
        public:
            explicit Translator(const Identifier &);
            virtual ~Translator() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Translator);
        };
    }
}

#endif // !Y_Chemical_Formula_Translator_Included
