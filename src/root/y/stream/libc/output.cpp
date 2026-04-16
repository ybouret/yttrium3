
#include "y/stream/libc/output.hpp"
#include "y/libc/file/output.hpp"
#include "y/exception.hpp"

namespace Yttrium
{

    namespace
    {
        typedef Libc::OutputFile Code;
    }

    OutputFile:: ~OutputFile() noexcept
    {
        assert(code);
        delete static_cast<Code *>(code);
        Coerce(code) = 0;
    }

    OutputFile:: OutputFile(const StdOut_ &) :
    OutputStream(Y_STDOUT),
    code( OpenStdErr() )
    {
    }

    OutputFile:: OutputFile(const StdErr_ &) :
    OutputStream(Y_STDERR),
    code( OpenStdErr() )
    {
    }


    void * OutputFile:: OpenRegular(const String &fileName, const bool append)
    {
        return new Code(fileName,append);
    }

    void * OutputFile:: OpenStdOut()
    {
        return new Code(StdOut);
    }


    void * OutputFile:: OpenStdErr()
    {
        return new Code(StdErr);
    }


    void OutputFile:: write(const char C)
    {
        assert(code);
        try {
            static_cast<Code*>(code)->write(C);
        }
        catch(Exception &excp)
        {
            throw stamp(excp);
        }
        catch(...)
        {
            throw;
        }
    }

    void OutputFile:: flush()
    {
        assert(code);
        try {
            static_cast<Code*>(code)->flush();
        }
        catch(Exception &excp)
        {
            throw stamp(excp);
        }
        catch(...)
        {
            throw;
        }
    }

    void OutputFile:: write(const void * const blockAddr, const size_t blockSize)
    {
        assert(code);
        try {
            static_cast<Code*>(code)->write(blockAddr,blockSize);
        }
        catch(Exception &excp)
        {
            throw stamp(excp);
        }
        catch(...)
        {
            throw;
        }
    }


}


