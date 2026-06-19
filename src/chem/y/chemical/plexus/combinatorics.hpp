
#ifndef Y_Chemical_Plexus_Combinatorics_Included
#define Y_Chemical_Plexus_Combinatorics_Included 1

#include "y/chemical/plexus/topology.hpp"
#include "y/chemical/reactive/equilibria.hpp"


namespace Yttrium
{
    namespace Coven { class StandardSurvey; }

    namespace Chemical
    {

        //______________________________________________________________________
        //
        //
        //
        //! Create ccombinatorics from a group of equilibria
        //
        //
        //______________________________________________________________________
        class Combinatorics
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign;      //!< "Combinatorics"
            static const size_t       MinCoeff = 2;  //!< alias


            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! create from existing topology on equilibria
            explicit Combinatorics(XML::Log        &,
                                   Topology        &,
                                   Equilibria      &,
                                   const XReadable &);

            virtual ~Combinatorics() noexcept; //!< cleanup

        private:
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            Y_Disable_Copy_And_Assign(Combinatorics);
            void buildPrimary(Coven::StandardSurvey &,
                              XML::Log              &,
                              Topology              &) const;
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        };
    }

}

#endif // !Y_Chemical_Plexus_Combinatorics_Included

