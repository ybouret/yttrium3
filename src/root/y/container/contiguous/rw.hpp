

//! \file

#ifndef Y_ReadWriteContiguous_Included
#define Y_ReadWriteContiguous_Included 1

#include "y/container/iter/linear.hpp"



namespace Yttrium
{

    template <typename WRITABLE>
    class ReadWriteContiguous : public  WRITABLE
    {
    public:
        typedef typename WRITABLE::Type      Type;
        typedef typename WRITABLE::ConstType ConstType;

        using WRITABLE::size;
        using WRITABLE::ask;

        typedef Iter::Linear<Iter::Forward,Type>      Iterator;
        typedef Iter::Linear<Iter::Reverse,Type>      ReverseIterator;
        typedef Iter::Linear<Iter::Forward,ConstType> ConstIterator;
        typedef Iter::Linear<Iter::Reverse,ConstType> ConstReverseIterator;


        inline explicit ReadWriteContiguous() :  WRITABLE()
        {
        }

        inline virtual ~ReadWriteContiguous() noexcept
        {
        }

        inline Type * operator()(void)  noexcept
        {
            return (size()>0) ? (Type *)& ask(1) : 0;
        }

        inline ConstType * operator()(void)  const noexcept
        {
            return (size()>0) ? & ask(1) : 0;
        }

        //
        
        inline Iterator begin() noexcept {
            return (size()>0) ?  (Type *) &ask(1) : 0;
        }

        inline  Iterator end() noexcept
        {
            const size_t n = size();
            return n>0 ? ((Type *)&ask(1))+n : 0;
        }

        inline ReverseIterator rbegin() noexcept {
            const size_t n = size();
            return (n>0) ? ((Type *)&ask(n)) : 0;
        }

        inline ReverseIterator rend() noexcept
        {
            return (size() > 0) ? (((Type*)&ask(1))-1) : 0;
        }

        //
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
        Y_Disable_Copy_And_Assign(ReadWriteContiguous);
    };

}


#endif // !Y_ReadWriteContiguous_Included
