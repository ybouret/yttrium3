
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
                                        const bool         wK,
                                        const xreal_t      tK) const
        {
            static const char Sep[] = " : ";
            efmt.print(os,eq,Justify::Left) << Sep;
            rfmt.print(os,eq.reac,Justify::Right);
            os << ' ' << Equilibrium::Symbol << ' ';
            pfmt.print(os,eq.prod,Justify::Left);
            os << Sep;
            if(wK)
            {
                const xreal_t K  = Coerce(eq).K(tK);
                const real_t  p  = K.log10();
                os << "'10^(" << p << ")'";
            }
            return os << std::endl;
        }
    }

}
