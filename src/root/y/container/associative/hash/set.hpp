
//! \file

#ifndef Y_Associative_HashSet_Inluded
#define Y_Associative_HashSet_Inluded 1

#include "y/container/associative/hash/proto.hpp"
#include "y/container/associative/lexicon.hpp"
#include "y/hashing/key/hasher.hpp"
#include "y/hashing/fnv.hpp"


namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Node for HashSet
    //
    //
    //__________________________________________________________________________
    template <typename KEY, typename T>
    class HashSetNode
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

        //! setup \param h hash key \param t type
        inline  HashSetNode(const size_t h, ParamType t) :
        hkey(h), data(t), next(0), prev(0) { }

        //! cleanup
        inline ~HashSetNode() noexcept {}

        //! duplicate \param node another node
        inline  HashSetNode(const HashSetNode &node) :
        hkey(node.hkey), data(node.data), next(0), prev(0) {}

        inline friend std::ostream & operator<<(std::ostream &os, const HashSetNode &self)
        {
            return os << self.data;
        }

        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        inline ConstType & operator*() const noexcept { return data; }       //!< \return content
        inline Type &      operator*()       noexcept { return data; }       //!< \return content
        inline ConstKey &  key()       const noexcept { return data.key(); } //!< \return key

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        const size_t  hkey; //!< hash key
    private:
        Type          data; //!< data with key()
    public:
        HashSetNode * next; //!< for list/pool
        HashSetNode * prev; //!< for list
    private:
        Y_Disable_Assign(HashSetNode); //!< discared
    };


    //__________________________________________________________________________
    //
    //
    //
    //! Hash container for type with type.key() method
    //
    //
    //__________________________________________________________________________
    template <typename KEY,
    typename T,
    typename HASHER = Hashing::KeyWith<Hashing::FNV> >
    class HashSet : public HashProto< HashSetNode<KEY,T>, Lexicon, HASHER>
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
        typedef HashSetNode<KEY,T>                 NodeType;  //!< alias
        typedef HashProto<NodeType,Lexicon,HASHER> ProtoType; //!< alias
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
        inline explicit HashSet(const size_t minTableSize=0) :
        ProtoType(minTableSize)
        {
        }

        //! cleanup
        inline virtual ~HashSet() noexcept
        {
            
        }

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________

        //!< [Lexicon] \param args data to insert \return true iff successful
        inline virtual bool insert(ParamType args)
        {
            const size_t hkey = hash( args.key() );
            NodeType *   node = pool.size ? pool.query() : Object::AcquireZombie<NodeType>();
            try { node = new (node) NodeType(hkey,args); }
            catch(...) { pool.store(node); throw; }
            return insertNode( node );
        }

      


    private:
        Y_Disable_Copy_And_Assign(HashSet); //!< discarded

   
    };


}

#endif // !Y_Associative_HashSet_Inluded

