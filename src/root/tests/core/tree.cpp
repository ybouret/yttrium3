#include "y/core/tree.hpp"
#include "y/string/length.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

static inline bool FoundIn(Core::Tree &tree, const char * const text)
{
    const size_t       plen = StringLength(text);
    const Core::Tree & cst  = tree;
    {
        const Core::TreeNode * const node = cst.search(text,plen);
        if(!node)       return false;
        if(!node->data) return false;
    }

    {
        const Core::TreeNode * const node = tree.search(text,plen);
        if(!node)       return false;
        if(!node->data) return false;
    }

    return true;
}

Y_UTEST(core_tree)
{

    Y_SIZEOF(Core::TreeNode);

    Core::Tree tree;

    int a[3] = {1,2,3};

    tree.insert("Hello", a+0); Y_CHECK( FoundIn(tree,"Hello") );
    Vizible::Render("tree1.dot",tree);
    tree.insert("World",a+1); Y_CHECK( FoundIn(tree,"World") );
    Vizible::Render("tree2.dot",tree);
    tree.insert("Hell", a+2); Y_CHECK( FoundIn(tree,"Hell") );
    Vizible::Render("tree3.dot",tree);


}
Y_UDONE()

