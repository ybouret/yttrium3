

//! \file

#ifndef Y_Pointer_Clone_Included
#define Y_Pointer_Clone_Included 1

#include "y/pointer/reject-null.hpp"

namespace Yttrium
{

    //! common info for ArcPtr
    struct ClonePtrInfo
    {
        static const char * const Name; //!< "ClonePtr"
    };


    //__________________________________________________________________________
    //
    //
    //
    //! A Reference Counting PoinTeR
    //
    //
    //__________________________________________________________________________
    template <typename T,
    template <typename> class Redirect = Immediate
    >
    class ClonePtr : public Smart::RejectNullPointer<T,Redirect>
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef Smart::RejectNullPointer<T,Redirect> PointerType; //!< alias
        using PointerType::pointee;

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup \param ptr valid address
        inline ClonePtr(T * const ptr) : PointerType(ClonePtrInfo::Name,ptr)
        {
            assert(0!=pointee);
        }

        //! duplicate by cloning \param other another pointer
        inline ClonePtr(const ClonePtr &other)   :
        PointerType(ClonePtrInfo::Name,other.pointee->clone())
        {

        }


        //! assign by copy/xch \param other another pointer \return *this
        inline ClonePtr & operator=(const ClonePtr &other)
        {
            ClonePtr temp(other);
            this->xch(temp);
            return *this;
        }

        //! cleanup, delete when ref count is zero
        virtual ~ClonePtr() noexcept
        {
            assert(0!=pointee);
            delete pointee;
            pointee = 0;
        }

    };

}

#endif // !Y_Pointer_Clone_Included
