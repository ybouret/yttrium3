
//! file

#ifndef Y_OutputMemoryStream_Included
#define Y_OutputMemoryStream_Included


#include "y/stream/output.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/type/proxy.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Memory as Output Stream
    //
    //
    //__________________________________________________________________________
    class OutputMemoryStream :
    public OutputStream , public Proxy< Vector<char> >
    {
    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        template <typename NAME> inline
        explicit OutputMemoryStream(const NAME &name) : OutputStream(name)
        {
        }
        
        virtual ~OutputMemoryStream() noexcept;


        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual void flush() noexcept;
        virtual void write(const char);
        virtual void write(const void * const, const size_t);

        Vector<char> data;

    private:
        Y_Disable_Copy_And_Assign(OutputMemoryStream);
        Y_Proxy_Decl();

    };
}

#endif // !Y_OutputMemoryStream_Included

