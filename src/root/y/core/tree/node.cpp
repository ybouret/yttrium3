#include "y/core/tree/node.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Core
    {

        TreeNode:: TreeNode(const uint8_t    c,
                            void * const     d,
                            TreeNode * const n) noexcept :
        Object(),
        code(c),
        data(d),
        list(),
        next(0),
        prev(0),
        root(n)
        {
        }

        TreeNode:: ~TreeNode() noexcept
        {
            (void) erased();
        }


        TreeNode * TreeNode:: erased() noexcept
        {
            Coerce(code) = 0;
            Coerce(data) = 0;
            Coerce(root) = 0;
            return this;
        }

        OutputStream & TreeNode:: viz(OutputStream &fp) const
        {
            // emit list
            for(const TreeNode * node=list.head;node;node=node->next)
                node->viz(fp);

            // emit this
            nodeName(fp) << '[';
            Label(fp, (char)code ) << ",shape=";
            if(data) fp << "square,style=bold"; else fp << "circle";
            Endl(fp << ']');

            // link to list
            unsigned i=1;
            for(const TreeNode * node=list.head;node;node=node->next,++i)
            {
                assert(node->root==this);
                to(node,fp);
                if(list.size>1)
                    fp("[label=\"%u\"]",i);
                Endl(fp);
            }

            return fp;
        }

    }

}


