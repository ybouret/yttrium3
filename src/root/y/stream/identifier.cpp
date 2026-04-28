#include "y/stream/identifier.hpp"

namespace Yttrium
{
    Identifier:: ~Identifier() noexcept
    {
    }

    Identifier:: Identifier(const String * const p) noexcept :
    SharedString(p)
    {
    }

    Identifier:: Identifier(const Identifier &_) noexcept :
    SharedString(_)
    {
    }

    Identifier:: Identifier(const String &s) :
    SharedString( new String(s) )
    {
    }

    Identifier:: Identifier(const char * const s) :
    SharedString( new String(s) )
    {
    }

    Identifier:: Identifier(const char c) :
    SharedString( new String(c) )
    {
    }



}
