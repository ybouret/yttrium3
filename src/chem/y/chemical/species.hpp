
//! \file

#ifndef Y_Chemical_Species_Included
#define Y_Chemical_Species_Included 1

#include "y/chemical/formula.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        class Species : public CountedObject, public Formula
        {
        public:
            explicit Species(const Formula &);
            virtual ~Species() noexcept;
            
            const int    z;
            const String name;

        private:
            Y_Disable_Copy_And_Assign(Species);
        };
    }

}

#endif // !Y_Chemical_Species_Included

