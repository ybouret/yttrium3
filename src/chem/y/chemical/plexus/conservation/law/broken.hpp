

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
            //__________________________________________________________________
            //
            //
            //
            //! Broken law description
            //
            //
            //__________________________________________________________________
            class Broken
            {
            public:
                Broken(const Law &, const xreal_t, XWritable &) noexcept;
                Broken(const Broken &) noexcept; //!< duplicate
                ~Broken()              noexcept; //!< cleanup
                Y_OSTREAM_PROTO(Broken);         //!< display

                const Law & law; //!< the law
                xreal_t     bad; //!< bad score
                XWritable & prj; //!< projected concentration

            private:
                Y_Disable_Assign(Broken); //!< discarded
            };

            typedef Handy::PlainHeavyList<Broken> BList; //!< alias
            typedef BList::NodeType               BNode; //!< alias
        }

    }

}

#endif // !Y_Chemical_Conservation_Broken_Included

