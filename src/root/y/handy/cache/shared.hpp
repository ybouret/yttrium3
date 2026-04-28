//! \file

#ifndef Y_Handy_SharedCache_Included
#define Y_Handy_SharedCache_Included 1

#include "y/handy/cache/object.hpp"
#include "y/pointer/arc.hpp"
#include "y/object/counted.hpp"

namespace Yttrium
{
    namespace Handy
    {

        template <typename NODE, typename THREADING_POLICY>
        class SharedCache
        {
        public:
            Y_HandyCache_Decl();
            typedef ObjectCache<NODE,ThreadingPolicy> InnerCache;
            class Code : public CountedObject, public InnerCache
            {
            public:
                inline explicit Code() : CountedObject(), InnerCache() {}
                inline virtual ~Code() noexcept {}
            private:
                Y_Disable_Copy_And_Assign(Code);
            };

            inline explicit SharedCache() : code( new Code() )
            {
            }

            inline SharedCache(const SharedCache &sc) noexcept : code( sc.code )
            {
            }


            inline virtual ~SharedCache() noexcept
            {
            }

            inline InnerCache       * operator->() noexcept       { return & *code; }
            inline const InnerCache * operator->() const noexcept { return & *code; }


        private:
            Y_Disable_Assign(SharedCache);
            ArcPtr<Code> code;
        };

    }

}

#endif // !Y_Handy_SharedCache_Included

