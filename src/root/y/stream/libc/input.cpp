
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
    code( OpenStdIn() )
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
        
    }


}
