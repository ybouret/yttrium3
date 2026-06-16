
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
            class Law : public Actors
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
                // C++
                //
                //______________________________________________________________
                xreal_t excess(const XReadable &, const Level, XAdd &) const;

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
                Y_Disable_Copy_And_Assign(Law); //!< discarde
            };

        }
    }

}

#endif // !Y_Chemical_Conservation_Law_Included

