
//! \file

#ifndef Y_Chemical_Plexus_Reactors_Included
#define Y_Chemical_Plexus_Reactors_Included 1

#include "y/chemical/plexus/reactor.hpp"
#include "y/chemical/plexus/clusters.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        //______________________________________________________________________
        //
        //
        //
        //! Reactors for Clusters
        //
        //
        //______________________________________________________________________
        class Reactors : public Proxy< const Core::ListOf<Reactor> >
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Reactors(const Clusters &); //!< setup
            virtual ~Reactors() noexcept;        //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! best effort run, status saved in each Reactor 'last'
            /**
             \param xml      output
             \param C        [in|out] state
             \param L        state level
             \param maxCycle positive to debug
             */
            void operator()(XML::Log  & xml,
                            XWritable & C,
                            const Level L,
                            const size_t maxCycle = 0);

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
        private:
            Y_Disable_Copy_And_Assign(Reactors); //!< discarded
            Y_Proxy_Decl();                      //!< helper
            const Clusters     & clusters;       //!< attached clusters
            CxxListOf<Reactor>   reactors;       //!< one reactor for each cluster

        };

    }

}

#endif // !Y_Chemical_Plexus_Reactors_Included


