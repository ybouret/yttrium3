
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

        //! setup \param name identifier \param minCapacity data minimal capacity
        template <typename NAME> inline
        explicit OutputMemoryStream(const NAME  & name,
                                    const size_t  minCapacity=0
                                    ) :
        OutputStream(name),
        data(WithAtLeast,minCapacity)
        {
        }

        //! cleanup
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

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        Vector<char> data; //!< inner data

    private:
        Y_Disable_Copy_And_Assign(OutputMemoryStream); //!< discarded
        Y_Proxy_Decl(); //!< helper

    };
}

#endif // !Y_OutputMemoryStream_Included

