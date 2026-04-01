#include "y/object/factory.hpp"
#include <cstring>

namespace Yttrium
{

    Object::  Object() noexcept {}
    Object:: ~Object() noexcept {}

    void * Object :: operator new(const size_t blockSize)
    {
        assert(blockSize>0);
        static Factory & factory = Factory::Instance();
        return factory.query(blockSize);
    }

    void Object:: operator delete(void * const blockAddr, const size_t blockSize) noexcept
    {
        assert(0!=blockAddr);
        assert(blockSize>0);
        static Factory & factory = Factory::Location();
        factory.store(blockAddr,blockSize);
    }


    void * Object :: operator new[](const size_t blockSize)
    {
        assert(blockSize>0);
        static Factory & factory = Factory::Instance();
        return factory.query(blockSize);
    }

    void Object:: operator delete[](void * const blockAddr, const size_t blockSize) noexcept
    {
        assert(0!=blockAddr);
        assert(blockSize>0);
        static Factory & factory = Factory::Location();
        factory.store(blockAddr,blockSize);
    }

    void * Object:: operator new(const size_t blockSize, void * const blockAddr) noexcept
    {
        assert(0!=blockAddr);
        assert(blockSize>0);
        return memset(blockAddr,0,blockSize);
    }

    void Object:: operator delete(void * const , void * const) noexcept
    {
        
    }

}
