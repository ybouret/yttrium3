//! \file

#ifndef Y_Sequence_Included
#define Y_Sequence_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Sequence interface
    //
    //
    //__________________________________________________________________________
    template <typename T, typename WRITABLE>
    class Sequence : public WRITABLE
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Declare(T,Type); //!< aliases

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        inline explicit Sequence() noexcept : WRITABLE() {} //!< setup
        inline virtual ~Sequence() noexcept {}              //!< cleanup

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual void pushTail(ParamType) = 0; //!< push new element at tail
        virtual void pushHead(ParamType) = 0; //!< push new element at head

        virtual void popTail() noexcept = 0; //!< remove element at tail
        virtual void popHead() noexcept = 0; //!< remove element at head


    private:
        Y_Disable_Copy_And_Assign(Sequence); //!< discarded
    };
}


#endif // !Y_Sequence_Included

