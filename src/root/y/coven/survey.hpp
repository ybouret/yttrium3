
//! \file

#ifndef Y_Coven_Survey_Included
#define Y_Coven_Survey_Included 1

#include "y/coven/vector.hpp"
#include "y/type/proxy.hpp"

namespace Yttrium
{

    namespace Coven
    {

        class Survey : public Proxy< const Vectors >
        {
        public:
            explicit Survey() noexcept;
            virtual ~Survey() noexcept;

        private:
            Y_Disable_Assign(Survey);
            const Vectors & locus() const noexcept;
            Vectors list;
        };

    }

}

#endif // !Y_Coven_Survey_Included

