
//! \file

#ifndef Y_Associative_SuffixSet_Inluded
#define Y_Associative_SuffixSet_Inluded 1

#include "y/container/associative/suffix/proto.hpp"
#include "y/container/associative/lexicon.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Node for SuffixSet
    //
    //
    //__________________________________________________________________________
    template <typename KEY, typename T>
    class SuffixSetNode
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

        //! setup \param args data
        inline SuffixSetNode(ParamType args) :
        data(args), next(0), prev(0)     {}

        //! cleanup
        inline ~SuffixSetNode() noexcept {}

        //! duplicate \param node another node
        SuffixSetNode(const SuffixSetNode &node) :
        data(node.data), next(0), prev(0) {}

        //! display
        inline friend std::ostream & operator<<(std::ostream &os, const SuffixSetNode &node)
        {
            return os << node.data;
        }

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        inline Type      & operator*()       noexcept { return data; }       //!< \return data
        inline ConstType & operator*() const noexcept { return data; }       //!< \return const data
        inline ConstKey  & key()       const noexcept { return data.key(); } //!< \return const key

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
    private:
        Type            data; //!< data
    public:
        SuffixSetNode * next; //!< for list/pool
        SuffixSetNode * prev; //!< for list
    private:
        Y_Disable_Assign(SuffixSetNode); //!< discarded
    };

    //__________________________________________________________________________
    //
    //
    //
    //! SuffixSet
    //
    //
    //__________________________________________________________________________
    template <typename KEY, typename T>
    class SuffixSet :  public SuffixProto<KEY,T,SuffixSetNode,Lexicon<KEY,T>>
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef SuffixSetNode<KEY,T> Node; //!< alias
        Y_Args_Declare(T, Type);           //!< aliases
        Y_Args_Declare(KEY, Key);          //!< aliases

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        inline explicit SuffixSet()          {} //!< setup
        inline virtual ~SuffixSet() noexcept {} //!< cleanup

        //! duplicate \param other another suffix set
        inline SuffixSet(const SuffixSet &other) :
        SuffixProto<KEY,T,SuffixSetNode,Lexicon<KEY,T>>(other)
        {}

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! try to insert \param args new data \return true iff data was inserted
        inline bool insert(ParamType args)
        {
            // make a living node from args
            Node * const node = this->queryZombie();
            try { new (node) Node(args); }
            catch(...) { this->storeZombie(node); throw; }

            // try to insert it
            return this->insertLiving(node);
        }


    private:
        Y_Disable_Assign(SuffixSet); //!< discarded
    };

}

#endif // !Y_Associative_SuffixSet_Inluded

