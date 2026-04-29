//! \file

#ifndef Y_Handy_PlainList_Included
#define Y_Handy_PlainList_Included 1

#include "y/handy/list-proto.hpp"
#include "y/handy/cache/object.hpp"
#include "y/ability/releasable.hpp"

namespace Yttrium
{
    namespace Handy
    {

        template <typename NODE, typename THREADING_POLICY>
        class PlainList :
        public ListProto<NODE,ObjectCache,THREADING_POLICY>,
        public Releasable
        {
        public:
            inline explicit PlainList() {}

            inline PlainList(const PlainList &L) :
            ListProto<NODE,ObjectCache,THREADING_POLICY>(L),
            Releasable()
            {
            }
            

            inline virtual ~PlainList() noexcept
            {
            }

            inline virtual void release() noexcept
            {
                while(this->list.size>0)
                    this->cache->removeLiving(this->list.popTail());
                this->cache->release();
            }

        private:
            Y_Disable_Assign(PlainList);
        };

    }
}

#endif // !Y_Handy_PlainList_Included

