

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
        Y_Args_Declare(T,Type);

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

        inline Writable & ld(ParamType value)
        {
            for(size_t i=this->size();i>0;--i) (*this)[i] = value;
            return *this;
        }
        
        //! load content \param a a compatible source \return
        template <typename ARRAY> inline
        Writable & load(ARRAY &a)
        {
            assert(this->size()==a.size());
            for(size_t i=this->size();i>0;--i) (*this)[i] = a[i];
            return *this;
        }



    private:
        Y_Disable_Copy_And_Assign(Writable); //!< discarded
    };

}

#endif // !Y_Writable_Container_Included

