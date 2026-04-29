
//! file

#ifndef Y_Stream_Included
#define Y_Stream_Included 1

#include "y/ability/identifiable.hpp"
#include "y/stream/identifier.hpp"
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
        // Methods
        //
        //______________________________________________________________________

        //!stamp exception
        /**
         \param excp input exception
         \param line optional line number
         \return stamped exception
         */
        Exception & stamp(Exception &excp, const unsigned line=0);


        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        const Identifier title; //!< title for this stream

    private:
        Y_Disable_Copy_And_Assign(Stream); //!< discarded
    };

}


#endif // !Y_Stream_Included
