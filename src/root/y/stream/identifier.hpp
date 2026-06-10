//! file

#ifndef Y_Identifier_Included
#define Y_Identifier_Included


#include "y/string.hpp"
#include "y/pointer/arc.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Identifier to be passed on
    //
    //
    //__________________________________________________________________________
    class Identifier : public ArcPtr<const String>
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef ArcPtr<const String> SharedString; //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        Identifier(const String * const) noexcept; //!< setup from a new string
        Identifier(const Identifier &)   noexcept; //!< setup from another identifier
        Identifier(const String &);                //!< setup from a string
        Identifier(const char * const);            //!< setup from a text
        Identifier(const char);                    //!< setup from a character
        virtual ~Identifier()            noexcept; //!< cleanup

        

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        const String & key() const noexcept; //!< \return **this

    private:
        Y_Disable_Assign(Identifier); //!< discarded
    };

}

#endif // !Y_Identifier_Included

