

//! \file

#ifndef Y_Associative_HashMap_Inluded
#define Y_Associative_HashMap_Inluded 1

#include "y/container/associative/hash/proto.hpp"

namespace Yttrium
{
    template <typename KEY, typename T>
    class HashMapNode
    {
    public:
        Y_Args_Declare(KEY,Key);
        Y_Args_Declare(T,Type);

        inline HashMapNode(const size_t h, ParamKey k, ParamType t) :
        hkey(h), key_(k), data(t), next(0), prev(0)
        {
        }

        inline HashMapNode(const HashMapNode &node) :
        hkey(node.hkey), key_(node.key_), data(node.data), next(0), prev(0) {}

        inline ~HashMapNode() noexcept {}

        inline ConstKey & key() const noexcept { return key_; }

        const size_t hkey;
    private:
        ConstKey     key_;
        Type         data;
        Y_Disable_Assign(HashMapNode);
    public:
        HashMapNode * next;
        HashMapNode * prev;

    };

}

#endif // !Y_Associative_HashMap_Inluded

