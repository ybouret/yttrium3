//! \file

#ifndef Y_Jive_Spot_Included
#define Y_Jive_Spot_Included 1

#include "y/stream/identifier.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //
        //! Specific location
        //
        //
        //______________________________________________________________________
        class Spot
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param name compatible initializer for title
            template <typename NAME> inline
            explicit Spot(const NAME &name) :
            title(name), line(1), column(1)
            {
            }

            virtual ~Spot()    noexcept; //!< cleanup
            Spot(const Spot &) noexcept; //!< duplicate

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Identifier title;  //!< title
            const unsigned   line;   //!< current line
            const unsigned   column; //!< current column

        private:
            Y_Disable_Assign(Spot); //!< discarded
        };

    }
}


#endif // !Y_Jive_Spot_Included

