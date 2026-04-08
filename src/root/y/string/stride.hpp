
//! \file

#ifndef Y_String_Stride_Included
#define Y_String_Stride_Included 1

#include "y/memory/allocator.hpp"
#include "y/string/length.hpp"
#include "y/core/display.hpp"
#include <cstring>
namespace Yttrium
{

    class CoreStride
    {
    public:
        explicit CoreStride() noexcept;
        virtual ~CoreStride() noexcept;

        static Memory::Allocator & AllocatorInstance();
        static Memory::Allocator & AllocatorLocation() noexcept;

    private:
        Y_Disable_Copy_And_Assign(CoreStride);
    };

#define Y_Stride_Acquire()  \
/**/    count(capacity+1),  \
/**/    bytes(0),           \
/**/    entry( AllocatorInstance().acquireAs<T>(Coerce(count),Coerce(bytes)) )

#define Y_Stride_Upgrade() Coerce(capacity) = count-1

    template <typename T>
    class Stride : public CoreStride
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
        }


        inline virtual ~Stride() noexcept
        {
            static Memory::Allocator &mgr = AllocatorLocation();
            mgr.releaseAs(Coerce(entry),Coerce(count),Coerce(bytes));
            Coerce(capacity) = 0;
            Coerce(size)     = 0;
        }

        inline friend std::ostream & operator<<(std::ostream &os, const Stride &self)
        {
            return Core::Display(os,self.entry,self.size) <<  '#' << self.size << '/' << self.capacity;
        }

        const size_t capacity;
        size_t       size;
        const size_t count;
        const size_t bytes;
        T *   const  entry;
    private:
        Y_Disable_Copy_And_Assign(Stride);

    };

}

#endif // !Y_String_Stride_Included

