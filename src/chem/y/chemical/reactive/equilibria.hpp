
//! \file

#ifndef Y_Chemical_Equilibria_Included
#define Y_Chemical_Equilibria_Included 1

#include "y/chemical/reactive/equilibrium/format.hpp"
#include "y/container/associative/hash/set.hpp"
#include "y/pointer/keyed.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        typedef Keyed<String, ArcPtr<Equilibrium>> EqPtr;
        typedef HashSet<String,EqPtr>              EqSet;

        class Equilibria :
        public Proxy<const EqSet>,
        public EqFormat
        {
        public:
            static const char * const    CallSign;
            typedef EqSet::ConstIterator ConstIterator;

            explicit Equilibria();
            virtual ~Equilibria() noexcept;
            Equilibria(const Equilibria &);
            Y_OSTREAM_PROTO(Equilibria);


            void           add(const EqPtr &); //!< add a precompiled equilibria
            std::ostream & print(std::ostream &os, const bool wK) const;


        private:
            Y_Disable_Assign(Equilibria);
            Y_Proxy_Decl();
            EqSet db;
        public:
            xreal_t t_print; //!< time to print constants
        };
    }

}

#endif // !Y_Chemical_Equilibria_Included
