
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
        prod(AsSpec)
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


    }

}


