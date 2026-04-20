

//! \file

#ifndef Y_Expandable_Included
#define Y_Expandable_Included 1

#include "y/config/setup.hpp"


namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Expandable interface based on Releasable/Collectable
    //
    //
    //__________________________________________________________________________
    template <typename RELEASABLE>
    class Expandable : public RELEASABLE
    {
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        inline explicit Expandable() noexcept  : RELEASABLE {} //!< setup

    public:
        inline virtual ~Expandable() noexcept {} //!< cleanup

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual void reserve(const size_t n) = 0;


        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        inline void ensure(const size_t minCapacity)
        {
            const size_t capa = this->capacity();
            if(capa<minCapacity) reserve(minCapacity-capa)
        }
        

    private:
        Y_Disable_Copy_And_Assign(Expandable); //!< discarding
    };

}

#endif // !Y_Expandable_Included

