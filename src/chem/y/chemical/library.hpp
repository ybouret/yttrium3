

//! \file

#ifndef Y_Chemical_Library_Included
#define Y_Chemical_Library_Included 1

#include "y/chemical/species.hpp"
#include "y/container/associative/hash/set.hpp"
#include "y/pointer/keyed.hpp"
#include "y/type/proxy.hpp"
#include "y/ability/freezable.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        typedef Keyed<String, ArcPtr<Species>> SpPtr;
        typedef HashSet<String,SpPtr>          SpSet;

        class Library :
        public Proxy<const SpSet>,
        public Freezable
        {
        public:
            static const char * const CallSign;
            
            explicit Library();
            virtual ~Library() noexcept;

            Species & operator[](const Formula &);
            

        private:
            Y_Disable_Copy_And_Assign(Library);
            Y_Proxy_Decl();
            SpSet db;
        };
    }

}

#endif // !Y_Chemical_Library_Included
