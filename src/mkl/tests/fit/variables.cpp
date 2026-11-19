#include "y/mkl/fit/variable/primary.hpp"
#include "y/mkl/fit/variable/replica.hpp"

#include "y/exception.hpp"




#include "y/container/associative/suffix/set.hpp"
#include "y/type/proxy.hpp"


#include "y/format/decimal.hpp"
#include "y/core/max.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {
            typedef SuffixSet<String,Variable::Pointer> VarDB;

            class Variables : public Proxy<const VarDB>
            {
            public:
                // Definitions
                typedef VarDB::Iterator Iterator;
                typedef VarDB::ConstIterator ConstIterator;

                // C++
                explicit Variables();
                virtual ~Variables() noexcept;
                Variables(const Variables &);
                Variables & operator=( const Variables &);


                // Methods

                //! create a new, automatically indexed, primary variable
                /**
                 \param varName variable name
                 \return created variable
                 */
                template <typename NAME>
                const Variable & operator()(const NAME &varName)
                {
                    const Variable::Pointer var = new PrimaryVariable(varName, vdb.size()+1);
                    return insert(var);
                }

                //! create a new replica variable
                /**
                 \param alias  name of the alias
                 \param source original variable
                 \return created variable
                 */
                template <typename NAME>
                const Variable & operator()(const NAME &alias, const Variable &source)
                {
                    const Variable::Pointer var = new ReplicaVariable(alias,source);
                    return insert(var);
                }

                //! insert a copy of an existing variable
                /**
                 \param  source original variable
                 \return created variable
                 */
                const Variable & operator()(const Variable &source)
                {
                    const Variable::Pointer var = ReplicaVariable::CheckVariable(source);
                    return insert(var);
                }

                template <typename RHS> inline
                Variables & operator<<(const RHS &rhs)
                {
                    Variables &self = *this;
                    self(rhs);
                    return self;
                }

                friend std::ostream & operator<<(std::ostream &os, const Variables &vars)
                {
                    return os << vars.vdb << "|span=" << vars.span;
                }

            private:
                Y_Proxy_Decl();
                const Variable & insert( const Variable::Pointer &var );

                VarDB vdb;
            public:
                const size_t span;
            };


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




        }



    }
}

#include "y/utest/run.hpp"
#include "y/container/sequence/vector.hpp"

using namespace Yttrium;
using namespace MKL;


Y_UTEST(fit_variables)
{


    Fit::Variables       vars;
    const Fit::Variable &D1 = vars("D1");
    const Fit::Variable &D2 = vars("D2");
    const Fit::Variable &t0 = vars("t0");

    Y_PRINTV(vars);

    {
        Fit::Variables v1;
        v1("D",D1);
        Y_PRINTV(v1);

        v1 << t0;
        Y_PRINTV(v1);
        {
            const Fit::Variables cpy1 = v1;
            Y_PRINTV(cpy1);
        }
        v1 = vars;
        Y_PRINTV(v1);
    }

    std::cerr << std::endl;
    Y_PRINTV(vars);
    Vector<size_t>          vec;
    const Readable<size_t> &cst = vec;
    vec << 1 << 2 << 3;

    Y_PRINTV(D1[vec]);
    Y_PRINTV(D2[vec]);
    Y_PRINTV(t0[vec]);
    Y_PRINTV(D1[cst]);
    Y_PRINTV(D2[cst]);
    Y_PRINTV(t0[cst]);
}
Y_UDONE()

