//! \file

#ifndef Y_Handy_ListProto_Included
#define Y_Handy_ListProto_Included 1

#include "y/core/list.hpp"
#include "y/container/iter/linked.hpp"
#include "y/ability/lockable.hpp"


namespace Yttrium
{

    namespace Handy
    {

        template <
        typename                           NODE,
        template <typename,typename> class CACHE,
        typename                           THREADING_POLICY
        >
        class ListProto
        {
        public:
            typedef NODE                         NodeType;
            typedef typename NodeType::ParamType ParamType;
            typedef Core::ListOf<NODE>           CoreType;
            typedef typename NodeType::Type      Type;
            typedef typename NodeType::ConstType ConstType;

            inline explicit ListProto() : list(), cache() {}

            inline explicit ListProto(const CACHE<NODE,THREADING_POLICY> &sc) :
            list(), cache(sc) {}

            inline explicit ListProto(const ListProto &other) : list(), cache(other.cache)
            {
                Y_Lock(*cache);
                try
                {
                    for(const NodeType *node=other.list.head;node;node=node->next)
                        list.pushTail(cache->mirror(node));
                }
                catch(...) { free_(); throw; }
            }

            inline virtual ~ListProto() noexcept { free_(); }

            inline friend std::ostream & operator<<(std::ostream &os, const ListProto &self)
            {
                return os << self.list;
            }

            inline size_t size()     const noexcept { return list.size; }

            inline void popTail() noexcept
            {
                Y_Lock(*cache);
                cache->banish( list.popTail() );
            }

            inline void popHead() noexcept
            {
                Y_Lock(*cache);
                cache->banish( list.popTail() );
            }

            inline void pushTail(ParamType args)
            {
                Y_Lock(*cache);
                list.pushTail( cache->summon(args) );
            }

            inline void pushHead(ParamType args)
            {
                Y_Lock(*cache);
                list.pushHead( cache->summon(args) );
            }

            inline ListProto & operator<<(ParamType args)
            {
                pushTail(args); return *this;
            }

            inline ListProto & operator>>(ParamType args)
            {
                pushHead(args); return *this;
            }

            inline virtual void free() noexcept { free_(); }



            inline Type &      head()       noexcept { assert(list.head); return **list.head; }
            inline Type &      tail()       noexcept { assert(list.tail); return **list.tail; }
            inline ConstType & head() const noexcept { assert(list.head); return **list.head; }
            inline ConstType & tail() const noexcept { assert(list.tail); return **list.tail; }

            inline ListProto & operator<<( const ListProto & other )
            {
                { ListProto tmp(other); list.mergeTail(tmp.list); }
                return *this;
            }

            inline ListProto & operator>>( const ListProto & other )
            {
                { ListProto tmp(other); list.mergeHead(tmp.list); }
                return *this;
            }



        protected:
            Core::ListOf<NODE>           list;

        public:
            CACHE<NODE,THREADING_POLICY> cache;

        private:
            Y_Disable_Assign(ListProto);
            inline void free_() noexcept
            {
                Y_Lock(*cache);
                while( list.size ) cache->banish( list.popTail() );
            }

        public:
            //__________________________________________________________________
            //
            //
            // Iterators
            //
            //__________________________________________________________________
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            typedef Iter::Linked<Iter::Forward,NODE>       Iterator;
            typedef Iter::Linked<Iter::Forward,const NODE> ConstIterator;

            inline Iterator      begin()       noexcept { return list.head; }
            inline Iterator      end()         noexcept { return 0; }
            inline ConstIterator begin() const noexcept { return list.head; }
            inline ConstIterator end()   const noexcept { return 0; }

            typedef Iter::Linked<Iter::Reverse,NODE>       ReverseIterator;
            typedef Iter::Linked<Iter::Reverse,const NODE> ConstReverseIterator;

            inline ReverseIterator      rbegin()       noexcept { return list.tail; }
            inline ReverseIterator      rend()         noexcept { return 0; }
            inline ConstReverseIterator rbegin() const noexcept { return list.tail; }
            inline ConstReverseIterator rend()   const noexcept { return 0; }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)


        };


    }

}

#endif // !Y_Handy_ListProto_Included

