
#ifndef Y_Chemical_Stoichio_Included
#define Y_Chemical_Stoichio_Included 1

#include "y/container/cxx/array.hpp"
#include "y/core/list/cxx.hpp"
#include "y/type/proxy.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        typedef CxxArray<int> iArray;

        class Stoichio : public Object, public iArray
        {
        public:
            typedef CxxListOf<Stoichio> List;

            explicit Stoichio(const iArray &);
            virtual ~Stoichio() noexcept;
            
            Stoichio *next;
            Stoichio *prev;

        private:
            Y_Disable_Copy_And_Assign(Stoichio);
        };

        class StoichioDB : public Proxy<const Stoichio::List>
        {
        public:
            explicit StoichioDB() noexcept;
            virtual ~StoichioDB() noexcept;

            bool mayUse(const iArray &);

        private:
            Y_Disable_Copy_And_Assign(StoichioDB);
            Y_Proxy_Decl();

            CxxListOf<Stoichio> list;

        };

    }

}

#endif // !Y_Chemical_Stoichio_Included

