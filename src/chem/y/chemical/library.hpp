

//! \file

#ifndef Y_Chemical_Library_Included
#define Y_Chemical_Library_Included 1

#include "y/chemical/species.hpp"
#include "y/container/associative/hash/set.hpp"
#include "y/pointer/keyed.hpp"
#include "y/type/proxy.hpp"
#include "y/ability/freezable.hpp"
#include "y/chemical/type/assembly.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        typedef Keyed<String, ArcPtr<Species>> SpPtr; //!< alias
        typedef HashSet<String,SpPtr>          SpSet; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! Database of species
        //
        //
        //______________________________________________________________________
        class Library :
        public Proxy<const SpSet>,
        public Freezable,
        public Assembly
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const    CallSign;      //!< "Library"
            typedef SpSet::ConstIterator ConstIterator; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Library();          //!< setup
            virtual ~Library() noexcept; //!< cleanup
            Y_OSTREAM_PROTO(Library);    //!< display

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \return on-the-fly or existing species matching formula
            Species & operator[](const Formula &);
            

        private:
            Y_Disable_Copy_And_Assign(Library); //!< discarded
            Y_Proxy_Decl();                     //!< helper
            SpSet db;                           //!< inner database
        };
    }

}

#endif // !Y_Chemical_Library_Included
