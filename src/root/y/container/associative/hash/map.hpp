

//! \file

#ifndef Y_Associative_HashMap_Inluded
#define Y_Associative_HashMap_Inluded 1

#include "y/container/associative/hash/proto.hpp"
#include "y/container/associative/catalog.hpp"
#include "y/hashing/key/hasher.hpp"
#include "y/hashing/fnv.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Node for HashMap
    //
    //
    //__________________________________________________________________________
    template <typename KEY, typename T>
    class HashMapNode
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Declare(KEY,Key); //!< aliases
        Y_Args_Declare(T,Type);  //!< aliases

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup \param h hashed key \param k key \param t type
        inline HashMapNode(const size_t h, ParamKey k, ParamType t) :
        hkey(h), key_(k), data(t), next(0), prev(0)
        {
        }

        //! duplicate \param node another node
        inline HashMapNode(const HashMapNode &node) :
        hkey(node.hkey), key_(node.key_), data(node.data), next(0), prev(0) {}

        //! cleanup
        inline ~HashMapNode() noexcept {}

        //! display key:data
        inline friend std::ostream & operator<<(std::ostream &os, const HashMapNode &self)
        {
            return os << self.key_ << ':' << self.data;
        }
        
        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        inline ConstType & operator*() const noexcept { return data; } //!< \return const content
        inline Type      & operator*()       noexcept { return data; } //!< \return content
        inline ConstKey  & key()       const noexcept { return key_; } //!< \return key

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        const size_t hkey; //!< hashed key
    private:
        ConstKey     key_; //!< key
        Type         data; //!< data
        Y_Disable_Assign(HashMapNode); //!< discarded
    public:
        HashMapNode * next; //!< for list/pool
        HashMapNode * prev; //!< for list

    };

    //__________________________________________________________________________
    //
    //
    //
    //! Hash map of (key,value)
    //
    //
    //__________________________________________________________________________
    template <typename KEY,
    typename T,
    typename HASHER = Hashing::KeyWith<Hashing::FNV> >
    class HashMap : public HashProto< HashMapNode<KEY,T>, Catalog, HASHER>
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Declare(KEY,Key);                              //!< aliases
        Y_Args_Declare(T,Type);                               //!< aliases
        typedef HashMapNode<KEY,T>                 NodeType;  //!< alias
        typedef HashProto<NodeType,Catalog,HASHER> ProtoType; //!< alias
        using ProtoType::list;
        using ProtoType::pool;
        using ProtoType::htab;
        using ProtoType::hash;
        using ProtoType::insertNode;

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup \param minTableSize minimal slots in table
        inline explicit HashMap(const size_t minTableSize=0) :
        ProtoType(minTableSize)
        {
        }

        inline HashMap(const HashMap &other ) :
        ProtoType(other)
        {
        }

        //! cleanup
        inline virtual ~HashMap() noexcept {}



        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________

        //! [Catalog] \param key key \param args data \return true iff (key,data) was inserted
        inline virtual bool insert(ParamKey key, ParamType args)
        {
            const size_t hkey = hash(key);
            NodeType *   node = pool.size ? pool.query() : Object::AcquireZombie<NodeType>();
            try { node = new (node) NodeType(hkey,key,args); }
            catch(...) { pool.store(node); throw; }
            return insertNode( node );
        }

    private:
        Y_Disable_Assign(HashMap); //!< discarded

    };

}

#endif // !Y_Associative_HashMap_Inluded

