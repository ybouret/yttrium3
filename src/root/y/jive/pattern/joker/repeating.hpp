//! \file


#ifndef Y_Jive_Repeating_Included
#define Y_Jive_Repeating_Included 1

#include "y/jive/pattern/joker/joker.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //
        //! Repeating pattern
        //
        //
        //______________________________________________________________________
        class Repeating : public Joker
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const uint32_t UUID = Y_FOURCC('R', 'E', 'P', '_'); //!< UUID

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup with SOUND motif and minimal count
            explicit Repeating(const Motif &, const size_t);
            Repeating(const Repeating &);  //!< duplicate
            virtual ~Repeating() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual Pattern *     clone()                   const;
            virtual bool          univocal()       const noexcept; // false
            virtual size_t        serialize(OutputStream &) const;
            virtual bool          sound()          const noexcept; // false
            virtual bool          takes(Token&,Source&)     const;
            virtual OutputStream &viz(OutputStream &)       const;
            virtual Pattern *     optimized();
            virtual Pattern *     insensitive();

            //__________________________________________________________________
            //
            //
            // Method
            //
            //__________________________________________________________________

            //! \return new repeating from new pattern and parameter
            static Repeating * Make(Pattern * const,const size_t);

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t atLeast; //!< minimal count

        private:
            Y_Disable_Assign(Repeating); //!< discarded
        };
    }

}

#endif // !Y_Jive_Repeating_Included

