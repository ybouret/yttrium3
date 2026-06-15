

#include "y/chemical/reactive/equilibria.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        const char * const Equilibria:: CallSign = "Equilibria";

        Equilibria:: ~Equilibria() noexcept
        {
        }

        Y_Proxy_Impl(Equilibria,db)
        
        Equilibria:: Equilibria() :
        Proxy<const EqSet>(),
        efmt(),
        rfmt(),
        pfmt(),
        db(),
        t_print(0)
        {}

        Equilibria:: Equilibria(const Equilibria &eqs) :
        Proxy<const EqSet>(),
        efmt(eqs.efmt),
        rfmt(eqs.rfmt),
        pfmt(eqs.pfmt),
        db(eqs.db),
        t_print(eqs.t_print)
        {}

        void Equilibria:: add(const EqPtr &eq)
        {
            if(eq->indx[TopLevel] != db.size()+1 )
                throw Specific::Exception(CallSign,"invalid '%s' top-level index", eq->name.c_str() );

            // check
            

            // try insert
            if(!db.insert(eq))
                throw Specific::Exception(CallSign,"multiple '%s'", eq->name.c_str() );

            // update
            Coerce(efmt).enroll(*eq);
            Coerce(rfmt).enroll(eq->reac);
            Coerce(pfmt).enroll(eq->prod);

        }

    }

}
