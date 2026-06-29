
#ifndef Y_Chemical_Conservation_Canons_Included
#define Y_Chemical_Conservation_Canons_Included 1

#include "y/chemical/plexus/conservation/canon.hpp"
#include "y/xml/log.hpp"
#include "y/chemical/type/assembly.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        namespace Conservation
        {
            class Canons : public Proxy<const Canon::List>
            {
            public:
                explicit Canons(XML::Log                &,
                                const Core::ListOf<Law> &,
                                const Assembly          &);
                virtual ~Canons() noexcept;

            private:
                Y_Disable_Copy_And_Assign(Canons);
                Y_Proxy_Decl();
                Canon::List list;
            };
        }

    }

}

#endif // !Y_Chemical_Conservation_Canons_Included

