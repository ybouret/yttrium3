//! \file

#ifndef Y_Jive_Spot_Included
#define Y_Jive_Spot_Included 1

#include "y/stream/identifier.hpp"

namespace Yttrium
{
    class Exception;

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
            // Definitions
            //
            //__________________________________________________________________
            static const unsigned DefaultLine   = 1; //!< alias
            static const unsigned DefaultColumn = 1; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param name compatible initializer for title
            template <typename NAME> inline
            explicit Spot(const NAME &name) :
            title(name), line(DefaultLine), column(DefaultColumn)
            {
            }

            virtual ~Spot()                noexcept; //!< cleanup
            Spot(const Spot &)             noexcept; //!< duplicate
            Spot & operator=(const Spot &) noexcept; //!< assign \return *this

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________


            Exception & stamp(Exception &) const noexcept; //!< \return stamped exception
            String      str()                       const; //!< \return stamped string
            void        set(const Identifier &)  noexcept; //!< reset

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Identifier title;  //!< title
            const unsigned   line;   //!< current line
            const unsigned   column; //!< current column

        };

    }
}


#endif // !Y_Jive_Spot_Included

