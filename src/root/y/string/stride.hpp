
//! \file

#ifndef Y_String_Stride_Included
#define Y_String_Stride_Included 1

#include "y/memory/allocator.hpp"
#include "y/string/length.hpp"
#include "y/core/display.hpp"
#include "y/libc/block/zeroed.h"
#include <cstring>

namespace Yttrium
{

    namespace Core
    {
        struct Stride
        {
            static Memory::Allocator & AllocatorInstance();
            static Memory::Allocator & AllocatorLocation() noexcept;
        };
    }

#define Y_Stride_Acquire()  \
/**/    count(capacity+1),  \
/**/    bytes(0),           \
/**/    entry( Core::Stride::AllocatorInstance().acquireAs<T>(Coerce(count),Coerce(bytes)) )

#define Y_Stride_Upgrade() Coerce(capacity) = count-1

    template <typename T>
    class Stride
    {
    public:
        inline explicit Stride(const size_t n) :
        capacity(n),
        size(0),
        Y_Stride_Acquire()
        {
            Y_Stride_Upgrade();
        }

        explicit Stride(const T * const text) :
        capacity( StringLength(text) ),
        size( capacity ),
        Y_Stride_Acquire()
        {
            Y_Stride_Upgrade();
            memcpy(entry,text,size*sizeof(T));
            assert(sanity());
        }

        explicit Stride(const Stride &s) :
        capacity(s.size),
        size(s.size),
        Y_Stride_Acquire()
        {
            Y_Stride_Upgrade();
            memcpy(entry,s.entry,size*sizeof(T));
            assert(sanity());
        }

        inline virtual ~Stride() noexcept
        {
            static Memory::Allocator &mgr = Core::Stride::AllocatorLocation();
            mgr.releaseAs(Coerce(entry),Coerce(count),Coerce(bytes));
            Coerce(capacity) = 0;
            Coerce(size)     = 0;
        }



        inline friend std::ostream & operator<<(std::ostream &os, const Stride &self)
        {
            return Core::Display(os,self.entry,self.size) <<  '#' << self.size << '/' << self.capacity;
        }

        inline bool sanity() const noexcept
        {
            assert(size<=capacity);
            assert(capacity==count-1);
            return Y_TRUE == Yttrium_Zeroed(entry+size,(count-size)*sizeof(T));
        }

        inline Stride & cat(const T * const text, const size_t tlen) noexcept
        {
            assert(sanity());
            assert(tlen == StringLength(text));
            assert(size+tlen<=capacity);
            memcpy(entry+size,text,tlen*sizeof(T));
            Coerce(size) += tlen;
            assert(sanity());
            return *this;
        }

        const size_t capacity;
        const size_t size;
        const size_t count;
        const size_t bytes;
        T *   const  entry;
    private:
        Y_Disable_Assign(Stride);

    };

}

#endif // !Y_String_Stride_Included

