//! \file

#ifndef Y_Jive_Char_Included
#define Y_Jive_Char_Included 1

#include "y/jive/spot.hpp"
#include "y/object/light.hpp"


namespace Yttrium
{
    namespace Jive
    {
        //______________________________________________________________________
        //
        //
        //
        //! Character with location
        //
        //
        //______________________________________________________________________
        class Char : public LightObject, public Spot
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Char(const Spot &, const uint8_t) noexcept; //!< setup
            Char(const Char &)                         noexcept; //!< duplicate
            virtual ~Char()                            noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            uint8_t       & operator*()       noexcept; //!< \return inner data
            const uint8_t & operator*() const noexcept; //!< \return inner data

        private:
            Y_Disable_Assign(Char); //!< discarded

            //__________________________________________________________________
            //
            //
            // Member
            //
            //__________________________________________________________________
            uint8_t data; //!< inner data
        public:
            Char * next; //!< for list/pool
            Char * prev; //!< for list
        };
    }

}


#endif // !Y_Jive_Char_Included
