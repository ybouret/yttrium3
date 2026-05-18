
//! \file

#ifndef Y_Associative_HashProto_Inluded
#define Y_Associative_HashProto_Inluded 1

#include "y/container/associative.hpp"
#include "y/core/htable.hpp"
#include "y/object.hpp"
#include "y/type/pulverize.hpp"
#include "y/core/list.hpp"
#include "y/core/pool.hpp"
#include "y/type/args.hpp"


namespace Yttrium
{
    namespace Core
    {
        template <typename NODE>
        class HashNode
        {
        public:
            typedef ListOf<HashNode> Slot;
            typedef PoolOf<HashNode> Pool;

            inline HashNode(NODE * const user) noexcept :
            node(user), next(0), prev(0)
            {
                assert(0!=user);
            }

            inline ~HashNode() noexcept {}



            NODE * const node;
            HashNode *   next;
            HashNode *   prev;

        private:
            Y_Disable_Copy_And_Assign(HashNode);
        };

        template <typename NODE>
        class HashTable : public Object, public HTable
        {
        public:
            typedef typename NODE::Key       Key;
            typedef typename NODE::ConstKey  ConstKey;
            typedef typename NODE::ParamKey  ParamKey;
            typedef HashNode<NODE>           HNode;
            typedef typename HNode::Slot     HSlot;
            typedef typename HNode::Pool     HPool;


            inline explicit HashTable(const size_t minSlots) :
            Object(),
            HTable(minSlots,sizeof(HSlot)),
            count(0),
            slots( static_cast<HSlot *>(entry) ),
            zpool()
            {
            }

            inline virtual ~HashTable() noexcept { quit(); }

            //! try to insert new node
            /**
             \param node new, unlinked node
             \param pool where to return node in case of error
             */
            inline bool insert(NODE * const   node,
                               PoolOf<NODE> & pool)
            {
                assert(node);
                assert(0==node->next);
                assert(0==node->prev);
                try
                {
                    const size_t hkey = node->hkey;
                    HSlot &      slot = slots[hkey&tmask];
                    {
                        ConstKey & key = node->key();
                        for(const HNode *hn=slot.head;hn;hn=hn->next)
                        {
                            const NODE * const mine = hn->node;
                            if(hkey == mine->hkey && key == mine->key() )
                            {
                                pool.store( Pulverized(node) );
                                return false;
                            }
                        }
                    }

                    slot.pushHead( new (zpool.size ? zpool.query() : Object:: AcquireZombie<HNode>()) HNode(node) );
                    ++Coerce(count);
                    return true;
                }
                catch(...)
                {
                    pool.store( Pulverized(node) ); throw;
                }
            }

            //! search \param hkey hash key \param key key \return matching NODE, 0 if not found
            inline const NODE * search(const size_t hkey, ConstKey &key) const
            {
                const HSlot & slot = slots[hkey&tmask];
                for(const HNode *hn=slot.head;hn;hn=hn->next)
                {
                    const NODE * const mine = hn->node;
                    if(hkey == mine->hkey && key == mine->key() ) return mine;
                }
                return 0;
            }

            //! search with optimization \param hkey hash key \param key key \return matching NODE, 0 if not found
            inline NODE * search(const size_t hkey, ConstKey &key)
            {
                HSlot & slot = slots[hkey&tmask];
                for(HNode *hn=slot.head;hn;hn=hn->next)
                {
                    const NODE * const mine = hn->node;
                    if(hkey == mine->hkey && key == mine->key() )
                    {
                        slot.moveToHead(hn); // for next search...
                        return mine;
                    }
                }
                return 0;
            }

            //! remove \param hkey hash key \param key key \return true if node was removed
            inline bool remove(const size_t hkey,
                               ConstKey &key,
                               ListOf<NODE> &list,
                               PoolOf<NODE> &pool)
            {
                HSlot & slot = slots[hkey&tmask];
                for(HNode *scan=slot.head;scan;scan=scan->next)
                {
                    NODE * const mine = scan->node;
                    if(hkey == mine->hkey && key == mine->key() )
                    {
                        assert(list.owns(mine));
                        pool.store(  Pulverized( list.pop(mine) ) );
                        zpool.store( Pulverized( slot.pop(scan) ) );
                        --Coerce(count);
                        return true;
                    }
                }
                return false;
            }

            //! free content, keep memory
            inline void free( ListOf<NODE> &list, PoolOf<NODE> &pool ) noexcept
            {
                for(size_t i=0;i<tsize;++i)
                {
                    HSlot & slot = slots[i];
                    while(slot.size)
                    {
                        HNode * const scan = slot.popHead(); assert(scan->node);
                        NODE *  const node = scan->node;     assert(list.owns(node));
                        pool.store(  Pulverized( list.pop(node) ) );
                        zpool.store( Pulverized(scan) );
                    }
                }
                Coerce(count) = 0;
            }

            //! FORCE erase content, NODEs are not taken care of
            inline void clear() noexcept
            {
                for(size_t i=0;i<tsize;++i) {
                    HSlot & slot = slots[i];
                    while(slot.size)
                        zpool.store( Pulverized(slot.popHead()));
                }
                Coerce(count) = 0;
            }

            //! release pool and EMPTY table
            inline void quit() noexcept
            {
                assert(0==count);
                while(zpool.size) Object::ReleaseZombie( zpool.query() );
            }


            inline void steal(HashTable &other) noexcept
            {
                assert(0==count);
                for(size_t i=0;i<other.tsize;++i) {
                    HSlot & source = other.slots[i];
                    while(source.size)
                    {
                        HNode * const scan = source.popHead();
                        slots[scan->node->hkey&tmask].pushTail(scan);
                        --Coerce(source.count);
                        ++Coerce(count);
                    }
                }
                zpool.merge(other.zpool);
                assert(0==other.count);
            }


            const size_t  count;
            HSlot * const slots;
            HPool         zpool;

        private:
            Y_Disable_Copy_And_Assign(HashTable);
        };
    }

    template <typename NODE>
    class HashProto
    {
    public:
        typedef typename NODE::Key       Key;
        typedef typename NODE::ConstKey  ConstKey;
        typedef typename NODE::ParamKey  ParamKey;
        typedef typename NODE::Type      Type;
        typedef typename NODE::ConstType ConstType;
        typedef typename NODE::ParamType ParamType;
        typedef Core::HashTable<NODE>    Table;

        inline HashProto(const size_t minTableSize) :
        list(),
        pool(),
        htab( new Table(minTableSize) )
        {
            
        }



        inline virtual ~HashProto() noexcept
        {
            release_();
            Destroy(htab);
        }

        inline friend std::ostream & operator<<(std::ostream &os, const HashProto &self)
        {
            return os << self.list;
        }


        inline virtual void free() noexcept
        {
            htab->free(list,pool);
        }

        inline virtual void release() noexcept
        {
            release_();
        }

        inline bool insertNode(NODE * const node)
        {
            assert(0!=node); assert(0==node->next); assert(0==node->prev);
            assert(0!=htab);
            if( htab->insert(node,pool) )
            {
                list.pushTail( node );
                return true;
            }
            else
            {
                return false;
            }
        }


    protected:


        Core::ListOf<NODE> list; //!< living list
        Core::PoolOf<NODE> pool; //!< zombie pool
        Table * const      htab; //!< table

        inline void release_() noexcept
        {
            htab->clear();
            htab->quit();
            while(list.size) Object::ReleaseZombie( Pulverized(list.popHead()) );
            while(pool.size) Object::ReleaseZombie( pool.query() );
        }

    };

}

#endif // !Y_Associative_HashProto_Inluded

