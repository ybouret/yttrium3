

//! \file

#ifndef Y_Chemical_Equilibrium_Group_Included
#define Y_Chemical_Equilibrium_Group_Included 1

#include "y/chemical/reactive/equilibrium.hpp"
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
            Y_OSTREAM_PROTO(EGroup);

            bool     accepts(const Equilibrium &another) const noexcept
            {
                for(const ENode *en=(**this).head;en;en=en->next)
                {
                    if( (**en).linkedTo(another) ) return true;
                }
                return false;
            }

            void finalize() noexcept;

            EGroup * next;
            EGroup * prev;
        private:
            Y_Disable_Copy_And_Assign(EGroup);
        };
    }

}

#endif // !Y_Chemical_Equilibrium_Group_Included
