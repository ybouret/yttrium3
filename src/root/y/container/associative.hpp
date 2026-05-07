//! \file

#ifndef Y_Associative_Container_Inluded
#define Y_Associative_Container_Inluded 1

#include "y/container.hpp"
#include "y/type/args.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Associative container minimal interface
    //
    //
    //__________________________________________________________________________
    template <typename KEY, typename T>
    class Associative : public Container
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Declare(T,Type);  //!< aliases
        Y_Args_Declare(KEY,Key); //!< aliases

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        inline explicit Associative() noexcept : Container() {} //!< setup
        inline virtual ~Associative() noexcept {}               //!< cleanup

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual Type *      search(ParamKey)       = 0; //!< \return address of matching key, 0 if not found
        virtual ConstType * search(ParamKey) const = 0; //!< \return address of matching key, 0 if not found


    private:
        Y_Disable_Copy_And_Assign(Associative); //!< discarded
    };

}

#endif // !Y_Associative_Container_Inluded

