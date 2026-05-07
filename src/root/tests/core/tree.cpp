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

    int a[4] = {1,2,3,4};

    tree.insert("Hello", a+0);  Y_CHECK( FoundIn(tree,"Hello")  );
    Vizible::Render("tree1.dot",tree);
    tree.insert("World",a+1);   Y_CHECK( FoundIn(tree,"World")  );
    Vizible::Render("tree2.dot",tree);
    tree.insert("Hell", a+2);   Y_CHECK( FoundIn(tree,"Hell")   );
    Vizible::Render("tree3.dot",tree);
    tree.insert("Helico", a+3); Y_CHECK( FoundIn(tree,"Helico") );
    Vizible::Render("tree4.dot",tree);

    {
        Y_CHECK( 0 != tree.search("Wor") );
        Y_CHECK( 0 == tree.search("Wor")->data );
    }

    Y_CHECK(a+2==tree.remove("Hell"));
    Vizible::Render("tree5.dot",tree);
    Y_CHECK(a+0==tree.remove("Hello"));
    Vizible::Render("tree6.dot",tree);
    Y_CHECK(a+1==tree.remove("World"));
    Vizible::Render("tree7.dot",tree);

    Y_PRINTV(tree.size);
    Y_PRINTV(tree.pool.size);

    tree.free();
    Y_PRINTV(tree.size);
    Y_PRINTV(tree.pool.size);

    tree.insert("Hello", a+0);  Y_CHECK( FoundIn(tree,"Hello")  );
    tree.insert("World",a+1);   Y_CHECK( FoundIn(tree,"World")  );
    tree.insert("Hell", a+2);   Y_CHECK( FoundIn(tree,"Hell")   );
    tree.insert("Helico", a+3); Y_CHECK( FoundIn(tree,"Helico") );
    tree.free();
    Y_PRINTV(tree.size);
    Y_PRINTV(tree.pool.size);
}
Y_UDONE()

