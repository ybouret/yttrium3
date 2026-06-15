
#include "y/chemical/reactive/equilibrium/format.hpp"

namespace Yttrium
{
    namespace Chemical
    {


        EqFormat:: ~EqFormat() noexcept
        {
        }

        EqFormat:: EqFormat() noexcept :
        efmt(),
        rfmt(),
        pfmt()
        {}

        EqFormat:: EqFormat(const EqFormat &_) noexcept :
        efmt(_.efmt),
        rfmt(_.rfmt),
        pfmt(_.pfmt)
        {
        }

        void EqFormat:: enroll(const Equilibrium &eq) noexcept
        {
            Coerce(efmt).enroll(eq);
            Coerce(rfmt).enroll(eq.reac);
            Coerce(pfmt).enroll(eq.prod);
        }

        std::ostream & EqFormat:: print(std::ostream      &os,
                                        const Equilibrium &eq,
                                        const bool         wK) const
        {

            efmt.print(os,eq,Justify::Left) << " : ";
            return os << std::endl;
        }
    }

}
