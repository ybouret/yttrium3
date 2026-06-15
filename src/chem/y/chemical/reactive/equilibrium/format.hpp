
//! \file

#ifndef Y_Chemical_Equilibrium_Format_Included
#define Y_Chemical_Equilibrium_Format_Included 1

#include "y/chemical/reactive/equilibrium.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        class EqFormat
        {
        public:
            explicit EqFormat()        noexcept;
            virtual ~EqFormat()        noexcept;
            EqFormat(const EqFormat &) noexcept;

            void enroll(const Equilibrium &) noexcept;

            std::ostream & print(std::ostream      &os,
                                 const Equilibrium &eq,
                                 const bool         wK,
                                 const xreal_t      tK) const;

            const Assembly efmt;
            const Assembly rfmt;
            const Assembly pfmt;

        private:
            Y_Disable_Assign(EqFormat);
        };
    }

}

#endif // !Y_Chemical_Equilibrium_Format_Included

