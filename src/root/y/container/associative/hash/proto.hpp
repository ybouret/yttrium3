
//! \file

#ifndef Y_Associative_HashProto_Inluded
#define Y_Associative_HashProto_Inluded 1

#include "y/container/associative.hpp"
#include "y/core/htable.hpp"
#include "y/object.hpp"
#include "y/type/pulverize.hpp"
#include "y/core/list.hpp"
#include "y/core/pool.hpp"

namespace Yttrium
{
    namespace Core
    {
        //______________________________________________________________________
        //
        //
        //
        //! Node for Slots in HashTable
        //
        //
        //______________________________________________________________________
        template <typename NODE>
        class HashNode
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef ListOf<HashNode> Slot; //!< alias
            typedef PoolOf<HashNode> Pool; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param user data node
            inline HashNode(NODE * const user) noexcept : node(user), next(0), prev(0) { assert(0!=user); }
            inline ~HashNode() noexcept {} //!< cleanup

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            NODE * const node; //!< user's node
            HashNode *   next; //!< for list/pool
            HashNode *   prev; //!< for pool
        private:
            Y_Disable_Copy_And_Assign(HashNode); //!< discarded
        };

        //______________________________________________________________________
        //
        //
        //
        //! Manage Abstract Chained Hash Table
        //
        //
        //______________________________________________________________________
        template <typename NODE>
        class HashTable : public Object, public HTable
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef typename NODE::Key       Key;      //!< alias
            typedef typename NODE::ConstKey  ConstKey; //!< alias
            typedef typename NODE::ParamKey  ParamKey; //!< alias
            typedef HashNode<NODE>           HNode;    //!< alias
            typedef typename HNode::Slot     HSlot;    //!< alias
            typedef typename HNode::Pool     HPool;    //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param minSlots minimal table slots
            inline explicit HashTable(const size_t minSlots) :
            Object(),
            HTable(minSlots,sizeof(HSlot)),
            count(0),
            slots( static_cast<HSlot *>(entry) ),
            zpool()
            {
            }

            //! cleanup: MUST have count==0
            inline virtual ~HashTable() noexcept { quit(); }


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! try to insert new node
            /**
             \param node new, unlinked node: taken care of in case of error
             \param pool where to return node in case of error
             \return true iff node was insert
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
                    NODE * const mine = hn->node;
                    if(hkey == mine->hkey && key == mine->key() )
                    {
                        slot.moveToHead(hn); // for next search...
                        return mine;
                    }
                }
                return 0;
            }

            //! remove
            /**
             \param hkey hash key
             \param key  key
             \param list extract data from it if found
             \param pool put extracted data if found
             \return true if node was removed
             */
            inline bool remove(const size_t  hkey,
                               ConstKey &    key,
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
            /**
             \param list source list
             \param pool target pool
             */
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


            //! steal content \param other another table
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

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t  count; //!< items in table
            HSlot * const slots; //!< allocated tsize slots
            HPool         zpool; //!< pool of zombie hash nodes

        private:
            Y_Disable_Copy_And_Assign(HashTable); //!< discarded
        };
    }


    //__________________________________________________________________________
    //
    //
    //
    //! Hash container prototype (up to insert)
    //
    //
    //__________________________________________________________________________
    template <
    typename NODE,
    template <typename,typename> class ASSOCIATIVE,
    typename HASHER
    >
    class HashProto : public ASSOCIATIVE<typename NODE::Key, typename NODE::Type>
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef typename NODE::Key       Key;       //!< alias
        typedef typename NODE::ConstKey  ConstKey;  //!< alias
        typedef typename NODE::ParamKey  ParamKey;  //!< alias
        typedef typename NODE::Type      Type;      //!< alias
        typedef typename NODE::ConstType ConstType; //!< alias
        typedef typename NODE::ParamType ParamType; //!< alias
        typedef Core::HashTable<NODE>    Table;     //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup \param minTableSize minimal slots in table
        inline HashProto(const size_t minTableSize) :
        list(),
        pool(),
        htab( new Table(minTableSize) ),
        hash()
        {
            
        }

        //! cleanup
        inline virtual ~HashProto() noexcept
        {
            release_();
            Destroy(htab);
        }

        //! display
        inline friend std::ostream & operator<<(std::ostream &os, const HashProto &self)
        {
            return os << self.list;
        }


        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________

        //! [Recyclable] free content, keep memory
        inline virtual void free() noexcept
        {
            htab->free(list,pool);
        }

        //! [Releasable] free content, release maximum memory
        inline virtual void release() noexcept
        {
            release_();
        }

        //! [Container] \return items in container
        inline virtual size_t size() const noexcept
        {
            assert(list.size==htab->count);
            return list.size;
        }

        //! [Container] \return current capacity
        inline virtual size_t capacity() const noexcept
        {
            assert(list.size==htab->count);
            return list.size + pool.size;
        }

        //! [Associative] \param key key to search \return item address if found, 0 otherwise
        inline virtual Type * search(ParamKey key)
        {
            NODE * const node = htab->search( hash(key), key);
            return node ? & **node : 0;
        }

        //! [Associative] \param key key to search \return const item address if found, 0 otherwise
        inline virtual ConstType * search(ParamKey key) const
        {
            const NODE * const node = htab->search( hash(key), key);
            return node ? & **node : 0;
        }

        //! [Associative] \param key key to remove \return true iff found and removed item with key
        inline virtual bool remove(ParamKey key)
        {
            return htab->remove( hash(key), key, list, pool);
        }


        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
    protected:
        Core::ListOf<NODE> list; //!< living list
        Core::PoolOf<NODE> pool; //!< zombie pool
        Table * const      htab; //!< table
    public:
        mutable HASHER     hash; //!< hasher

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
    protected:
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

    private:
        //! release all nodes
        inline void release_() noexcept
        {
            htab->clear();
            htab->quit();
            while(list.size) Object::ReleaseZombie( Pulverized(list.popHead()) );
            while(pool.size) Object::ReleaseZombie( pool.query() );
        }

        Y_Disable_Copy_And_Assign(HashProto);
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
    };

}

#endif // !Y_Associative_HashProto_Inluded

