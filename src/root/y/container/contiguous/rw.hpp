//! \file

#ifndef Y_ReadWriteContiguous_Included
#define Y_ReadWriteContiguous_Included 1

#include "y/container/iter/linear.hpp"


namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Read Write Contiguous
    //
    //
    //__________________________________________________________________________
    template <typename WRITABLE>
    class ReadWriteContiguous : public  WRITABLE
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef typename WRITABLE::Type      Type;      //!< alias
        typedef typename WRITABLE::ConstType ConstType; //!< alias

        using WRITABLE::size;
        using WRITABLE::ask;

        typedef Iter::Linear<Iter::Forward,Type>      Iterator;             //!< alias
        typedef Iter::Linear<Iter::Reverse,Type>      ReverseIterator;      //!< alias
        typedef Iter::Linear<Iter::Forward,ConstType> ConstIterator;        //!< alias
        typedef Iter::Linear<Iter::Reverse,ConstType> ConstReverseIterator; //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup
        inline explicit ReadWriteContiguous() :  WRITABLE()
        {
        }

        //! cleanup
        inline virtual ~ReadWriteContiguous() noexcept
        {
        }

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! \return legacy access
        inline Type * operator()(void)  noexcept
        {
            return (size()>0) ? (Type *)& ask(1) : 0;
        }

        //! \return legacy const access
        inline ConstType * operator()(void)  const noexcept
        {
            return (size()>0) ? & ask(1) : 0;
        }


#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

        inline Iterator        begin()  noexcept { return (size()>0) ?  (Type *) &ask(1) : 0; }
        inline Iterator        end()    noexcept { const size_t n = size(); return n>0 ? ((Type *)&ask(1))+n : 0; }
        inline ReverseIterator rbegin() noexcept { const size_t n = size(); return (n>0) ? ((Type *)&ask(n)) : 0; }
        inline ReverseIterator rend()   noexcept { return (size() > 0) ? (((Type*)&ask(1))-1) : 0; }

        inline ConstIterator        begin()  const noexcept { return (size()>0) ? & ask(1) : 0; }
        inline ConstIterator        end()    const noexcept { const size_t n = size(); return n>0 ? (&ask(1))+n : 0; }
        inline ConstReverseIterator rbegin() const noexcept { const size_t n = size(); return (n>0) ? (&ask(n)) : 0; }
        inline ConstReverseIterator rend()   const noexcept { return (size() > 0) ? ((&ask(1))-1) : 0; }

#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

    private:
        Y_Disable_Copy_And_Assign(ReadWriteContiguous); //!< discarded
    };

}


#endif // !Y_ReadWriteContiguous_Included
