//! file

#ifndef Y_Identifiers_Included
#define Y_Identifiers_Included


#include "y/stream/identifier.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Shared database of identifiers
    //
    //
    //__________________________________________________________________________
    class Identifiers
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const char * const CallSign; //!< "Identifiers"
        class Code;


        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit Identifiers();                     //!< setup empty
        virtual ~Identifiers()            noexcept; //!< cleanup
        Identifiers(const Identifiers &)  noexcept; //!< duplicate shared copy

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! on-the-fly identifier get/create
        /**
         \param  name compatible name
         \return new or existing identifier
         */
        template <typename NAME> inline
        const Identifier  operator[](const NAME &name)
        {
            return record(name);
        }



    private:
        Y_Disable_Assign(Identifiers); //!< discarded
        Code * const code;             //!< inner code
        const Identifier   record(const Identifier &);   //!< \return matching found/created identifier
        const Identifier   record(const String     &);   //!< \return matching found/created identifier
        const Identifier   record(const char * const);   //!< \return matching found/created identifier
        const Identifier * search(const String &) const; //!< \return matching identifier
    };


}

#endif // !Y_Identifiers_Included
