
#include "y/chemical/weasel.hpp"
#include "y/utest/run.hpp"

#include "y/jive/syntax/grammar.hpp"
#include "y/stream/libc/output.hpp"
#include "y/handy/basic/light/list.hpp"

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



        class Partition
        {
        public:

            explicit Partition(Equilibria &eqs);
            virtual ~Partition() noexcept;

        protected:
            EGroup::List party;

        private:
            Y_Disable_Copy_And_Assign(Partition);
        };

        Partition:: ~Partition() noexcept
        {
        }


        Partition:: Partition(Equilibria &eqs) :
        party()
        {
            typedef Handy::BasicLightList<EGroup> GList;
            typedef GList::NodeType               GNode;

            for(Equilibria::Iterator it=eqs.begin();it!=eqs.end();++it)
            {
                GList         accepting;
                Equilibrium & eq = **it;

                for(EGroup *g=party.head;g;g=g->next)
                {
                    if(g->accepts(eq)) accepting << *g;
                }
                std::cerr << "#accepting: " << accepting->size << std::endl;
                switch(accepting->size)
                {
                    case 0:
                        // new group
                        party.pushTail( new EGroup(eq) );
                        continue;

                    case 1:
                        // insert into group
                        accepting.head() << eq;
                        continue;
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

    Partition part(eqs);

}
Y_UDONE()

