
//! \file

#ifndef Y_Associative_Lexicon_Inluded
#define Y_Associative_Lexicon_Inluded 1

#include "y/container/associative.hpp"

namespace Yttrium
{

    template <typename KEY, typename T>
    class Lexicon : public Associative<KEY,T>
    {
    public:
        Y_Args_Declare(T,Type);

        inline explicit Lexicon() noexcept : Associative<KEY,T>() {}
        inline virtual ~Lexicon() noexcept {}

        virtual bool insert(ParamType) = 0;

    private:
        Y_Disable_Copy_And_Assign(Lexicon);
    };

}

#endif // !Y_Associative_Lexicon_Inluded

