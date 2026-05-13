
//! \file

#ifndef Y_Container_Ordered_Included
#define Y_Container_Ordered_Included 1


#include "y/container.hpp"
#include "y/type/args.hpp"

namespace Yttrium
{
    template <typename T>
    class Ordered : public Container
    {
    public:
        Y_Args_Declare(T,Type);

        inline explicit Ordered() noexcept : Container()
        {
        }


        inline virtual ~Ordered() noexcept {}

        virtual void        push(ParamType)       = 0;
        virtual void        pop()        noexcept = 0;
        virtual ConstType & peek() const noexcept = 0;

        inline Type pull()
        {
            ConstType saved = peek();
            pop();
            return saved;
        }

    private:
        Y_Disable_Copy_And_Assign(Ordered);
    };
}

#endif // !Y_Container_Ordered_Included

