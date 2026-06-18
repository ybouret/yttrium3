
#include "y/chemical/plexus/combinatorics.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        Combinatorics:: ~Combinatorics() noexcept
        {
        }


        Combinatorics:: Combinatorics(XML::Log   & xml,
                                      Topology   & topo,
                                      Equilibria & eqs)
        {
            Y_XML_Element(xml,BuildCombinatorics);
            
        }
        
    }

}
