

//! \file

#ifndef Y_Associative_HashMap_Inluded
#define Y_Associative_HashMap_Inluded 1

#include "y/container/associative/hash/proto.hpp"
#include "y/container/associative/catalog.hpp"
#include "y/hashing/key/hasher.hpp"
#include "y/hashing/fnv.hpp"

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
        inline ConstType & operator*() const noexcept { return data; }
        inline Type      & operator*()       noexcept { return data; }
        inline ConstKey  & key()       const noexcept { return key_; }

        const size_t hkey;
    private:
        ConstKey     key_;
        Type         data;
        Y_Disable_Assign(HashMapNode);
    public:
        HashMapNode * next;
        HashMapNode * prev;

    };

    template <typename KEY,
    typename T,
    typename HASHER = Hashing::KeyWith<Hashing::FNV> >
    class HashMap : public HashProto< HashMapNode<KEY,T>, Associative >
    {
    public:
        Y_Args_Declare(KEY,Key);
        Y_Args_Declare(T,Type);
        typedef HashMapNode<KEY,T>              NodeType;
        typedef HashProto<NodeType,Associative> ProtoType;
        using ProtoType::list;
        using ProtoType::pool;
        using ProtoType::htab;
        using ProtoType::insertNode;

        inline explicit HashMap(const size_t minTableSize=0) :
        ProtoType(minTableSize)
        {
        }

        inline virtual bool insert(ParamKey key, ParamType args)
        {
            const size_t hkey = hash( key);
            NodeType *   node = pool.size ? pool.query() : Object::AcquireZombie<NodeType>();
            try { node = new (node) NodeType(hkey,key,args); }
            catch(...) { pool.store(node); throw; }
            return insertNode( node );
        }

        inline virtual ~HashMap() noexcept
        {

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
        Y_Disable_Assign(HashMap);

    public:
        mutable HASHER hash;
    };

}

#endif // !Y_Associative_HashMap_Inluded

