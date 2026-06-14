
//! \file

#ifndef Y_Chemical_Components_Included
#define Y_Chemical_Components_Included 1

#include "y/chemical/reactive/actors.hpp"
#include "y/chemical/type/assembly.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        class Components : public Indexed
        {
        public:
            explicit Components(const String &, const size_t);
            virtual ~Components() noexcept;

            void addReac(const unsigned nu, const Species &sp);
            void addProd(const unsigned nu, const Species &sp);

            const Actors   reac;
            const Actors   prod;
            

        private:
            Y_Disable_Copy_And_Assign(Components);
            void checkUnused(const char * const, const Species &) const;
        };

    }
}

#endif // !Y_Chemical_Components_Included

