

//! \file

#ifndef Y_Writable_Container_Included
#define Y_Writable_Container_Included 1

#include "y/container/readable.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Writable container is a Readable container
    //
    //
    //__________________________________________________________________________
    template <typename T>
    class Writable : public Readable<T>
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef typename Readable<T>::Type      Type; //!< alias
        typedef typename Readable<T>::ConstType ConstType; //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        inline explicit Writable() noexcept {} //!< setup
        inline virtual ~Writable() noexcept {} //!< cleanup

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! access \param indx in [1:size()] \return indx-th item
        inline Type & operator[](const size_t indx) noexcept
        {
            assert(indx>=1); assert(indx<=this->size());
            return (Type&)(this->ask(indx));
        }

        //! const access \param indx in [1:size()] \return indx-th item
        inline ConstType & operator[](const size_t indx) const noexcept
        {
            assert(indx>=1); assert(indx<=this->size());
            return  this->ask(indx);
        }

    private:
        Y_Disable_Copy_And_Assign(Writable); //!< discarded
    };

}

#endif // !Y_Writable_Container_Included

