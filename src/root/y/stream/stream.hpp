
//! file

#ifndef Y_Stream_Included
#define Y_Stream_Included 1

#include "y/ability/identifiable.hpp"
#include "y/string.hpp"

namespace Yttrium
{

    class Exception;

    //__________________________________________________________________________
    //
    //
    //
    //! (virtual) base class for streams
    //
    //
    //__________________________________________________________________________
    class  Stream : public Identifiable
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
        explicit Stream(const NAME &name) : title(name)
        {

        }
        virtual ~Stream() noexcept; //!< cleanup
        
    protected:
        explicit Stream();
        
    public:
        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual const char * callSign() const noexcept;

        //______________________________________________________________________
        //
        //
        // method
        //
        //______________________________________________________________________
        Exception & stamp(Exception &excp); //!< stamp exception \param excp input exception \return stamped exception

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        const String title; //!< title for this stream

    private:
        Y_Disable_Copy_And_Assign(Stream); //!< discarded
    };

}


#endif // !Y_Stream_Included
