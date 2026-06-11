//! \file

#ifndef Y_Chemical_Weasel_Included
#define Y_Chemical_Weasel_Included 1

#include "y/singleton.hpp"
#include "y/chemical/formula.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        class Weasel : public Singleton<Weasel,ClassLockPolicy>
        {
        public:
            class Parser;
            static const char * const CallSign; //!< "Weasel";

        private:
            Y_Disable_Copy_And_Assign(Weasel);
        };

    }
}

#endif // !Y_Chemical_Weasel_Included

