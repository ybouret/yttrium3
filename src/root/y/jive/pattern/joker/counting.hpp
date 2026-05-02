
//! \file


#ifndef Y_Jive_Counting_Included
#define Y_Jive_Counting_Included 1

#include "y/jive/pattern/joker/joker.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //
        //! Counting pattern
        //
        //
        //______________________________________________________________________
        class Counting : public Joker
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const uint32_t UUID = Y_FOURCC('C', 'N', 'T', '_'); //!< UUID

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup with SOUND motif and counts
            explicit Counting(const Motif &, const size_t, const size_t);
            Counting(const Counting &);
            virtual ~Counting() noexcept;

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
            static Counting * Make(Pattern * const,const size_t,const size_t);

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t lower;
            const size_t upper;

        private:
            Y_Disable_Assign(Counting); //!< discarded
        };
    }

}

#endif // !Y_Jive_Counting_Included

