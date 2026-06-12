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
            class Code;
            static const char * const CallSign; //!< "Weasel";
            static const Longevity    LifeTime = 0;
            
        private:
            Y_Disable_Copy_And_Assign(Weasel);
            friend class Singleton<Weasel,ClassLockPolicy>;
            
            explicit Weasel();
            virtual ~Weasel() noexcept;
            Code * const code;
        };

    }
}

#endif // !Y_Chemical_Weasel_Included

