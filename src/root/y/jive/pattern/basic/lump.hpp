


//! \file

#ifndef Y_Jive_Lump_Included
#define Y_Jive_Lump_Included 1

#include "y/jive/pattern/basic/one-char.hpp"
#include "y/jive/pattern/within.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //
        //! Accept a range of characters
        //
        //
        //______________________________________________________________________
        class Lump : public OneChar, public Within
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const uint32_t UUID = Y_FOURCC('L','U','M','P'); //!< UUID

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Lump(const uint8_t,const uint8_t) noexcept; //!< setup
            Lump(const Within)                noexcept; //!< setup from Within
            virtual ~Lump()                   noexcept; //!< cleanup
            Lump(const Lump &)                noexcept; //!< duplicate

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual Pattern *     clone()                   const;
            virtual size_t        serialize(OutputStream &) const;
            virtual void          glean(Leading &) const noexcept;
            virtual bool          univocal()       const noexcept;
            virtual OutputStream &viz(OutputStream &)       const;
            virtual Pattern *     optimized();
            virtual Pattern *     insensitive();


        private:
            Y_Disable_Assign(Lump); //!< discared
            virtual bool found(const uint8_t) const noexcept;
        };

    }

}

#endif // !Y_Jive_Lump_Included

