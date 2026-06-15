
#include "y/chemical/reactive/components.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        Components:: ~Components() noexcept
        {
        }

        Components:: Components(const String &eqName, const size_t eqIndx) :
        Indexed(eqName,eqIndx),
        reac(AsSpec),
        prod(AsSpec),
        one(1)
        {

        }

        void Components:: checkUnused(const char *const fn, const Species &sp) const
        {
            const char * const id   = sp.name.c_str();
            if(reac.hired(sp)) throw Specific::Exception(fn,"'%s' already in reactants",id);
            if(prod.hired(sp)) throw Specific::Exception(fn,"'%s' already in products",id);
        }

        void Components:: addReac(const unsigned nu, const Species &sp)
        {
            static const char  fn[] = "Components::addReac";
            checkUnused(fn,sp);
            Coerce(reac).hire(nu,sp);
        }

        void Components:: addProd(const unsigned nu, const Species &sp)
        {
            static const char  fn[] = "Components::addProd";
            checkUnused(fn,sp);
            Coerce(prod).hire(nu,sp);
        }

        bool Components:: electroneutral() const
        {
            return reac.charge() == prod.charge();
        }

        bool  Components:: atLeastOneItem() const
        {
            return reac->size>0 || prod->size>0;
        }

        xreal_t Components:: massAction(const xreal_t     K,
                                        XMul &            X,
                                        const XReadable & C,
                                        const Level       L) const
        {
            X.set(K); prod.massAction(X,C,L);
            const xreal_t lhs = X();

            X.set(one); reac.massAction(X,C,L);
            const xreal_t rhs = X();

            return lhs-rhs;
        }

        xreal_t Components:: massAction(const xreal_t K, XMul &X, const XReadable &C, const Level L, const xreal_t xi) const
        {
            X.set(K); prod.massAction(X,C,L,xi);
            const xreal_t lhs = X();

            X.set(one); reac.massAction(X,C,L,-xi);
            const xreal_t rhs = X();

            return lhs-rhs;
        }



    }

}


