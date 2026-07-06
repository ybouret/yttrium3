
#include "y/chemical/plexus/conservation/law/pcoef.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        namespace Conservation
        {
            const PCoef & PCoef:: operator*() const noexcept { return *this; }



            PCoef:: PCoef(const xreal_t cf_, const Species &sp_) noexcept :
            cf(cf_),
            sp(sp_),
            next(0),
            prev(0)
            {
            }

            PCoef:: ~PCoef() noexcept
            {
            }

            std::ostream & operator<<(std::ostream &os, const PCoef &self)
            {
                os << (double)self.cf << '*' <<  '[' << self.sp.name << ']';
                return os;
            }

            
        }

    }

}


