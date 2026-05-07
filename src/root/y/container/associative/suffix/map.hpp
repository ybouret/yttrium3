

//! \file

#ifndef Y_Associative_SuffixMap_Inluded
#define Y_Associative_SuffixMap_Inluded 1

#include "y/container/associative/suffix/proto.hpp"

namespace Yttrium
{
    template <typename KEY, typename T>
    class SuffixMapNode
    {
    public:
        Y_Args_Declare(T,Type);
        Y_Args_Declare(KEY,Key);

        inline SuffixMapNode(ParamKey k, ParamType args) :
        key_(k),
        data(args),
        next(0),
        prev(0)
        {
        }
        inline ~SuffixMapNode() noexcept {}

        inline Type      & operator*()       noexcept { return data; }
        inline ConstType & operator*() const noexcept { return data; }
        inline ConstKey  & key()       const noexcept { return key_; }

    private:
        ConstKey        key_;
        Type            data;
    public:
        SuffixMapNode * next;
        SuffixMapNode * prev;
    private:
        Y_Disable_Assign(SuffixMapNode);
    };
}

#endif // !Y_Associative_SuffixMap_Inluded

