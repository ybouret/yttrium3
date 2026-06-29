
#ifndef Y_Chemical_Conservation_Law_Included
#define Y_Chemical_Conservation_Law_Included 1

#include "y/chemical/reactive/actors.hpp"

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
                explicit Law(const size_t) noexcept; //!< setup empty
                virtual ~Law()             noexcept; //!< cleanup
                Y_OSTREAM_PROTO(Law);                //!< display

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


                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const size_t irow; //!< index
                Law *        next; //!< for list
                Law *        prev; //!< for list

            private:
                Y_Disable_Copy_And_Assign(Law); //!< discarded
            };


        }
    }

}

#endif // !Y_Chemical_Conservation_Law_Included

