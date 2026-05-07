

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

        SuffixMapNode(const SuffixMapNode &node) :
        key_(node.key_),
        data(node.data),
        next(0),
        prev(0)
        {
        }

        inline friend std::ostream & operator<<(std::ostream &os, const SuffixMapNode &node)
        {
            return os << node.key_ << ":" << node.data;
        }

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

    template <typename KEY, typename T>
    class SuffixMap :  public SuffixProto<KEY, T, SuffixMapNode>
    {
    public:
        typedef SuffixMapNode<KEY, T> Node;
        Y_Args_Declare(T, Type);
        Y_Args_Declare(KEY, Key);

        inline explicit SuffixMap() {}
        inline virtual ~SuffixMap() noexcept {}

        inline bool insert(ParamKey key, ParamType args)
        {
            // make a living node from args
            Node * const node = this->queryZombie();
            try { new (node) Node(key,args); }
            catch(...) { this->storeZombie(node); throw; }

            // try to insert it
            return this->insertLiving(node);
        }

    private:
        Y_Disable_Copy_And_Assign(SuffixMap);
    };

}

#endif // !Y_Associative_SuffixMap_Inluded

