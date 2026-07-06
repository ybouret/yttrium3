

#ifndef Y_Chemical_Conservation_Broken_Included
#define Y_Chemical_Conservation_Broken_Included 1

#include "y/chemical/type/defs.hpp"
#include "y/chemical/plexus/conservation/law.hpp"
#include "y/handy/plain/heavy/list.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        namespace Conservation
        {
            class Broken
            {
            public:
                Broken(const Law &, const xreal_t, XWritable &) noexcept;
                ~Broken() noexcept;
                Broken(const Broken &) noexcept;
                Y_OSTREAM_PROTO(Broken);

                const Law & law; //!< the law
                xreal_t     bad; //!< bad score
                XWritable & prj; //!< projected concentration

            private:
                Y_Disable_Assign(Broken);
            };

            typedef Handy::PlainHeavyList<Broken> BList;
            typedef BList::NodeType               BNode;
        }

    }

}

#endif // !Y_Chemical_Conservation_Broken_Included

