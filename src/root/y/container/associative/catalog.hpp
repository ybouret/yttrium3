

//! \file

#ifndef Y_Associative_Catalog_Inluded
#define Y_Associative_Catalog_Inluded 1

#include "y/container/associative.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Associative for (key,type)
    //
    //
    //__________________________________________________________________________
    template <typename KEY, typename T>
    class Catalog : public Associative<KEY,T>
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
        inline explicit Catalog() noexcept : Associative<KEY,T>() {} //!< setup
        inline virtual ~Catalog() noexcept {}                        //!< cleanup

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________

        //! try to insert a new (key,args) item \return true iff success
        virtual bool insert(ParamKey, ParamType) = 0;

    private:
        Y_Disable_Copy_And_Assign(Catalog); //!< discarded
    };

}

#endif // !Y_Associative_Catalog_Inluded

