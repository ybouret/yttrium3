
//! \file

#ifndef Y_Associative_Lexicon_Inluded
#define Y_Associative_Lexicon_Inluded 1

#include "y/container/associative.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Associative for type with type.key() method
    //
    //
    //__________________________________________________________________________
    template <typename KEY, typename T>
    class Lexicon : public Associative<KEY,T>
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
        inline explicit Lexicon() noexcept : Associative<KEY,T>() {} //!< setup
        inline virtual ~Lexicon() noexcept {}                        //!< cleanup

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________

        //! try to insert argument with its key() \return true iff success
        virtual bool insert(ParamType) = 0;

    private:
        Y_Disable_Copy_And_Assign(Lexicon); //!< cleanup
    };

}

#endif // !Y_Associative_Lexicon_Inluded

