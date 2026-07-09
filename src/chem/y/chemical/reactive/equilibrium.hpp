
//! \file

#ifndef Y_Chemical_Equilibrium_Included
#define Y_Chemical_Equilibrium_Included 1

#include "y/chemical/reactive/components.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        //______________________________________________________________________
        //
        //
        //
        //! Equilibrium interface
        //
        //
        //______________________________________________________________________
        class Equilibrium : public CountedObject, public Components
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "Equilibrium"
            static const char * const Symbol;   //!< "<=>"
            class Translator;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Equilibrium(const String &, const size_t); //!< setup
            virtual ~Equilibrium() noexcept;                    //!< cleanup
            Y_OSTREAM_PROTO(Equilibrium);                       //!< display name

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            xreal_t K(xreal_t); //!< \return checked getK(t)

        private:
            Y_Disable_Copy_And_Assign(Equilibrium); //!< discaeded
            virtual xreal_t getK(const xreal_t) = 0;      //!< \return constant at given time
        };

    }

}

#endif // !Y_Chemical_Equilibrium_Included

