
//! \file

#ifndef Y_Pattern_Within_Included
#define Y_Pattern_Within_Included 1

#include "y/config/setup.hpp"
#include "y/ostream-proto.hpp"

namespace Yttrium
{

    namespace Jive
    {
        class Pattern;
        
        //______________________________________________________________________
        //
        //
        //
        //! Within holds lower and upper bounds
        //
        //
        //______________________________________________________________________
        class Within
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Within(const uint8_t,const uint8_t) noexcept; //!< setup
            virtual ~Within()                   noexcept; //!< cleanup
            Within(const Within &)              noexcept; //!< duplicate
            Y_OSTREAM_PROTO(Within);                      //!< display

            //__________________________________________________________________
            //
            //
            // methods
            //
            //__________________________________________________________________
            bool      isByte() const noexcept; //!< \return true iff lower==upper
            bool      isLump() const noexcept; //!< \return true iff lower<upper
            Pattern * create() const; //!< \return matching Byte or Lump

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const uint8_t lower; //!< lower bound
            const uint8_t upper; //!< upper bound

        private:
            Y_Disable_Assign(Within); //!< discarded
        };
    }

}

#endif // !Y_Pattern_Within_Included
