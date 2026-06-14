
//! \file

#ifndef Y_Chemical_Equilibria_Included
#define Y_Chemical_Equilibria_Included 1

#include "y/chemical/reactive/equilibrium.hpp"
#include "y/container/associative/hash/set.hpp"
#include "y/pointer/keyed.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        typedef Keyed<String, ArcPtr<Equilibrium>> EqPtr;
        typedef HashSet<String,EqPtr>              EqSet;

        class Equilibria : public Proxy<const EqSet>
        {
        public:
            typedef EqSet::ConstIterator ConstIterator;

            explicit Equilibria();
            virtual ~Equilibria() noexcept;
            Equilibria(const Equilibria &);
            
            //Y_OSTREAM_PROTO(Library);

        private:
            Y_Disable_Assign(Equilibria);
            Y_Proxy_Decl();
            EqSet db;
        };
    }

}

#endif // !Y_Chemical_Equilibria_Included
