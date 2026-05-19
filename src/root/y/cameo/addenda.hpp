
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

#if 0
        template <typename T>
        class Addenda :
        public Proxy< Core::ListOf< Addition<T> > >
        {
        public:
            typedef Addition<T>                AdditionType;
            typedef Core::ListOf<AdditionType> CoreListType;
            typedef Proxy<CoreListType>        ProxyType;

            inline explicit Addenda(const size_t n) :
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

            inline void grow(const size_t n)
            {
                for(size_t i=0;i<n;++i)
                {
                    pool.store( new AdditionType() );
                }
            }

            inline void grow(const size_t n, const size_t minCapacity)
            {
                for(size_t i=0;i<n;++i)
                {
                    pool.store( new AdditionType(minCapacity) );
                }
            }

        private:
            Y_Disable_Copy_And_Assign(Addenda);
            CxxListOf<AdditionType> list; //!< live, usable addition(s)
            CxxPoolOf<AdditionType> pool; //!< live, standing by addition(s)

            inline virtual const CoreListType & locus() const noexcept { return list; }



        };
#endif

    }

}

#endif // !Y_Cameo_Addenda_Included
