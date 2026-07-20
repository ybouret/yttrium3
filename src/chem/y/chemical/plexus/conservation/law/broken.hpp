

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
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                //! setup
                /**
                 \param theLaw broken law
                 \param excess current excess
                 \param thePrj where to store projected data
                 */
                Broken(const Law    &theLaw,
                       const xreal_t excess,
                       XWritable    &thePrj) noexcept;
                Broken(const Broken &) noexcept; //!< duplicate
                ~Broken()              noexcept; //!< cleanup
                Y_OSTREAM_PROTO(Broken);         //!< display

                //______________________________________________________________
                //
                //
                // methods
                //
                //______________________________________________________________
                const Law & law; //!< the law
                xreal_t     xsc; //!< excess of concentration
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

