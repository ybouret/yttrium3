
#ifndef Y_Chemical_Plexus_Canon_Included
#define Y_Chemical_Plexus_Canon_Included 1

#include "y/chemical/plexus/topology.hpp"
#include "y/chemical/plexus/conservation/law.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        typedef Matrix<unsigned> UMatrix; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! Canon of conservation laws
        //
        //
        //______________________________________________________________________
        class Canon
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            typedef Conservation::Law Law;  //!< alias
            typedef Law::List         Laws; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Canon(XML::Log &, const Topology &); //!< setup
            virtual ~Canon() noexcept;                    //!< cleanup

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const UMatrix Qm;   //!< conservation matrix
            const size_t &Nc;   //!< Qm.rows
            const size_t  rg;   //!< rank of Qm
            const Laws    laws; //!< conservation law(s)

        private:
            Y_Disable_Copy_And_Assign(Canon); //!< discarded
            void prepare(XML::Log &);
        };

    }

}

#endif // !Y_Chemical_Plexus_Canon_Included

