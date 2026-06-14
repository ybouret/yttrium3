

//! \file

#ifndef Y_Chemical_Actors_Included
#define Y_Chemical_Actors_Included 1

#include "y/chemical/reactive/actor.hpp"
#include "y/type/proxy.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        class Actors : public Proxy<const Actor::List>, public Entity
        {
        public:
            static const char * const CallSign;
            
            explicit Actors(const Acting);
            virtual ~Actors() noexcept;

            void hire(const unsigned nu, const Species &sp);
            bool hired(const Species &) const noexcept;

            void massAction(XMul &X, const XReadable &C, const Level L) const;
            void massAction(XMul &X, const XReadable &C, const Level L, const xreal_t xi) const; //!< safe

            apz  charge() const;

        private:
            Y_Disable_Copy_And_Assign(Actors);
            Y_Proxy_Decl();
            Actor::List  list;
            const Acting acting;
        };

    }
}

#endif // !Y_Chemical_Actors_Included

