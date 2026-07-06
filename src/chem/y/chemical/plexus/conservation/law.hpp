
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
                const xreal_t gamma2; //!< sum |coef|^2
                const xreal_t gamma;  //!< sqrt(gamma)
                Law *         next;   //!< for list
                Law *         prev;   //!< for list

            private:
                Y_Disable_Copy_And_Assign(Law); //!< discarded
            };


        }
    }

}

#endif // !Y_Chemical_Conservation_Law_Included

