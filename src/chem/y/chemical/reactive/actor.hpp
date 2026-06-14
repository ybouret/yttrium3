
//! \file

#ifndef Y_Chemical_Actor_Included
#define Y_Chemical_Actor_Included 1

#include "y/chemical/species.hpp"
#include "y/chemical/type/defs.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        enum Acting
        {
            AsSpec,
            AsConc
        };

        class Actor : public Object, public Entity
        {
        public:
            typedef CxxListOf<Actor> List;

            explicit Actor(const unsigned &, const Species &, const Acting);
            virtual ~Actor() noexcept;

            void massAction(XMul &X, const XReadable &C, const Level L) const;
            void massAction(XMul &X, const XReadable &C, const Level L, const xreal_t xi) const; //!< safe


            const unsigned nu;
            const Species &sp;
            const xreal_t  xn;   //!< nu as xreal
            const xreal_t  zero;
            Actor *        next;
            Actor *        prev;

        private:
            Y_Disable_Copy_And_Assign(Actor);
        };
    }

}

#endif // !Y_Chemical_Actor_Included
