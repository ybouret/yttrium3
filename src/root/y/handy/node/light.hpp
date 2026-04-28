//! \file


#ifndef Y_Handy_LightNode_Included
#define Y_Handy_LightNode_Included 1

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
        class LightNode
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Expose(T,Type); //!< aliases
            typedef T & DataType;  //!< alias
            typedef T & ParamType; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            inline  LightNode(ParamType args) noexcept :
            data(args), next(0), prev(0) {} //!< setup \param args for inner data
            inline ~LightNode() noexcept {} //!< cleanup
            inline LightNode(const LightNode &node) noexcept :
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
            Y_Disable_Assign(LightNode); //!< discarded
            Type &      data; //!< inner data
        public:
            LightNode * next; //!< for list
            LightNode * prev; //!< for list/pool
        };


    }
}

#endif // !Y_Handy_LightNode_Included
