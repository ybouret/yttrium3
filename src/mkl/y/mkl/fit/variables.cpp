
#include "y/mkl/fit/variables.hpp"
#include "y/exception.hpp"
#include "y/format/decimal.hpp"
#include "y/core/max.hpp"


namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {
            Y_Proxy_Impl(Variables,vdb)

            Variables:: ~Variables() noexcept
            {
            }

            Variables:: Variables() :
            Proxy<const VarDB>(),
            vdb(), span(0)
            {
            }


            Variables:: Variables(const Variables &other) :
            Proxy<const VarDB>(),
            vdb(other.vdb),
            span(other.span)
            {
            }

            Variables & Variables:: operator=( const Variables &other )
            {
                VarDB _(other.vdb);
                vdb.xch(_);
                CoerceSwap(span,other.span);
                return *this;
            }

            const Variable & Variables:: insert( const Variable::Pointer &var )
            {
                const String & name = *var;
                const size_t   indx = var->indx();
                for(Iterator it=vdb.begin();it!=vdb.end();++it)
                {
                    const Variable &v = **it;

                    if(v==name)
                        throw Specific::Exception(Variable::CallSign, "multiple '%s'", name.c_str());

                    if(v.indx()==indx)
                        throw Specific::Exception(Variable::CallSign, "'%s' has same index #%s than '%s'", name.c_str(), Decimal(indx).c_str(), v.c_str() );

                }

                if(!vdb.insert(var))
                    throw Specific::Exception(Variable::CallSign,"unexpect insertion failure of '%s'", name.c_str());

                InSituMax( Coerce(span), indx );

                return *var;
            }

            std::ostream & operator<<(std::ostream &os, const Variables &vars)
            {
                return os << vars.vdb << "|span=" << vars.span;
            }


            const Variable & Variables:: operator[](const String &name) const
            {
                const Variable::Pointer *ppv = vdb.search(name);
                if(!ppv) throw Specific::Exception(Variable::CallSign,"missing '%s'", name.c_str() );
                return **ppv;
            }

            const Variable & Variables:: operator[](const char * const name) const
            {
                const String _(name); return (*this)[_];
            }


            const Variable & Variables:: operator[](const char name) const
            {
                const String _(name); return (*this)[_];
            }



        }

    }

}


