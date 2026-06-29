

#ifndef Y_Chemical_Conservation_Canon_Included
#define Y_Chemical_Conservation_Canon_Included 1

#include "y/chemical/plexus/conservation/law.hpp"
#include "y/chemical/type/roll.hpp"
#include "y/chemical/type/assembly.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        namespace Conservation
        {

            typedef Handy::BasicLightList<const Law> LList;
            typedef LList::NodeType                  LNode;

            class Canon : public Roll<Species>
            {
            public:
                typedef CxxListOf<Canon> List;

                explicit Canon(const Law &first);
                virtual ~Canon() noexcept;

                bool accepts(const Law &) const noexcept;
                void compile();

                LList    laws;
                Canon *  next;
                Canon *  prev;
                Assembly lfmt;

            private:
                Y_Disable_Copy_And_Assign(Canon);
            };
        }

    }

}

#endif // !Y_Chemical_Conservation_Canon_Included
