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
        const Identifier & operator[](const NAME &name)
        {
            const Identifier id(name); record(id);
            const Identifier * const pid = search(*id); assert(pid);
            return *pid;
        }




    private:
        Y_Disable_Assign(Identifiers); //!< discarded
        Code * const code;             //!< inner code

        void               record(const Identifier &);   //!< ensure existing identifier
        const Identifier * search(const String &) const; //!< \return matching identifier
    };


}

#endif // !Y_Identifiers_Included
