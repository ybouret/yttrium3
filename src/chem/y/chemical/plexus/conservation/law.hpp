
#ifndef Y_Chemical_Conservation_Law_Included
#define Y_Chemical_Conservation_Law_Included 1

#include "y/chemical/reactive/actors.hpp"
#include "y/chemical/slist.hpp"
#include "y/container/matrix.hpp"
#include "y/xml/log.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        namespace Conservation
        {


            class PCoef : public Object
            {
            public:
                typedef CxxListOf<PCoef> List;
                explicit PCoef(const xreal_t, const Species &) noexcept;
                virtual ~PCoef() noexcept;
                Y_OSTREAM_PROTO(PCoef);

                const PCoef & operator*() const noexcept { return *this; }

                

                const xreal_t  cf;
                const Species &sp;
                PCoef         *next;
                PCoef         *prev;

            private:
                Y_Disable_Copy_And_Assign(PCoef);
            };

            class Proj : public Object, public PCoef::List
            {
            public:
                typedef CxxListOf<Proj> List;
                explicit Proj(const Species &, const xreal_t) noexcept;
                virtual ~Proj()                noexcept;
                Y_OSTREAM_PROTO(Proj);
                
                void     build(const SList         &species,
                               const Readable<apz> &weights);

                const Species &sp;   //!< target species
                const xreal_t  scal; //!< scaling
                Proj *         next;
                Proj *         prev;

            private:
                Y_Disable_Copy_And_Assign(Proj);

            };


            //__________________________________________________________________
            //
            //
            //
            //! Single conservation law
            //
            //
            //__________________________________________________________________
            class Law : public Actors, public Vizible
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef CxxListOf<Law> List; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Law() noexcept; //!< setup empty
                virtual ~Law() noexcept; //!< cleanup
                Y_OSTREAM_PROTO(Law);   //!< display

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                xreal_t excess(const XReadable &, const Level, XAdd &) const;

                //! emit GraphViz code
                /**
                 \param fp output stream
                 \param color optional color
                 \return fp
                 */
                OutputStream & viz(OutputStream &fp, const char * const color) const;
                String         html() const; //!< \return html label

                bool linkedTo( const Law & ) const noexcept; //!< \return true iff common species

                //! \param slist from canon
                void compile(XML::Log &xml, const SList &slist);

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const xreal_t    gamma2; //!< sum |coef|^2
                const xreal_t    gamma;  //!< sqrt(gamma)
                const Proj::List lproj;  //!< list of projections
                Law *            next;   //!< for list
                Law *            prev;   //!< for list

            private:
                Y_Disable_Copy_And_Assign(Law); //!< discarded
            };


        }
    }

}

#endif // !Y_Chemical_Conservation_Law_Included

