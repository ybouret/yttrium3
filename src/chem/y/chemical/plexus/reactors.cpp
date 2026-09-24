
#include "y/chemical/plexus/reactors.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        Reactors:: Reactors(const Clusters &cls) :
        clusters(cls),
        reactors()
        {
            for(const Cluster *cl = cls->head; cl; cl=cl->next)
            {
                reactors.pushTail( new Reactor(*cl) );
            }
        }

        Reactors:: ~Reactors() noexcept
        {

        }



        Y_Proxy_Impl(Reactors,reactors)

        void Reactors:: operator()(XML::Log  & xml,
                                   XWritable & C,
                                   const Level L,
                                   const size_t maxCycle)
        {
            Y_XML_Element(xml,TransformReactors);
            for(Reactor *reactor=reactors.head;reactor;reactor=reactor->next)
                (void) reactor->transform(xml,C,L,clusters.K,maxCycle);

        }

    }

}
