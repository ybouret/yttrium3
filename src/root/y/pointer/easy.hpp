

//! \file

#ifndef Y_Pointer_Easy_Included
#define Y_Pointer_Easy_Included 1

#include "y/pointer/immediate.hpp"
#include "y/pointer/accept-null.hpp"
#include <iostream>

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! EasyPtr, reference counting and possibly Null
    //
    //
    //__________________________________________________________________________
    template <
    typename T,
    template <typename> class Redirect = Immediate
    >
    class EasyPtr : public Smart::AcceptNullPointer<T,Redirect>
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef Smart::AcceptNullPointer<T,Redirect> PointerType; //!< alias
        using PointerType::pointee;

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup \param ptr any address
        inline EasyPtr(T * const ptr) noexcept : PointerType(ptr)
        {
            if(pointee) pointee->withhold();
        }

        //! setup empty
        inline EasyPtr() noexcept : PointerType(0)
        {

        }

        //! cleanup
        inline virtual ~EasyPtr() noexcept
        {
            if(pointee&&pointee->liberate()) delete pointee;
            pointee=0;
        }

        //! keep only one copy \param other another pointer
        inline EasyPtr(const EasyPtr &other) noexcept :
        PointerType(other.pointee)
        {
            if(pointee) pointee->withhold();
        }

        //! keep only one copy \param other another pointer \return *this
        inline EasyPtr & operator=(const EasyPtr &other) noexcept
        {
            EasyPtr temp(other);
            this->xch(temp);
            return *this;
        }

        
        inline friend std::ostream & operator<<(std::ostream &os, const EasyPtr &self)
        {
            if(self.pointee) os << *self.pointee; else os << Core::NullPtr;
            return os;
        }

    };

}


#endif // !Y_Pointer_Easy_Included
