
//! \file

#ifndef Y_String_Stride_Included
#define Y_String_Stride_Included 1

#include "y/object.hpp"
#include "y/memory/allocator.hpp"

namespace Yttrium
{

    class CoreStride : public Object
    {
    public:
        explicit CoreStride() noexcept;
        virtual ~CoreStride() noexcept;

        static Memory::Allocator & AllocatorInstance();
        static Memory::Allocator & AllocatorLocation() noexcept;

    private:
        Y_Disable_Copy_And_Assign(CoreStride);
    };

    template <typename T>
    class Stride : public CoreStride
    {
    public:
        explicit Stride(const size_t n) :
        capacity(n),
        size(0),
        count(capacity+1),
        bytes(0),
        entry( AllocatorInstance().acquireAs<T>(count,bytes) )
        {
        }



        inline virtual ~Stride() noexcept
        {
            static Memory::Allocator &mgr = AllocatorLocation();
            mgr.releaseAs(entry, Coerce(count), Coerce(bytes));
            Coerce(capacity) = 0;
            Coerce(size)     = 0;
        }

        const size_t capacity;
        size_t       size;

    private:
        Y_Disable_Copy_And_Assign(Stride);
        const size_t count;
        const size_t bytes;
        T * const    entry;
    };

}

#endif // !Y_String_Stride_Included

