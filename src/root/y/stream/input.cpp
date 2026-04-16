
#include "y/stream/input.hpp"

namespace Yttrium
{

    InputStream::  InputStream() : Stream() {}
    InputStream:: ~InputStream() noexcept {}


    bool InputStream:: gets(String &s)
    {
        s.free();

        return false;
    }

}
