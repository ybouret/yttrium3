
//! \file

#ifndef Y_List_Included
#define Y_List_Included 1

#include "y/container/sequence.hpp"
#include "y/object.hpp"
#include "y/type/copy-of.hpp"
#include "y/type/replicate.hpp"
#include "y/type/destruct.hpp"
#include "y/type/with-at-least.hpp"
#include "y/ability/recyclable.hpp"
#include "y/ability/releasable.hpp"
#include "y/ability/expandable.hpp"
#include "y/container/writable.hpp"
#include "y/ability/releasable.hpp"
#include "y/core/list.hpp"
#include "y/core/pool.hpp"
#include "y/container/iter/linked.hpp"

namespace Yttrium
{


    //__________________________________________________________________________
    //
    //
    //
    //! List
    //
    //
    //__________________________________________________________________________
    template <typename T>
    class List :
    public Sequence<T,Writable<T>>,
    public Expandable<Releasable>,
    public Recyclable
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Declare(T,Type);                         //!< aliases
        typedef Sequence<T, Writable<T> > SequenceType; //!< alias

        class Node
        {
        public:
            Y_Args_Expose(T,Type);
            typedef Core::ListOf<Node> List;
            typedef Core::PoolOf<Node> Pool;

            inline Node(ConstType &args) : data(args), next(0), prev(0) {}
            inline ~Node() noexcept {}

            inline Type      & operator*()       noexcept { return data; }
            inline ConstType & operator*() const noexcept { return data; }


        private:
            MutableType data;
        public:
            Node *      next;
            Node *      prev;

        private:
            Y_Disable_Copy_And_Assign(Node);
        };

        typedef Core::ListOf<Node> ListType;
        typedef Core::PoolOf<Node> PoolType;

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        inline explicit List() noexcept : list(), pool() {}
        inline virtual ~List() noexcept { release_(); }

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        inline virtual size_t size()     const noexcept { return list.size; }
        inline virtual size_t capacity() const noexcept { return list.size+pool.size; }

        inline void reserve(const size_t n) {
            for(size_t i=n;i>0;--i) pool.store( CreateZombie() );
        }

        inline virtual void free() noexcept {
            while(list.size) pool.store( Destructed(list.popTail()) );
        }

        inline virtual void release() noexcept { release_(); }

        inline virtual void popTail() noexcept
        {
            assert(list.size); assert(list.tail);
            pool.store( Destructed(list.popTail()) );
        }

        inline virtual void popHead() noexcept
        {
            assert(list.size); assert(list.head);
            pool.store( Destructed(list.popHead()) );
        }

        inline virtual void pushTail(ParamType args)
        {
            Node * const node = queryNode();
            try { list.pushTail( new (node) Node(args) ); }
            catch(...) { pool.store(node); throw; }
        }

        inline virtual void pushHead(ParamType args)
        {
            Node * const node = queryNode();
            try { list.pushTail( new (node) Node(args) ); }
            catch(...) { pool.store(node); throw; }
        }

        //______________________________________________________________________
        //
        //
        // Iterators
        //
        //______________________________________________________________________
        typedef Iter::Linked<Iter::Forward,Node>       Iterator;
        typedef Iter::Linked<Iter::Forward,const Node> ConstIterator;

        inline Iterator      begin()       noexcept { return list.head; }
        inline Iterator      end()         noexcept { return 0; }
        inline ConstIterator begin() const noexcept { return list.head; }
        inline ConstIterator end()   const noexcept { return 0; }

        typedef Iter::Linked<Iter::Reverse,Node>       ReverseIterator;
        typedef Iter::Linked<Iter::Reverse,const Node> ConstReverseIterator;

        inline ReverseIterator      rbegin()       noexcept { return list.tail; }
        inline ReverseIterator      rend()         noexcept { return 0; }
        inline ConstReverseIterator rbegin() const noexcept { return list.tail; }
        inline ConstReverseIterator rend()   const noexcept { return 0; }
        
    private:
        Y_Disable_Copy_And_Assign(List); //!< discarded
        ListType list; //!< alive nodes
        PoolType pool; //!< zombie nodes

        inline virtual ConstType & ask(const size_t indx) const noexcept {
            return **list.fetch(indx);
        }

        inline virtual ConstType & getTail() const noexcept {
            assert(list.tail); return **list.tail;
        }

        inline virtual ConstType & getHead() const noexcept {
            assert(list.head); return **list.head;
        }


        inline static Node * CreateZombie()
        { return Object::AcquireZombie<Node>(); };

        inline static void   DeleteZombie(Node * const node) noexcept
        { Object::ReleaseZombie(node); }

        inline Node * queryNode() { return pool.size ? pool.query() : CreateZombie(); }

        inline void release_() noexcept
        {
            while(list.size) Object::ReleaseZombie( Destructed(list.popTail()) );
            while(pool.size) Object::ReleaseZombie( pool.query() );
        }
    };

}

#endif // !Y_List_Included
