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
        typedef CxxListOf<TreeNode> TreeList;
        //typedef CxxPoolOf<TreeNode> TreePool;

        class TreeNode : public Object, public Vizible
        {
        public:
            explicit TreeNode(const uint8_t, void * const) noexcept;
            virtual ~TreeNode() noexcept;

            TreeNode * erased() noexcept;

            OutputStream & viz(OutputStream &) const;

            const uint8_t code;
            void * const  data;
            TreeList      list;
            TreeNode *    next;
            TreeNode *    prev;

        private:
            Y_Disable_Copy_And_Assign(TreeNode);
        };

    }
}

#endif // !Y_Core_Tree_Node_Included

