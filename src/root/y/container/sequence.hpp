//! \file

#ifndef Y_Sequence_Included
#define Y_Sequence_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    template <typename T, typename WRITABLE>
    class Sequence : public WRITABLE
    {
    public:
        Y_Args_Declare(T,Type);
        
        inline explicit Sequence() noexcept : WRITABLE() {}
        inline virtual ~Sequence() noexcept {}

        virtual void pushTail(ParamType) = 0;
        virtual void pushHead(ParamType) = 0;

        virtual void popTail() noexcept = 0;
        virtual void popHead() noexcept = 0;


    private:
        Y_Disable_Copy_And_Assign(Sequence);
    };
}


#endif // !Y_Sequence_Included

