
//! \file

#ifndef Y_ContiguousWritable_Included
#define Y_ContiguousWritable_Included 1

#include "y/container/contiguous/rw.hpp"
#include "y/container/writable.hpp"


namespace Yttrium
{
    template <typename T>
    class ContiguousWritable  : public ReadWriteContiguous< Writable<T> >
    {
    public:
        inline explicit ContiguousWritable() noexcept : ReadWriteContiguous< Writable<T> >() {}
        inline virtual ~ContiguousWritable() noexcept {}

    private:
        Y_Disable_Copy_And_Assign(ContiguousWritable);
    };
}

#endif // !Y_ContiguousWritable_Included
