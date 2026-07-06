
#ifndef Y_Chemical_Conservation_Proj_Included
#define Y_Chemical_Conservation_Proj_Included 1

#include "y/chemical/plexus/conservation/law/pcoef.hpp"
#include "y/chemical/slist.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        namespace Conservation
        {
            class Proj : public Object, public PCoef::List
            {
            public:
                typedef CxxListOf<Proj> List;
                explicit Proj(const Species &, const xreal_t) noexcept;
                virtual ~Proj()                noexcept;
                Y_OSTREAM_PROTO(Proj);

                //! build coefficients
                /**
                 \param species list of species
                 \param weights array of weights
                 */
                void     build(const SList         &species,
                               const Readable<apz> &weights);

                void     apply(XWritable       &target, const Level tgt,
                               const XReadable &source, const Level src,
                               XAdd & xadd) const;

                const Species &sp;   //!< target species
                const xreal_t  scal; //!< scaling
                Proj *         next;
                Proj *         prev;

            private:
                Y_Disable_Copy_And_Assign(Proj);

            };
        }
    }
}

#endif // !Y_Chemical_Conservation_Proj_Included
