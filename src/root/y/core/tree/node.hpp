//! \file

#ifndef Y_Core_Tree_Node_Included
#define Y_Core_Tree_Node_Included 1

#include "y/graphviz/vizible.hpp"
#include "y/core/list/cxx.hpp"
#include "y/object.hpp"

namespace Yttrium
{
    namespace Core
    {
        class   TreeNode;
        typedef CxxListOf<TreeNode> TreeList; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! Store Tree inner data
        //
        //
        //______________________________________________________________________
        class TreeNode : public Object, public Vizible
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit TreeNode(const uint8_t, void * const, TreeNode * const) noexcept; //!< setup
            virtual ~TreeNode()                                              noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void           ldz()            noexcept; //!< erase content 
            OutputStream & viz(OutputStream &) const; //!< emit graphviz code \return output stream

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const uint8_t code; //!< code in path
            void * const  data; //!< data (NULL means vacant)
            TreeList      list; //!< child[ren]
            TreeNode *    next; //!< for list/pool
            TreeNode *    prev; //!< for list
            TreeNode *    root; //!< for tree
            
        private:
            Y_Disable_Copy_And_Assign(TreeNode); //!< discarded
        };

    }
}

#endif // !Y_Core_Tree_Node_Included

