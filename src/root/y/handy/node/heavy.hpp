//! \file

#ifndef Y_Handy_HeavyNode_Included
#define Y_Handy_HeavyNode_Included 1

#include "y/type/args.hpp"

namespace Yttrium
{
    namespace Handy
    {

        //______________________________________________________________________
        //
        //
        //
        //! Light Node
        //
        //
        //______________________________________________________________________
        template <typename T>
        class HeavyNode
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Declare(T,Type); //!< aliases

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            inline  HeavyNode(ParamType args) noexcept :
            data(args), next(0), prev(0) {} //!< setup \param args for inner data
            inline ~HeavyNode() noexcept {} //!< cleanup
            inline HeavyNode(const HeavyNode &node) :
            data(node.data), next(0), prev(0) {} //!< duplicate \param node another node

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            inline Type      & operator*()       noexcept { return data; } //!< \return inner data
            inline ConstType & operator*() const noexcept { return data; } //!< \return inner data

        private:
            Y_Disable_Assign(HeavyNode); //!< discarded
            Type &      data; //!< inner data
        public:
            HeavyNode * next; //!< for list
            HeavyNode * prev; //!< for list/pool
        };


    }
}

#endif // !Y_Handy_HeavyNode_Included
