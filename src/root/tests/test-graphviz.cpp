#include "y/graphviz/vizible.hpp"
#include "y/graphviz/color-scheme.hpp"
#include "y/utest/run.hpp"
#include "y/core/list/cxx.hpp"
#include "y/stream/output.hpp"
#include "y/core/display.hpp"
#include "y/stream/libc/output.hpp"

using namespace Yttrium;

namespace
{
    class Node : public Object, public Vizible
    {
    public:
        explicit Node(const uint8_t c) noexcept :
        code(c),
        next(0),
        prev(0)
        {
        }

        virtual ~Node() noexcept
        {

        }

        OutputStream & viz(OutputStream &fp) const
        {
            nodeName(fp) << '[';
            String label = "'";
            label += (char)code;
            label += "'";
            Label(fp, label );
            const GraphViz::ColorScheme &cs = GraphViz::ColorScheme::Query("dark28");
            const String                 color = cs[code];
            fp << ",color="     << color;
            fp << ",fontcolor=" << color;
            fp << ']';
            Endl(fp);
            return fp;
        }


        const uint8_t code;
        Node *        next;
        Node *        prev;

    private:
        Y_Disable_Copy_And_Assign(Node);
    };
}

Y_UTEST(graphviz)
{
    CxxListOf<Node> list;
    for(unsigned i=0;i<256;++i) list.pushTail( new Node( (uint8_t)i) );
    Vizible::Render("zero.dot",*list.head);

    {
        OutputFile fp("gv.dot");
        Vizible::Enter(fp);
        for(const Node * node=list.head;node;node=node->next)
            node->viz(fp);

        for(const Node * node=list.head;node;node=node->next)
        {
            if(node->next)
            {
                Vizible::Endl(node->to(node->next,fp));
            }
            else
            {
                Vizible::Endl(node->to(list.head,fp));
            }
        }
        Vizible::Leave(fp);
    }
    Vizible::DotToPng("gv.dot");

    for(size_t i=0;i<GraphViz::ColorScheme::Count;++i)
        std::cerr << GraphViz::ColorScheme::Table[i] << std::endl;
}
Y_UDONE()



