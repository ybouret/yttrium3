
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
            explicit Optional(const Motif &) noexcept; //!< setup
            Optional(const Optional &);                //!< duplicate
            virtual ~Optional() noexcept;              //!< cleanup

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

            //__________________________________________________________________
            //
            //
            // Method
            //
            //__________________________________________________________________

            //! \return new optional from new pattern
            static Optional * Make(Pattern * const);



        private:
            Y_Disable_Assign(Optional); //!< dicarded
        };
    }

}

#endif // !Y_Jive_Optional_Included

