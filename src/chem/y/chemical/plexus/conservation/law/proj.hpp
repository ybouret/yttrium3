
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
            //__________________________________________________________________
            //
            //
            //
            //! Projection code
            //
            //
            //__________________________________________________________________
            class Proj : public Object, public PCoef::List
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef CxxListOf<Proj> List; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Proj(const Species &, const xreal_t) noexcept; //!< setup with species and scaling
                virtual ~Proj()                               noexcept; //!< cleanup
                Y_OSTREAM_PROTO(Proj);                                  //!< discarded

                //! build coefficients
                /**
                 \param species list of species
                 \param weights array of weights
                 */
                void     build(const SList         &species,
                               const Readable<apz> &weights);

                //! compute projection
                /**
                 \param target write at sp(target,tgt)
                 \param tgt    target level
                 \param source source array
                 \param src    source level
                 \param xadd   addition
                 */
                void     apply(XWritable       &target, const Level tgt,
                               const XReadable &source, const Level src,
                               XAdd & xadd) const;

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Species &sp;   //!< target species
                const xreal_t  scal; //!< scaling factor
                Proj *         next; //!< for list
                Proj *         prev; //!< for list

            private:
                Y_Disable_Copy_And_Assign(Proj); //!< discarded

            };
        }
    }
}

#endif // !Y_Chemical_Conservation_Proj_Included
