
#include "y/chemical/reactive/equilibrium/partition.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        Partition:: Partition(XML::Log &xml, Equilibria &eqs) :
        party()
        {
            typedef Handy::BasicLightList<EGroup> GList;

            Y_XML_Element_Attr(xml,BuildPartition, Y_XML_Attr(eqs->size()) );

            //__________________________________________________________________
            //
            //
            //
            // Loop over equilibria
            //
            //
            //__________________________________________________________________
            for(Equilibria::Iterator it=eqs.begin();it!=eqs.end();++it)
            {
                //______________________________________________________________
                //
                //
                // Look for accepting groups
                //
                //______________________________________________________________
                GList         accepting;
                Equilibrium & eq = **it;
                for(EGroup *g=party.head;g;g=g->next)
                    if(g->accepts(eq))
                        accepting << *g;

                if(xml.verbose)
                    eqs.efmt.print(xml(), eq) << " : #accepting=" << std::setw(3) << accepting->size << " => ";

                //______________________________________________________________
                //
                //
                // process result
                //
                //______________________________________________________________
                switch(accepting->size)
                {
                    case 0:
                        //______________________________________________________
                        //
                        // new group
                        //______________________________________________________
                        party.pushTail( new EGroup(eq) );
                        if(xml.verbose) *xml << *party.tail << std::endl;
                        continue;

                    case 1:
                        //______________________________________________________
                        //
                        // insert into sole group
                        //______________________________________________________
                        accepting.head() << eq;
                        if(xml.verbose) *xml << accepting.head() << std::endl;
                        continue;

                    default:
                        break;
                }

                //______________________________________________________________
                //
                //
                // fusion groups
                //
                //______________________________________________________________
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

            //__________________________________________________________________
            //
            //
            //
            // Finalize group(s)
            //
            //
            //__________________________________________________________________
            Y_XML_Element_Attr(xml,FinalizeParty,Y_XML_Attr(party.size));
            for(EGroup *g=party.head;g;g=g->next)
            {
                g->finalize();
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

        Partition:: ~Partition() noexcept
        {
        }

    }

}
