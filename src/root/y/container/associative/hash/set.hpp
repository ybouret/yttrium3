
//! \file

#ifndef Y_Associative_HashSet_Inluded
#define Y_Associative_HashSet_Inluded 1

#include "y/container/associative/hash/proto.hpp"

namespace Yttrium
{

    template <typename KEY, typename T>
    class HashSetNode
    {
    public:
        Y_Args_Declare(KEY,Key);
        Y_Args_Declare(T,Type);

        inline  HashSetNode(const size_t h, ParamType t) :
        hkey(h), data(t), next(0), prev(0) { }
        inline ~HashSetNode() noexcept {}
        inline  HashSetNode(const HashSetNode &node) :
        hkey(node.hkey), data(node.data), next(0), prev(0) {}

        inline ConstKey & key() const noexcept { return data.key(); }

        const size_t hkey;
    private:
        Type         data;
        Y_Disable_Assign(HashSetNode);
    public:
        HashSetNode * next;
        HashSetNode * prev;
    };

}

#endif // !Y_Associative_HashSet_Inluded

