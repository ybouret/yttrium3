
//! \file

#ifndef Y_Handy_ObjectCache_Included
#define Y_Handy_ObjectCache_Included 1

#include "y/handy/cache/defs.hpp"
#include "y/core/pool.hpp"
#include "y/core/pool/to-list.hpp"
#include "y/core/list/to-pool.hpp"
#include "y/ability/caching.hpp"

namespace Yttrium
{
    namespace Handy
    {
        //______________________________________________________________________
        //
        //
        //
        //! Cache with object level pooling
        //
        //
        //______________________________________________________________________
        template <typename NODE, typename THREADING_POLICY>
        class ObjectCache : public THREADING_POLICY, public Caching
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_HandyCache_Decl();                     //!< aliases
            typedef Core::PoolOf<NodeType> PoolType; //!< alias
            typedef Core::ListOf<NodeType> ListType; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            inline explicit ObjectCache() :
            ThreadingPolicy(),
            Caching(),
            zpool()
            {

            }

            //! duplicate (do nothing)
            inline ObjectCache(const ObjectCache &) :
            ThreadingPolicy(),
            Caching(),
            zpool()
            {

            }

            //! cleanup
            inline virtual ~ObjectCache() noexcept { release_(); }

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            inline virtual void   release()      noexcept { release_(); }
            inline virtual size_t count()  const noexcept { return zpool.size; }
            inline virtual void   cache(const size_t n)
            {
                Y_Must_Lock();
                for(size_t i=n;i>0;--i)
                    zpool.store( LightObject::AcquireZombie<NodeType>() );
            }

            inline virtual void gc(const uint8_t amount) noexcept
            {
                Y_Must_Lock();
                ListType zlist;
                Core::PoolToList::Make(zlist,zpool).sortByDecreasingAddress();
                {
                    const size_t newSize = NewSize(amount,zlist.size);
                    while(zlist.size>newSize)
                        LightObject::ReleaseZombie( zlist.popHead() );
                }
                Core::ListToPool::Make(zpool,zlist);
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! summon new node
            /**
             \param args for constructor
             \return constructed node
             */
            inline NodeType * summon(ParamType args) {
                Y_Must_Lock();
                NodeType * const node = zpool.size ? zpool.query() : LightObject::AcquireZombie<NodeType>();
                try { return new (node) NodeType(args); }
                catch(...) {
                    zpool.store( NodeAPI::Clear(node) );
                    throw;
                }
            }

            //! banish living node, keep zombie \param alive living node
            inline void banish(NodeType * const alive) noexcept
            {
                Y_Must_Lock();
                assert(alive);
                zpool.store( Pulverized(alive) );
            }

            //! remove living node \param alive living node
            inline virtual void removeLiving(NodeType * const alive) noexcept
            {
                Y_Must_Lock();
                assert(alive);
                LightObject::ReleaseZombie( Pulverized(alive) );
            }

            //! remove zombie node \param zombie zombie node
            inline virtual void removeZombie(NodeType * const zombie) noexcept
            {
                Y_Must_Lock();
                assert(zombie);
                LightObject::ReleaseZombie( zombie );
            }


            inline ObjectCache *       operator->()       noexcept { return  this; } //!< \return API
            inline const ObjectCache * operator->() const noexcept { return  this; } //!< \return API
            inline Lockable &          operator*()        noexcept { return *this; } //!< \return lockable


        private:
            Y_Disable_Assign(ObjectCache); //!< discarded
            PoolType zpool;                //!< pool of zombies

            //! release all pool
            inline void release_() noexcept
            {
                Y_Must_Lock();
                while( zpool.size ) LightObject::ReleaseZombie( zpool.query() );
            }
        };

    }

}

#endif // !Y_Handy_ObjectCache_Included

