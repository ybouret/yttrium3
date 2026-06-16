
//! \file

#ifndef Y_LightArray_Included
#define Y_LightArray_Included 1

#include "y/container/contiguous/writable.hpp"

namespace Yttrium
{

    template <typename T>
    class LightArray : public ContiguousWritable<T>
    {
    public:
        Y_Args_Expose(T,Type);

        inline LightArray(Type * const entry, const size_t count) noexcept :
        ContiguousWritable<T>(),
        cxx( (MutableType *)entry ),
        num( count )
        {
            assert(!(0==cxx&&num>0));
            --Coerce(cxx);
        }

        inline LightArray(const LightArray &other) noexcept :
        ContiguousWritable<T>(),
        cxx(other.cxx),
        num(other.num)
        {
        }
        
        inline virtual ~LightArray() noexcept {}


        inline virtual size_t size()     const noexcept { return num; }
        inline virtual size_t capacity() const noexcept { return num; }


    private:
        Y_Disable_Assign(LightArray);
        MutableType * const cxx;
        const size_t        num;

        inline virtual ConstType & ask(const size_t i) const noexcept { return cxx[i]; }
    };

}

#endif // !Y_LightArray_Included

