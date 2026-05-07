
//! \file

#ifndef Y_Associative_SuffixProto_Inluded
#define Y_Associative_SuffixProto_Inluded 1

#include "y/container/associative.hpp"
#include "y/core/tree.hpp"
#include "y/type/pulverize.hpp"

namespace Yttrium
{

    template <
    typename KEY,
    typename T,
    template <typename, typename> class NODE >
    class SuffixProto : public Associative<KEY, T>
    {
    public:
        typedef NODE<KEY, T>       Node;
        typedef Core::ListOf<Node> List; //!< living nodes
        typedef Core::PoolOf<Node> Pool; //!< zombie nodes

        inline explicit SuffixProto() : list(), tree(), pool()
        {
        }
        

        inline virtual ~SuffixProto() noexcept { release_(); }

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


        inline virtual size_t size()     const noexcept { return list.size; }
        inline virtual size_t capacity() const noexcept { return list.size+pool.size; }
        inline virtual void   free()           noexcept { free_();    }
        inline virtual void   release()        noexcept { release_(); }




    protected:
        List       list;
        Core::Tree tree;
        Pool       pool;


        inline bool insertLiving(Node * const node)
        {
            try
            {
                if(!tree.insert(node->key(),node) )
                {
                    storeLiving(node);
                    return false;
                }
                else
                {
                    list.pushTail(node);
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



    private:
        Y_Disable_Assign(SuffixProto);
        Y_Disable_Copy(SuffixProto);




    };

}

#endif // !Y_Associative_SuffixProto_Inluded

