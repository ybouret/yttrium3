
#include "y/stream/serializable.hpp"

namespace Yttrium
{

    Serializable::  Serializable() noexcept {}
    Serializable:: ~Serializable() noexcept {}


}

#include "y/stream/libc/output.hpp"

namespace Yttrium
{
    size_t Serializable:: saveBinary(const char *const fileName) const
    {
        OutputFile fp(fileName);
        return serialize(fp);
    }

    size_t Serializable:: saveBinary(const String & fileName) const
    {
        OutputFile fp(fileName);
        return serialize(fp);
    }


}
