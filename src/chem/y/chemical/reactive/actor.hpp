
//! \file

#ifndef Y_Chemical_Actor_Included
#define Y_Chemical_Actor_Included 1

#include "y/chemical/species.hpp"
#include "y/chemical/type/defs.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        //______________________________________________________________________
        //
        //
        //
        //! Actor use
        //
        //
        //______________________________________________________________________
        enum Acting
        {
            AsSpec, //!< used as species
            AsConc  //!< ised as concentration
        };

        //______________________________________________________________________
        //
        //
        //
        //! Helper to format equilibria
        //
        //
        //______________________________________________________________________
        class Actor : public Object, public Entity
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef CxxListOf<Actor> List; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Actor(const unsigned &, const Species &, const Acting); //!< setup
            virtual ~Actor() noexcept;                                       //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void massAction(XMul &, const XReadable &, const Level) const;                //!< mass action at given concentration/level
            void massAction(XMul &, const XReadable &, const Level, const xreal_t) const; //!< safe mass action at shifted concentration/level

            xreal_t extent(const XReadable &, const Level) const noexcept;
            
            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const unsigned nu;   //!< coefficient
            const Species &sp;   //!< species
            const xreal_t  xn;   //!< nu as xreal
            const xreal_t  zero; //!< helper
            Actor *        next; //!< for list
            Actor *        prev; //!< for list

        private:
            Y_Disable_Copy_And_Assign(Actor); //!< discarded
        };
    }

}

#endif // !Y_Chemical_Actor_Included
