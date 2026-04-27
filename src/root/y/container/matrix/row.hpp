//! \file

#ifndef Y_MatrixRow_Included
#define Y_MatrixRow_Included 1

#include "y/container/contiguous/writable.hpp"
#include "y/type/destruct.hpp"

namespace Yttrium
{

    template <typename T>
    class MatrixRow : public ContiguousWritable<T>
    {
    public:
        Y_Args_Expose(T,Type);

        inline explicit MatrixRow(MutableType * const entry,
                                  const size_t        count) noexcept :
        cols(count),
        cxx(entry-1)
        {
            assert(count>0); assert(0!=entry);
        }

        inline virtual ~MatrixRow() noexcept
        {
            for(size_t i=cols;i>0;--i) Destruct(cxx+i);
            Coerce(cols) = 0;
            Coerce(cxx)  = 0;
        }

        inline virtual size_t size()     const noexcept { return cols; }
        inline virtual size_t capacity() const noexcept { return cols; }


        inline std::ostream & print(std::ostream &os) const
        {
            assert(cols>0);
            assert(0!=cxx);
            os << cxx[1];
            for(size_t i=2;i<=cols;++i)
            {
                os << ' ' << cxx[i];
            }
            return os;
        }


        const size_t cols;
    private:
        Y_Disable_Copy_And_Assign(MatrixRow);
        MutableType * const cxx;

        inline virtual ConstType & ask(const size_t c) const noexcept
        {
            assert(c>=1); assert(c<=cols);
            return cxx[c];
        }
    };

}

#endif // !Y_MatrixRow_Included


