
#include "y/stream/libc/input.hpp"
#include "y/libc/file/input.hpp"

namespace Yttrium
{
    namespace
    {
        typedef Libc::InputFile Code;
    }

    InputFile:: ~InputFile() noexcept
    {
        assert(code);
        delete static_cast<Code *>(code);
        Coerce(code) = 0;
    }

    InputFile:: InputFile(const StdIn_ &) :
    InputStream(Y_STDIN),
    code( OpenStdIn() ),
    buff()
    {
    }

    void * InputFile:: OpenRegular(const String &fileName)
    {
        return new Code(fileName);
    }

    void * InputFile:: OpenStdIn()
    {
        return new Code(StdIn);
    }

    bool InputFile:: query(char &C)
    {
        assert(code);

        if(buff.size) {
            C = **buff.head;
            delete buff.popHead();
            return true;
        }
        else
        {
            return static_cast<Code *>(code)->query(C);
        }
    }

    void InputFile:: store(const char c)
    {
        buff.pushHead( new IO::Char(c) );
    }


    namespace {

        static inline size_t transfer(void * const  data,
                                      IO::Chars   & buff,
                                      const size_t        size) noexcept
        {
            assert(size<=buff.size);
            uint8_t * p = (uint8_t *)data;
            for(size_t n=size;n>0;--n)
            {
                *(p++) = **buff.head; delete buff.popHead();
            }
            return size;
        }
    }

    size_t InputFile:: query(void * const blockAddr, const size_t blockSize)
    {
        if( buff.size >= blockSize )
        {
            return transfer(blockAddr, buff, blockSize);
        }
        else
        {
            const size_t done = transfer(blockAddr,buff,buff.size);
            return static_cast<Code *>(code)->query( static_cast<uint8_t *>(blockAddr) + done, blockSize - done);
        }
    }

    void InputFile:: prefetch(size_t n)
    {
        while(n-- > 0)
        {
            AutoPtr< IO::Char > pch = new IO::Char(0);
            if( static_cast<Code *>(code)->query( **pch ) )
            {
                buff.pushTail( pch.yield() );
                continue;
            }
            return;
        }
    }


}
