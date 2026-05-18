
//! \file

#ifndef Y_Associative_HashSet_Inluded
#define Y_Associative_HashSet_Inluded 1

#include "y/container/associative/hash/proto.hpp"
#include "y/hashing/key/hasher.hpp"
#include "y/hashing/fnv.hpp"


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


        inline ConstType & operator*() const noexcept { return data; }
        inline Type &      operator*()       noexcept { return data; }

        //! display
        inline friend std::ostream & operator<<(std::ostream &os, const HashSetNode &node)
        {
            return os << node.data;
        }

        inline ConstKey & key() const noexcept { return data.key(); }

        const size_t hkey;
    private:
        Type         data;
        Y_Disable_Assign(HashSetNode);
    public:
        HashSetNode * next;
        HashSetNode * prev;
    };



    template <typename KEY,
    typename T,
    typename HASHER = Hashing::KeyWith<Hashing::FNV> >
    class HashSet : public HashProto< HashSetNode<KEY,T>, Associative>
    {
    public:
        Y_Args_Declare(KEY,Key);
        Y_Args_Declare(T,Type);
        typedef HashSetNode<KEY,T>              NodeType;
        typedef HashProto<NodeType,Associative> ProtoType;
        using ProtoType::list;
        using ProtoType::pool;
        using ProtoType::insertNode;
        using ProtoType::htab;

        inline explicit HashSet(const size_t minTableSize=0) :
        ProtoType(minTableSize)
        {
        }

        inline virtual ~HashSet() noexcept
        {
            
        }

        inline virtual bool insert(ParamType args)
        {
            const size_t hkey = hash( args.key() );
            NodeType *   node = pool.size ? pool.query() : Object::AcquireZombie<NodeType>();
            try { node = new (node) NodeType(hkey,args); }
            catch(...) { pool.store(node); throw; }
            return insertNode( node );
        }

        inline virtual Type * search(ParamKey key)
        {
            NodeType * const node = htab->search( hash(key), key);
            return node ? & **node : 0;
        }

        inline virtual ConstType * search(ParamKey key) const
        {
            const NodeType * const node = htab->search( hash(key), key);
            return node ? & **node : 0;
        }

        inline virtual bool remove(ParamKey key)
        {
            return htab->remove( hash(key), key, list, pool);
        }



    private:
        Y_Disable_Assign(HashSet);

    public:
        mutable HASHER hash;
    };


}

#endif // !Y_Associative_HashSet_Inluded

