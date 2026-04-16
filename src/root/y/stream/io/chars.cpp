
#include "y/stream/io/chars.hpp"


namespace Yttrium
{
    namespace IO
    {
        Char:: Char(const char c) noexcept :
        LightObject(),
        data(c),
        next(0),
        prev(0)
        {
        }

        Char:: ~Char() noexcept
        {
        }

        char & Char:: operator*() noexcept
        {
            return data;
        }

        const char & Char:: operator*() const noexcept
        {
            return data;
        }

        Char:: Char(const Char &ch) noexcept :
        LightObject(),
        data(ch.data),
        next(0),
        prev(0)
        {
        }


    }

}

namespace Yttrium
{
    namespace IO
    {
        Chars:: Chars() noexcept : LightObject(), Char::List()
        {
        }

        Chars:: ~Chars() noexcept
        {
        }

        Chars::Chars(const Chars &other) : LightObject(), Char::List(other)
        {
        }
        
    }

}
