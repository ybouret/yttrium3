
#include "y/chemical/formula/translator.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        Formula::Translator:: ~Translator() noexcept
        {
        }

        Formula:: Translator:: Translator(const Identifier &id) :
        Jive::Editor(id)
        {
        }

    }
}
