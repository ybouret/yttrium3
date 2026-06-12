
//! \file

#ifndef Y_Chemical_Species_Included
#define Y_Chemical_Species_Included 1

#include "y/chemical/formula.hpp"
#include "y/chemical/type/indexed.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        class Species :
        public CountedObject,
        public Formula,
        public Indexed
        {
        public:
            explicit Species(const Formula &, const size_t);
            virtual ~Species() noexcept;
            const int    z;

        private:
            Y_Disable_Copy_And_Assign(Species);
        };
    }

}

#endif // !Y_Chemical_Species_Included

