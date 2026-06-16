
#include "y/chemical/weasel.hpp"
#include "y/utest/run.hpp"

#include "y/jive/syntax/grammar.hpp"
#include "y/stream/libc/output.hpp"
#include "y/handy/basic/light/list.hpp"
#include "y/xml/element.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        typedef Handy::BasicLightList<Equilibrium> EList;
        typedef EList::NodeType                    ENode;

        class EGroup : public Object, public EList
        {
        public:
            typedef CxxListOf<EGroup> List;

            explicit EGroup(Equilibrium &first);
            virtual ~EGroup() noexcept;
            Y_OSTREAM_PROTO(EGroup);

            bool     accepts(const Equilibrium &another) const noexcept
            {
                for(const ENode *en=(**this).head;en;en=en->next)
                {
                    if( (**en).linkedTo(another) ) return true;
                }
                return false;
            }

            EGroup * next;
            EGroup * prev;
        private:
            Y_Disable_Copy_And_Assign(EGroup);
        };

        EGroup:: EGroup( Equilibrium &first ) : Object(), EList()
        {
            (*this) << first;
        }


        EGroup:: ~EGroup() noexcept
        {
        }

        std::ostream & operator<<(std::ostream &os, const EGroup &g)
        {
            os << '[';
            const ENode *en = g->head;
            if(en)
            {
                os << (**en).name;
                for(en=en->next;en;en=en->next) os << ',' << (**en).name;
            }
            return os << ']';
        }



        class Partition
        {
        public:

            explicit Partition(XML::Log &xml, Equilibria &eqs);
            virtual ~Partition() noexcept;

        protected:
            EGroup::List party;

        private:
            Y_Disable_Copy_And_Assign(Partition);
        };

        Partition:: ~Partition() noexcept
        {
        }


        Partition:: Partition(XML::Log &xml, Equilibria &eqs) :
        party()
        {
            typedef Handy::BasicLightList<EGroup> GList;

            Y_XML_Element_Attr(xml,BuildPartition, Y_XML_Attr(eqs->size()) );
            for(Equilibria::Iterator it=eqs.begin();it!=eqs.end();++it)
            {
                GList         accepting;
                Equilibrium & eq = **it;
                for(EGroup *g=party.head;g;g=g->next)
                    if(g->accepts(eq))
                        accepting << *g;


                if(xml.verbose)
                    eqs.efmt.print(xml(), eq) << " : #accepting=" << std::setw(3) << accepting->size << " => ";

                switch(accepting->size)
                {
                    case 0:
                        // new group
                        party.pushTail( new EGroup(eq) );
                        if(xml.verbose) *xml << *party.tail << std::endl;
                        continue;

                    case 1:
                        // insert into sole group
                        accepting.head() << eq;
                        if(xml.verbose) *xml << accepting.head() << std::endl;
                        continue;

                    default:
                        break;
                }
                assert(accepting->size>=2);
                EGroup &target = **accepting->head; accepting.popHead();
                target << eq;
                while(accepting->size)
                {
                    EGroup &source = **accepting->head; accepting.popHead();
                    target->mergeTail( *source );
                    delete party.pop( &source );
                }
                if(xml.verbose) *xml << target << std::endl;
            }
            Y_XML_Element_Attr(xml,FinalizeParty,Y_XML_Attr(party.size));
            for(EGroup *g=party.head;g;g=g->next)
            {
                (**g).sortBy( Indexed::TopLevelCompare );
                Indexed::SubLabel(*g);
                Y_XMLog(xml, *g);
            }
            if(xml.verbose)
            {
                for(Equilibria::Iterator it=eqs.begin();it!=eqs.end();++it)
                {
                    Equilibrium &eq = **it;
                    eqs.efmt.print(xml(), eq);
                    Core::Display(*xml << " : ", eq.indx, eq.Levels) << std::endl;
                }
            }


        }


    }
}

using namespace Yttrium;
using namespace Chemical;

Y_UTEST(cluster)
{
    Weasel &   weasel = Weasel::Instance();
    Library    lib;
    Equilibria eqs;

    for(int i=1;i<argc;++i)
    {
        const String data = argv[i];
        weasel(Jive::Module::OpenData(data,data),lib,eqs);
    }

    std::cerr << "lib=" << lib << std::endl;
    std::cerr << "eqs=" << eqs << std::endl;

    bool      verbose = true;
    XML::Log  xml(std::cerr,verbose);
    Partition part(xml,eqs);

}
Y_UDONE()

