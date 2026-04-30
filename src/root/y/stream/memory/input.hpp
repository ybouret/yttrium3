
//! file

#ifndef Y_InputMemoryStream_Included
#define Y_InputMemoryStream_Included


#include "y/stream/input.hpp"
#include "y/memory/buffer/ro.hpp"
#include "y/string/length.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Memory to Input Stream
    //
    //
    //__________________________________________________________________________
    class InputMemoryStream : public InputStream
    {
    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup \param name for title \param buffer memory address \param buflen memory size
        template <typename NAME> inline
        explicit InputMemoryStream(const NAME &       name,
                                   const void * const buffer,
                                   const size_t       buflen) noexcept :
        InputStream(name),
        curr( (const char *) buffer ),
        base(curr),
        last(curr+buflen)
        {
            assert( !(0==buffer&&buflen>0) );
        }

        //! setup \param name for title \param buff read-only buffer
        template <typename NAME> inline
        explicit InputMemoryStream(const NAME &                  name,
                                   const Memory::ReadOnlyBuffer &buff) noexcept :
        InputStream(name),
        curr( (const char *) buff.ro() ),
        base(curr),
        last(curr+buff.length())
        {
        }

        //! setup \param name for title \param text any text
        template <typename NAME> inline
        explicit InputMemoryStream(const NAME &       name,
                                   const char * const text) noexcept :
        InputStream(name),
        curr(text),
        base(curr),
        last(curr+StringLength(text))
        {
        }

        virtual ~InputMemoryStream() noexcept; //!< cleanup

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual bool   query(char &);
        virtual size_t query(void * const, const size_t);
        virtual void   store(const char);

    private:
        Y_Disable_Copy_And_Assign(InputMemoryStream); //!< discarded
        const char *       curr; //!< current location
        const char * const base; //!< base location
        const char * const last; //!< first invalid location
    };

}

#endif // !Y_InputMemoryStream_Included

