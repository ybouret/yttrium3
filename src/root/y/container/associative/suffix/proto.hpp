
//! \file

#ifndef Y_Associative_SuffixProto_Inluded
#define Y_Associative_SuffixProto_Inluded 1

#include "y/container/associative.hpp"
#include "y/core/tree.hpp"
#include "y/type/pulverize.hpp"

namespace Yttrium
{

    namespace Core
    {
        struct SuffixCommon
        {
            static void InsertFailureException();
        };
    }

    //__________________________________________________________________________
    //
    //
    //
    //! Prototype for Suffix[Set|Map]
    //
    //
    //__________________________________________________________________________
    template <
    typename KEY,
    typename T,
    template <typename, typename> class NODE >
    class SuffixProto :
    public Associative<KEY,T>,
    public Releasable
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef NODE<KEY, T>       Node; //!< alias
        typedef Core::ListOf<Node> List; //!< living nodes
        typedef Core::PoolOf<Node> Pool; //!< zombie nodes
        Y_Args_Declare(T,Type);          //!< aliases
        Y_Args_Declare(KEY,Key);         //!< aliases

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        //! setup empty
        inline explicit SuffixProto() : list(), tree(), pool()
        {
        }
        
        inline SuffixProto(const SuffixProto &proto) :
        Associative<KEY,T>(), Releasable(),
        list(), tree(), pool()
        {
            duplicate(proto);
        }


    public:
        //! cleanup
        inline virtual ~SuffixProto() noexcept { release_(); }



        //! display
        inline friend std::ostream & operator<<(std::ostream &os, const SuffixProto &proto)
        {
            os << '{';
            const Node * node = proto.list.head;
            if(node) {
                os << *node;
                for(node=node->next;node;node=node->next) os << ',' << *node;
            }
            return os << '}';
        }

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        inline virtual size_t size()     const noexcept { return list.size; }
        inline virtual size_t capacity() const noexcept { return list.size+pool.size; }
        inline virtual void   free()           noexcept { free_();    }
        inline virtual void   release()        noexcept { release_(); }

        inline virtual Type * search(ParamKey key) noexcept
        {
            Core::TreeNode * const node = tree.search(key); if(!node) return 0;
            void * const           addr = node->data;       if(!addr) return 0;
            return & **static_cast<Node *>(addr);
        }


        inline virtual ConstType * search(ParamKey key) const noexcept
        {
            const Core::TreeNode * const node = tree.search(key); if(!node) return 0;
            const void * const           addr = node->data;       if(!addr) return 0;
            return & **static_cast<const Node *>(addr);
        }

        inline virtual bool remove(ParamKey key) noexcept
        {
            assert(tree.size==list.size);
            void * const addr = tree.remove(key); if(!addr) return false;
            Node * const node = static_cast<Node *>(addr);
            storeLiving(list.pop(node));
            assert(tree.size==list.size);
            return true;
        }


        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
    protected:
        List       list; //!< living nodes
        Core::Tree tree; //!< tree of node addresses
        Pool       pool; //!< zombie nodes


#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
        inline bool insertLiving(Node * const node)
        {
            assert(tree.size==list.size);
            try
            {
                if(!tree.insert(node->key(),node) )
                {
                    storeLiving(node);
                    assert(tree.size==list.size);
                    return false;
                }
                else
                {
                    list.pushTail(node);
                    assert(tree.size==list.size);
                    return true;
                }
            }
            catch(...) { this->storeLiving(node); throw; }
        }


        inline void free_() noexcept
        {
            tree.free();
            while(list.size) storeLiving(list.popTail());
        }

        inline void release_() noexcept
        {
            tree.release();
            while(list.size) RemoveLiving(list.popTail());
            while(pool.size) RemoveZombie(pool.query());
        }


        inline Node * queryZombie() {
            return pool.size ? pool.query() : Object::AcquireZombie<Node>();
        }


        inline void storeZombie(Node * const node) noexcept
        {
            assert(node); assert(0==node->next); assert(0==node->prev);
            pool.store(node);
        }

        inline void storeLiving(Node * const node) noexcept {
            storeZombie( Pulverized(node) );
        }

        static inline void RemoveZombie(Node * const node) noexcept {
            assert(node);
            Object::ReleaseZombie(node);
        }

        static inline void RemoveLiving(Node * const node) noexcept {
            assert(node);
            RemoveZombie( Pulverized(node) );
        }

        inline void duplicate(const SuffixProto &other)
        {
            try
            {
                for(const Node * node = other.list.head; node; node=node->next)
                {
                    // create living node
                    Node * const mine = queryZombie();
                    try { new (mine) Node(*node); }
                    catch(...) { storeZombie(mine); throw; }

                    // MUST insert
                    if(!insertLiving(mine))
                        Core::SuffixCommon::InsertFailureException();
                }
            }
            catch(...) { release_(); throw; }
        }

#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)



    private:
        Y_Disable_Assign(SuffixProto); //!< discarded
        //Y_Disable_Copy(SuffixProto);

    };

}

#endif // !Y_Associative_SuffixProto_Inluded

