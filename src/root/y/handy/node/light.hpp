
#ifndef Y_Handy_LightNode_Included
#define Y_Handy_LightNode_Included 1

#include "y/type/args.hpp"

namespace Yttrium
{
    namespace Handy
    {

        template <typename T>
        class LightNode
        {
        public:
            Y_Args_Expose(T,Type);
            typedef T & ParamType;

            inline  LightNode(ParamType args) noexcept :
            data(args), next(0), prev(0) {}
            inline ~LightNode() noexcept {}

            inline Type      & operator*()       noexcept { return data; }
            inline ConstType & operator*() const noexcept { return data; }

        private:
            Y_Disable_Copy_And_Assign(LightNode);
            Type &      data;
        public:
            LightNode * next;
            LightNode * prev;
        };


    }
}

#endif // !Y_Handy_LightNode_Included
