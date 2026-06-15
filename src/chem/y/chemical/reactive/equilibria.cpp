

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
        EqFormat(),
        db(),
        t_print(0)
        {}

        Equilibria:: Equilibria(const Equilibria &eqs) :
        Proxy<const EqSet>(),
        EqFormat(eqs),
        db(eqs.db),
        t_print(eqs.t_print)
        {}

        void Equilibria:: add(const EqPtr &eq)
        {
            const char * const eid = eq->name.c_str();
            if(eq->indx[TopLevel] != db.size()+1 )
                throw Specific::Exception(CallSign,"invalid '%s' top-level index", eid );

            // check
            if( !eq->atLeastOneItem() ) throw Specific::Exception(CallSign,"'%s' is degenerate!",eid);
            if( !eq->electroneutral() ) throw Specific::Exception(CallSign,"'%s' is not electroneutral!",eid);
            

            // try insert
            if(!db.insert(eq))
                throw Specific::Exception(CallSign,"multiple '%s'", eq->name.c_str() );

            // update
            enroll(*eq);
        }

        std::ostream & Equilibria:: print(std::ostream &os, const bool wK) const
        {
            os << '{' << std::endl;
            for(ConstIterator it=db.begin();it!=db.end();++it)
            {
                const Equilibrium &eq = **it;
                (void) EqFormat::print(os,eq,wK,t_print);
            }
            return os << '}';
        }

        std::ostream & operator<<(std::ostream &os, const Equilibria &eqs)
        {
            return eqs.print(os,true);
        }


    }

}
