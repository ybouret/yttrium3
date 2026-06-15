
//! \file

#ifndef Y_Chemical_Components_Included
#define Y_Chemical_Components_Included 1

#include "y/chemical/reactive/actors.hpp"
#include "y/chemical/type/assembly.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        class Components : public Indexed
        {
        public:
            explicit Components(const String &, const size_t);
            virtual ~Components() noexcept;

            void addReac(const unsigned nu, const Species &sp);
            void addProd(const unsigned nu, const Species &sp);

            bool  electroneutral() const;
            bool  atLeastOneItem() const;

            xreal_t massAction(const xreal_t K, XMul &X, const XReadable &C, const Level L) const;
            xreal_t massAction(const xreal_t K, XMul &X, const XReadable &C, const Level L, const xreal_t xi) const;


            const Actors   reac;
            const Actors   prod;
            const xreal_t  one;

        private:
            Y_Disable_Copy_And_Assign(Components);
            void checkUnused(const char * const, const Species &) const;
        };

    }
}

#endif // !Y_Chemical_Components_Included

