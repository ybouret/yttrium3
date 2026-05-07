
//! \file

#ifndef Y_Associative_SuffixSet_Inluded
#define Y_Associative_SuffixSet_Inluded 1

#include "y/container/associative/suffix/proto.hpp"

namespace Yttrium
{

    template <typename KEY, typename T>
    class SuffixSetNode
    {
    public:
        Y_Args_Declare(T,Type);
        Y_Args_Declare(KEY,Key);

        inline SuffixSetNode(ParamType args) :
        data(args),
        next(0),
        prev(0)
        {
        }
        inline ~SuffixSetNode() noexcept {}

        inline Type      & operator*()       noexcept { return data; }
        inline ConstType & operator*() const noexcept { return data; }
        inline ConstKey  & key()       const noexcept { return data.key(); }

    private:
        Type            data;
    public:
        SuffixSetNode * next;
        SuffixSetNode * prev;
    private:
        Y_Disable_Assign(SuffixSetNode);
    };

    template <typename KEY, typename T> 
    class SuffixSet :  public SuffixProto<KEY,T,SuffixSetNode>
    {
    public:
        typedef SuffixSetNode<KEY,T> Node;
        Y_Args_Declare(T, Type);
        Y_Args_Declare(KEY, Key);

        inline explicit SuffixSet() {}
        inline virtual ~SuffixSet() noexcept {}

        inline bool insert(ParamType args)
        {
            // make a living node from args
            Node * const node = this->queryZombie();
            try { new (node) Node(args); }
            catch(...) { this->storeZombie(node); throw; }

            // put living node in the tree
            try
            {
                if(!this->tree.insert(node->key(),node) )
                {
                    this->storeLiving(node); throw;
                    return false;
                }
                else
                {
                    return true;
                }
            }
            catch(...)
            {
                this->storeLiving(node); throw;
            }

        }


    private:
        Y_Disable_Copy_And_Assign(SuffixSet);
    };

}

#endif // !Y_Associative_SuffixSet_Inluded

