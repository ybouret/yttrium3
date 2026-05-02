
//! \file


#ifndef Y_Jive_Optional_Included
#define Y_Jive_Optional_Included 1

#include "y/jive/pattern/joker/joker.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //
        //! Optional pattern
        //
        //
        //______________________________________________________________________
        class Optional : public Joker
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const uint32_t UUID = Y_FOURCC('O', 'P', 'T', '_'); //!< UUID

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Optional(const Motif &) noexcept;
            Optional(const Optional &);
            virtual ~Optional() noexcept;

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual Pattern * clone() const;
            virtual bool      univocal() const noexcept;        // false
            virtual size_t    serialize(OutputStream &) const;
            virtual bool      sound() const noexcept; // false
            virtual bool      takes(Token&,Source&) const;

            //__________________________________________________________________
            //
            //
            // Method
            //
            //__________________________________________________________________
            static Optional * Make(Pattern * const);

        private:
            Y_Disable_Assign(Optional);
        };
    }

}

#endif // !Y_Jive_Optional_Included

