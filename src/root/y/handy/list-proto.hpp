//! \file

#ifndef Y_Handy_ListProto_Included
#define Y_Handy_ListProto_Included 1

#include "y/type/proxy.hpp"
#include "y/core/list.hpp"
#include "y/container/iter/linked.hpp"
#include "y/ability/lockable.hpp"
#include "y/ability/recyclable.hpp"


namespace Yttrium
{

    namespace Handy
    {

        //______________________________________________________________________
        //
        //
        //
        //! Prototype for all lists
        //
        //
        //______________________________________________________________________
        template <
        typename                           NODE,
        template <typename,typename> class CACHE,
        typename                           THREADING_POLICY
        >
        class ListProto : public Proxy< Core::ListOf<NODE> >, public Recyclable
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef NODE                         NodeType;  //!< alias
            typedef typename NodeType::ParamType ParamType; //!< alias
            typedef Core::ListOf<NODE>           CoreList;  //!< alias
            typedef typename NodeType::Type      Type;      //!< alias
            typedef typename NodeType::ConstType ConstType; //!< alias
            typedef Proxy<CoreList>              ProxyType; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup empty
            inline explicit ListProto() : ProxyType(), list(), cache() {}

            //! setup with existing cache \param sc shared cache (should be)
            inline explicit ListProto(const CACHE<NODE,THREADING_POLICY> &sc) :
            ProxyType(),
            list(),
            cache(sc) {}

            //! duplicate \param other
            inline explicit ListProto(const ListProto &other) :
            ProxyType(),
            Recyclable(),
            list(), cache(other.cache)
            {
                Y_Lock(*cache);
                try
                {
                    for(const NodeType *node=other.list.head;node;node=node->next)
                        list.pushTail(cache->mirror(node));
                }
                catch(...) { free_(); throw; }
            }

            //! cleanup
            inline virtual ~ListProto() noexcept { free_(); }

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            inline virtual void free() noexcept { free_(); }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            inline size_t size() const noexcept { return list.size; } //!< \return current size


            //! remove tail node
            inline void popTail() noexcept
            {
                Y_Lock(*cache);
                cache->banish( list.popTail() );
            }

            //! remove head node
            inline void popHead() noexcept
            {
                Y_Lock(*cache);
                cache->banish( list.popTail() );
            }

            //! push new value \param args compatible value
            inline void pushTail(ParamType args)
            {
                Y_Lock(*cache);
                list.pushTail( cache->summon(args) );
            }

            //! push new value \param args compatible value
            inline void pushHead(ParamType args)
            {
                Y_Lock(*cache);
                list.pushHead( cache->summon(args) );
            }



#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            inline ListProto & operator<<(ParamType args) {
                pushTail(args); return *this;
            }

            inline ListProto & operator>>(ParamType args)
            {
                pushHead(args); return *this;
            }

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
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)


            
            inline Type &      head()       noexcept { assert(list.head); return **list.head; } //!< \return head item
            inline Type &      tail()       noexcept { assert(list.tail); return **list.tail; } //!< \return tail item
            inline ConstType & head() const noexcept { assert(list.head); return **list.head; } //!< \return head item
            inline ConstType & tail() const noexcept { assert(list.tail); return **list.tail; } //!< \return tail item


        protected:
            CoreList list; //!< current content

        public:
            CACHE<NODE,THREADING_POLICY> cache; //!< cache

        private:
            Y_Disable_Assign(ListProto); //!< discarded

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            inline virtual const CoreList & locus() const noexcept { return list; }
            inline void free_() noexcept {
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

