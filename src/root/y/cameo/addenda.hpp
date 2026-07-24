
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

        template <typename T>
        class Addenda :
        public Proxy< Core::ListOf< Addition<T> > >,
        public Container
        {
        public:
            typedef Addition<T>                AdditionType;
            typedef Core::ListOf<AdditionType> CoreListType;
            typedef Proxy<CoreListType>        ProxyType;

            inline explicit Addenda(const size_t n = 0) :
            ProxyType(), list(), pool()
            {
                grow(n);
            }

            inline explicit Addenda(const size_t n, const size_t minCapacity) :
            ProxyType(), list(), pool()
            {
                grow(n,minCapacity);
            }

            inline virtual ~Addenda() noexcept {}

            inline virtual size_t size()     const noexcept { return list.size; }
            inline virtual size_t capacity() const noexcept { return pool.size; }


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
            Y_Disable_Copy_And_Assign(Addenda);
            CxxListOf<AdditionType> list; //!< live, usable addition(s)
            CxxPoolOf<AdditionType> pool; //!< live, standing by addition(s)

            inline virtual const CoreListType & locus() const noexcept { return list; }

            inline void prefetch(const size_t n) noexcept
            {
                while(list.size<n && pool.size) list.pushTail( pool.query() );
            }

            inline void notAbove(const size_t n) noexcept
            {
                while(list.size>n) pool.store( list.popTail() );
            }


        };

    }

}

#endif // !Y_Cameo_Addenda_Included
