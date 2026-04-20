//! \file

#ifndef Y_ReadOnlyContiguous_Included
#define Y_ReadOnlyContiguous_Included 1

#include "y/container/iter/linear.hpp"


namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Read Only Contiguous
    //
    //
    //__________________________________________________________________________
    template <typename READABLE>
    class ReadOnlyContiguous : public READABLE
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef typename READABLE::ConstType ConstType; //!< alias
        typedef typename READABLE::Type      Type; //!< alias

        using READABLE::size;
        using READABLE::ask;

        typedef Iter::Linear<Iter::Forward,ConstType> ConstIterator;        //!< alias
        typedef Iter::Linear<Iter::Reverse,ConstType> ConstReverseIterator; //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup
        inline explicit ReadOnlyContiguous() : READABLE()
        {
        }

        //! cleanup
        inline virtual ~ReadOnlyContiguous() noexcept
        {
        }

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! \return legacy access
        inline ConstType * operator()(void) const noexcept
        {
            return (size()>0) ? & ask(1) : 0;
        }

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

        inline ConstIterator        begin()  const noexcept { return (size()>0) ? & ask(1) : 0; }
        inline ConstIterator        end()    const noexcept { const size_t n = size(); return n>0 ? (&ask(1))+n : 0; }
        inline ConstReverseIterator rbegin() const noexcept { const size_t n = size(); return (n>0) ? (&ask(n)) : 0; }
        inline ConstReverseIterator rend()   const noexcept { return (size() > 0) ? ((&ask(1))-1) : 0; }

#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

    private:
        Y_Disable_Copy_And_Assign(ReadOnlyContiguous); //!< discarded
    };

}


#endif // !Y_ReadOnlyContiguous_Included
