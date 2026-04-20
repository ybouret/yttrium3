
//! \file

#ifndef Y_ReadOnlyContiguous_Included
#define Y_ReadOnlyContiguous_Included 1

#include "y/container/iter/linear.hpp"


namespace Yttrium
{

    template <typename READABLE>
    class ReadOnlyContiguous : public READABLE
    {
    public:
        typedef typename READABLE::ConstType ConstType;
        using READABLE::size;
        using READABLE::ask;

        typedef Iter::Linear<Iter::Forward,ConstType> ConstIterator;
        typedef Iter::Linear<Iter::Reverse,ConstType> ConstReverseIterator;

        inline explicit ReadOnlyContiguous() : READABLE()
        {
        }

        inline virtual ~ReadOnlyContiguous() noexcept
        {
        }

        inline ConstType * operator()(void) const noexcept
        {
            return (size()>0) ? & ask(1) : 0;
        }

        inline ConstIterator begin() const noexcept {
            return (size()>0) ? & ask(1) : 0;
        }

        inline ConstIterator end() const noexcept
        {
            const size_t n = size();
            return n>0 ? (&ask(1))+n : 0;
        }

        inline ConstReverseIterator rbegin() const noexcept {
            const size_t n = size();
            return (n>0) ? (&ask(n)) : 0;
        }

        inline ConstReverseIterator rend() const noexcept
        {
            return (size() > 0) ? ((&ask(1))-1) : 0;
        }

    private:
        Y_Disable_Copy_And_Assign(ReadOnlyContiguous);
    };

}


#endif // !Y_ReadOnlyContiguous_Included
