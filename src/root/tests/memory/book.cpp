#include "y/memory/book.hpp"
#include "y/concurrent/nucleus.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(memory_book)
{
    Y_SIZEOF(Memory::Pages);
    Y_SIZEOF(Memory::Book);

    Concurrent::Nucleus &nucleus = Concurrent::Nucleus::Instance();
    Memory::Book         book(nucleus,nucleus.access);
}
Y_UDONE()

