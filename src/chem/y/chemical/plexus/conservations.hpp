//! \file

#ifndef Y_Chemical_Plexus_Conservations_Included
#define Y_Chemical_Plexus_Conservations_Included 1

#include "y/chemical/type/roll/sp.hpp"
#include "y/chemical/plexus/topology.hpp"
#include "y/chemical/plexus/conservation/law.hpp"
#include "y/chemical/type/matrix.hpp"


namespace Yttrium
{
    namespace Chemical
    {

      
        

        //______________________________________________________________________
        //
        //
        //
        //! Conservation laws/dispatch species
        //
        //
        //______________________________________________________________________
        class Conservations
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            typedef Conservation::Law Law;    //!< alias
            typedef Law::List         Laws;   //!< alias
            

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Conservations(XML::Log &, const Topology &); //!< setup
            virtual ~Conservations() noexcept;                    //!< cleanup

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const UMatrix  Gamma;     //!< conservation matrix
            const size_t & Nc;        //!< Qm.rows
            const size_t   rg;        //!< rank of Qm
            const Laws     laws;      //!< conservation law(s)
            const SpDB     conserved; //!< conserved species
            const SpDB     unbounded; //!< unbounded species
            const Assembly lfmt;      //!< assembly to format laws
            
        private:
            Y_Disable_Copy_And_Assign(Conservations);          //!< discarded
            void computeVectors(XML::Log &, const Topology &); //!< compute row vectors of Gamma
            void collectSpecies(XML::Log &,const SList &);     //!< populate conserved/unbounded
        };

    }

}

#endif // !Y_Chemical_Plexus_Conservations_Included

