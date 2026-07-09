
#ifndef Y_Chemical_Conservation_PCoef_Included
#define Y_Chemical_Conservation_PCoef_Included 1

#include "y/chemical/species.hpp"
#include "y/chemical/type/defs.hpp"

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
            //! Projection coefficient
            //
            //
            //__________________________________________________________________
            class PCoef : public Object
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef CxxListOf<PCoef> List; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit PCoef(const xreal_t, const Species &) noexcept; //!< setup
                virtual ~PCoef() noexcept;                               //!< cleanup
                Y_OSTREAM_PROTO(PCoef);                                  //!< display

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                const PCoef & operator*() const noexcept; //!< helper to display list \return *this

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const xreal_t  cf;   //!< coefficient
                const Species &sp;   //!< species
                PCoef         *next; //!< for list
                PCoef         *prev; //!< for list

            private:
                Y_Disable_Copy_And_Assign(PCoef); //!< discarded
            };
        }

    }

}

#endif // !Y_Chemical_Conservation_PCoef_Included

