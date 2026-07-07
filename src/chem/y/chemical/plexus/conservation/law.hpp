
#ifndef Y_Chemical_Conservation_Law_Included
#define Y_Chemical_Conservation_Law_Included 1

#include "y/chemical/reactive/actors.hpp"
#include "y/chemical/slist.hpp"
#include "y/chemical/type/matrix.hpp"
#include "y/chemical/plexus/conservation/law/proj.hpp"
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
                typedef CxxListOf<Law>      List; //!< alias
                static const char *  const  Name; //!< Conservation::Law

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
                void compile(XML::Log      &xml,
                             const SList   &slist,
                             const IMatrix &topNuT);


                XWritable & project(XWritable       &target, const Level tgt,
                                    const XReadable &source, const Level src,
                                    XAdd &xadd) const;
                
                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const xreal_t    gamma2; //!< sum |coef|^2
                const xreal_t    gamma;  //!< sqrt(gamma)
                const Proj::List projected;  //!< list of projected species
                const SList      untouched;  //!< list of untouched species
                Law *            next;   //!< for list
                Law *            prev;   //!< for list

            private:
                Y_Disable_Copy_And_Assign(Law); //!< discarded
            };


        }
    }

}

#endif // !Y_Chemical_Conservation_Law_Included

