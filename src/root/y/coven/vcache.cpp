#include "y/coven/vcache.hpp"

namespace Yttrium
{

    namespace Coven
    {
        VCache:: ~VCache() noexcept
        {
        }

        VCache:: VCache(const Metrics &metrics) :
        Concurrent::Mutex(),
        Metrics(metrics),
        vpool()
        {
        }

        size_t VCache:: count() const noexcept
        {
            return vpool.size;
        }

        void VCache:: cache(const size_t n)
        {
            Y_Lock(*this);
            for(size_t i=n;i>0;--i) vpool.store( new Vector(*this) );
        }

        Vector * VCache:: query()
        {
            Y_Lock(*this);
            assert(0==vpool.size || dimension==vpool.head->dimension);
            return vpool.size ? vpool.query() : new Vector(*this);
        }

        void VCache:: store(Vector * const v) noexcept
        {
            Y_Lock(*this);
            assert(v);
            assert(dimension==v->dimension);
            vpool.store(v)->ldz();
        }


        Vector * VCache:: query(const Vector &source)
        {
            Y_Lock(*this);
            assert(dimension==source.dimension);
            assert(dimension==source.size());
            if(vpool.size)
            {
                Vector * const target = vpool.query();
                try { return & ( *target = source ); }
                catch(...)   { store(target); throw; }
            }
            else
            {
                return new Vector(source);
            }
        }


    }

}


#include "y/core/pool/to-list.hpp"
#include "y/core/list/to-pool.hpp"

namespace Yttrium
{

    namespace Coven
    {
        void VCache:: gc(const uint8_t amount) noexcept
        {
            Y_Lock(*this);
            Vectors vlist;
            Core::PoolToList::Make(vlist,vpool).sortByDecreasingAddress();
            {
                const size_t newSize = NewSize(amount,vpool.size);
                while(vlist.size>newSize) delete vlist.popHead();
            }
            Core::ListToPool::Make(vpool,vlist);
        }
    }

}

