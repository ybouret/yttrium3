
//! \file

#ifndef Y_LightArray_Included
#define Y_LightArray_Included 1

#include "y/container/contiguous/writable.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Array based on persistent data
    //
    //
    //__________________________________________________________________________
    template <typename T>
    class LightArray : public ContiguousWritable<T>
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Expose(T,Type); //!< aliases

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup \param entry base address \param count number of items
        inline LightArray(Type * const entry, const size_t count) noexcept :
        Container(),
        ContiguousWritable<T>(),
        cxx( (MutableType *)entry ),
        num( count )
        {
            assert(!(0==cxx&&num>0));
            --Coerce(cxx);
        }

        //! duplicate \param other another light array
        inline LightArray(const LightArray &other) noexcept :
        Container(),
        ContiguousWritable<T>(),
        cxx(other.cxx),
        num(other.num)
        {
        }

        //! cleanup
        inline virtual ~LightArray() noexcept {}

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        inline virtual size_t size()     const noexcept { return num; }
        inline virtual size_t capacity() const noexcept { return num; }


    private:
        inline virtual ConstType & ask(const size_t i) const noexcept { return cxx[i]; }
        Y_Disable_Assign(LightArray); //!< discarded

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        MutableType * const        cxx; //!< cxx[1:num]
        const size_t               num; //!< number of items
    };

}

#endif // !Y_LightArray_Included

