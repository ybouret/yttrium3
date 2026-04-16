//! file

#ifndef Y_InputStream_Included
#define Y_InputStream_Included


#include "y/stream/stream.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Base class for input stream
    //
    //
    //__________________________________________________________________________
    class InputStream : public Stream
    {

    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup \param name for title
        template <typename NAME> inline
        explicit InputStream(const NAME &name) : Stream(name)
        {
        }
        
        virtual ~InputStream() noexcept; //!< cleanup

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual bool   query(char &)                      = 0; //!< \return true if new char is available
        virtual size_t query(void * const, const size_t ) = 0; //!< \return read in block
        virtual void   store(const char)                  = 0; //!< store single back back into the stream

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        bool gets(String &s);
        

    protected:
        explicit InputStream(); //!< for virtual constructor

    private:
        Y_Disable_Copy_And_Assign(InputStream); //!< discarded
    };

}


#endif // !Y_InputStream_Included
