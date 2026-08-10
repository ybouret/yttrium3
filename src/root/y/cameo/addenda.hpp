
//! \file

#ifndef Y_Cameo_Addenda_Included
#define Y_Cameo_Addenda_Included 1


#include "y/cameo/addition.hpp"
#include "y/type/proxy.hpp"
#include "y/core/list/cxx.hpp"
#include "y/core/pool/cxx.hpp"


namespace Yttrium
{
    namespace Cameo
    {

        //______________________________________________________________________
        //
        //
        //
        //! Cache of mutliple Cameo::Addition
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Addenda :
        public CountedObject,
        public Proxy< Core::ListOf< Addition<T> > >,
        public Container,
        public Recyclable
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef Addition<T>                AdditionType; //!< alias
            typedef Core::ListOf<AdditionType> CoreListType; //!< alias
            typedef Proxy<CoreListType>        ProxyType;    //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param n optional cache size
            inline explicit Addenda(const size_t n = 0) :
            CountedObject(), ProxyType(), list(), pool()
            {
                grow(n);
            }

            //! setup \param n optional cache size \param minCapacity optional capacity per addition
            inline explicit Addenda(const size_t n, const size_t minCapacity) :
            ProxyType(), list(), pool()
            {
                grow(n,minCapacity);
            }

            //! cleanup
            inline virtual ~Addenda() noexcept {}

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            inline virtual size_t size()     const noexcept { return list.size; }
            inline virtual size_t capacity() const noexcept { return pool.size; }
            inline virtual void   free()           noexcept { while(list.size) pool.store(list.popTail()); }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            inline void grow(const size_t n) {
                for(size_t i=0;i<n;++i)
                    pool.store( new AdditionType() );
            }

            inline void grow(const size_t n, const size_t minCapacity) {
                for(size_t i=0;i<n;++i)
                    pool.store( new AdditionType(minCapacity) );
            }

            inline AdditionType *make(const size_t n)
            {
                notAbove(n);
                prefetch(n);
                while(list.size<n) list.pushTail( new AdditionType() );
                return list.head;
            }

            inline AdditionType *make(const size_t n, const size_t minCapacity)
            {
                notAbove(n);
                prefetch(n);
                while(list.size<n) list.pushTail( new AdditionType(minCapacity) );
                return list.head;
            }


        private:
            Y_Disable_Copy_And_Assign(Addenda); //!< discard
            CxxListOf<AdditionType> list;       //!< live, usable addition(s)
            CxxPoolOf<AdditionType> pool;       //!< live, standing by addition(s)

            inline virtual const CoreListType & locus() const noexcept { return list; }

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            inline void prefetch(const size_t n) noexcept {
                while(list.size<n && pool.size) list.pushTail( pool.query() );
            }

            inline void notAbove(const size_t n) noexcept {
                while(list.size>n) pool.store( list.popTail() );
            }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        };

    }

}

#endif // !Y_Cameo_Addenda_Included
