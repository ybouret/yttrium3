#include "y/memory/book.hpp"
#include "y/concurrent/nucleus.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

Y_UTEST(memory_book)
{
    Core::Rand ran;
    Y_SIZEOF(Memory::Pages);
    Y_SIZEOF(Memory::Book);

    Concurrent::Nucleus &nucleus = Concurrent::Nucleus::Instance();
    Memory::Book        &book    = nucleus.book;
    for(unsigned shift=book.MinPageShift;shift<=book.MinPageShift*3;++shift)
    {
        book[shift].cache(ran.in<size_t>(1,10));
    }
    std::cerr << "reserved: " << book.availableBytes() << std::endl;
    book.gc(0x25);
    std::cerr << "reserved: " << book.availableBytes() << std::endl;


}
Y_UDONE()

