#include "y/core/meta-max.hpp"
#include "y/calculus/alignment.hpp"

#include "y/utest/run.hpp"

#include "y/libc/block/zero.h"
#include "y/format/hexadecimal.hpp"

namespace Yttrium
{

    namespace Concurrent
    {

        class VaList
        {
        public:
            static const unsigned MaxArgs = 2;
            typedef void (VaList::*Meth)(void);
            typedef void (*Func)(void);
            static const size_t BytesForArgs = MaxArgs * sizeof(void*);
            static const size_t BytesForFunc = BytesForArgs + sizeof(Func);
            static const size_t BytesForMeth = BytesForArgs + sizeof(void *) + sizeof(Meth);
            static const size_t RequiredBytes = MetaMax<BytesForFunc,BytesForMeth>::Value;
            static const size_t RequiredWords = Alignment::WordsGEQ<RequiredBytes>::Count;

            VaList() noexcept :
            wptr(0),
            rptr(0),
            data(0),
            wksp()
            {
                Coerce(data) = static_cast<uint8_t *>( Y_BZero(wksp) );
                wptr         = data;
                rptr         = data;
            }


            ~VaList() noexcept
            {
            }

            Y_OSTREAM_PROTO(VaList);


            size_t usedBytes() const noexcept
            {
                return static_cast<size_t>(wptr-data);
            }

            size_t freeBytes() const noexcept
            {
                assert(wptr>=data);
                assert(wptr<=data+RequiredBytes);
                return static_cast<size_t>( (data+RequiredBytes)-wptr );
            }

            size_t codeBytes() const noexcept
            {
                assert(wptr>=data);
                assert(wptr<=data+RequiredBytes);
                assert(rptr>=data);
                assert(rptr<=wptr);
                return static_cast<size_t>(wptr-rptr);
            }


            //! pack an argument address
            template <typename T> inline
            VaList & operator<<(T &args)
            {
                return record(&args);
            }


            //! pack a C-style function address
            template <typename CFUNCTION>
            VaList & operator()(CFUNCTION cfunction)
            {
                assert(0!=cfunction);
                union {
                    CFUNCTION func;
                    void *    addr;
                } alias =  { cfunction };
                assert(0!=alias.addr);
                return record(alias.addr);
            }

            template <typename T> inline
            T & as() noexcept
            {
                return *static_cast<T*>( unpack() );
            }

            template <typename CFUNCTION> inline
            CFUNCTION func()
            {
                return (CFUNCTION) unpack();
            }




        private:
            Y_Disable_Copy_And_Assign(VaList);
            uint8_t *          wptr;
            uint8_t *          rptr;
            uint8_t * const    data;
            void *             wksp[RequiredWords];

            void *  unpack() noexcept
            {
                assert(codeBytes()>=sizeof(void*));
                void * const addr = *(void **)rptr;
                rptr += sizeof(void*);
                return addr;
            }

            VaList & record(const void * const addr) noexcept
            {
                assert( freeBytes() >= sizeof(void *) );
                *(void **)wptr = (void *) addr;
                wptr += sizeof(void *);
                return *this;
            }
        };

        std::ostream & operator<<(std::ostream &os, const VaList &vp)
        {
            return Hexadecimal::Display(os,vp.data,vp.usedBytes());
        }


    }

}

using namespace Yttrium;

namespace
{
    typedef void (*CProto)(void);

    static inline void doNothing(void)
    {
        std::cerr << "I do nothing.." << std::endl;
    }
}

Y_UTEST(concurrent_args)
{

    Y_SIZEOF(Concurrent::VaList::Func);
    Y_SIZEOF(Concurrent::VaList::Meth);
    Y_PRINTV(Concurrent::VaList::BytesForFunc);
    Y_PRINTV(Concurrent::VaList::BytesForMeth);
    Y_PRINTV(Concurrent::VaList::RequiredBytes);
    Y_PRINTV(Concurrent::VaList::RequiredWords);
    Y_SIZEOF(Concurrent::VaList);


    Concurrent::VaList vp; Y_CHECK(vp.freeBytes() >= Concurrent::VaList::RequiredBytes );
    Y_PRINTV(vp);

    int a = 8;
    Y_PRINTV( (void*) &a );
    Y_PRINTV(vp<<a);
    Y_PRINTV(vp(doNothing));

    a=7;
    Y_PRINTV( vp.as<const int>() );

    CProto f = vp.func<CProto>();
    f();




}
Y_UDONE()
