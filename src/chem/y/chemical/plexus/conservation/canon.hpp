

#ifndef Y_Chemical_Conservation_Canon_Included
#define Y_Chemical_Conservation_Canon_Included 1

#include "y/chemical/plexus/conservation/law.hpp"
#include "y/handy/basic/light/list.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        namespace Conservation
        {

            typedef Handy::BasicLightList<const Law> LList;
            typedef LList::NodeType                  LNode;

            class Canon : public Object, public LList
            {
            public:
                explicit Canon(const Law &first);
                virtual ~Canon() noexcept;

                Canon * next;
                Canon * prev;
                
            private:
                Y_Disable_Copy_And_Assign(Canon);
            };
        }

    }

}

#endif // !Y_Chemical_Conservation_Canon_Included
