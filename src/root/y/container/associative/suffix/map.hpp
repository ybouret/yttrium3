

//! \file

#ifndef Y_Associative_SuffixMap_Inluded
#define Y_Associative_SuffixMap_Inluded 1

#include "y/container/associative/suffix/proto.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Node for SuffixMap
    //
    //
    //__________________________________________________________________________
    template <typename KEY, typename T>
    class SuffixMapNode
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Declare(T,Type);  //!< aliases
        Y_Args_Declare(KEY,Key); //!< aliases

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup \param k key \param args value
        inline SuffixMapNode(ParamKey k, ParamType args) :
        key_(k),
        data(args),
        next(0),
        prev(0)
        {
        }

        //! cleanup
        inline ~SuffixMapNode() noexcept {}

        //! duplicate \param node another node
        SuffixMapNode(const SuffixMapNode &node) :
        key_(node.key_),
        data(node.data),
        next(0),
        prev(0)
        {
        }

        //! display
        inline friend std::ostream & operator<<(std::ostream &os, const SuffixMapNode &node)
        {
            return os << node.key_ << ":" << node.data;
        }

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        inline Type      & operator*()       noexcept { return data; } //!< \return data
        inline ConstType & operator*() const noexcept { return data; } //!< \return const data
        inline ConstKey  & key()       const noexcept { return key_; } //!< \return key_

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
    private:
        ConstKey        key_; //!< key
        Type            data; //!< data
    public:
        SuffixMapNode * next; //!< for list/pool
        SuffixMapNode * prev; //!< for list
    private:
        Y_Disable_Assign(SuffixMapNode); //!< discarded
    };

    //__________________________________________________________________________
    //
    //
    //
    //! SuffixMap of key:value
    //
    //
    //__________________________________________________________________________
    template <typename KEY, typename T>
    class SuffixMap :  public SuffixProto<KEY, T, SuffixMapNode>
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef SuffixMapNode<KEY, T> Node; //!< alias
        Y_Args_Declare(T, Type);            //!< aliases
        Y_Args_Declare(KEY, Key);           //!< aliases

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        inline explicit SuffixMap()          {} //!< setup empty
        inline virtual ~SuffixMap() noexcept {} //!< cleanup

        //! duplicate \param other another suffix map
        inline SuffixMap(const SuffixMap &other) :
        SuffixProto<KEY,T,SuffixMapNode>(other)
        {}
        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! try to insert new pair
        /**
         \param key key
         \param args data
         \return true if key was not present
         */
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
        Y_Disable_Assign(SuffixMap); //!< discarded
    };

}

#endif // !Y_Associative_SuffixMap_Inluded

