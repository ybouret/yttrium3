
//! \file

#ifndef Y_Apex_Overseer_Included
#define Y_Apex_Overseer_Included 1


#include "y/singleton.hpp"
#include "y/calculus/alignment.hpp"

namespace Yttrium
{
    namespace Apex
    {
        class Overseer : public Singleton<Overseer,ClassLockPolicy>
        {
        public:
            static const char * const CallSign;
            static const Longevity    LifeTime         = 0;
            static const unsigned     StaticBlockShift = 14;
            static const size_t       StaticBlockBytes = size_t(1) << StaticBlockShift;
            static const size_t       NumStaticWords   = Alignment::WordsGEQ<StaticBlockBytes>::Count;
            static void *             StaticWords[ NumStaticWords ];

            void * acquireBlock(const unsigned blockShift);
            void   releaseBlock(void * const blockEntry, const unsigned blockShift) noexcept;

        private:
            Y_Disable_Copy_And_Assign(Overseer);
            friend class Singleton<Overseer,ClassLockPolicy>;
            explicit Overseer();
            virtual ~Overseer() noexcept;
        };
    }
}

#endif // !Y_Apex_Overseer_Included

