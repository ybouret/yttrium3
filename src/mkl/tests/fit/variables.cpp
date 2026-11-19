
#include "y/string.hpp"

#include "y/pointer/arc.hpp"
#include "y/pointer/keyed.hpp"

#include "y/exception.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            class Variable : public String
            {
            public:
                static const char * const                CallSign;
                typedef Keyed< String,ArcPtr<Variable> > Pointer;

                template <typename NAME>
                inline   Variable(const NAME &varName) :
                String(varName)
                {
                    checkName();
                }

                virtual ~Variable() noexcept;


                virtual size_t indx() const noexcept = 0;
                const String  & key() const noexcept;

                friend std::ostream & operator<<(std::ostream &os, const Variable &var)
                {

                    os << static_cast<const String&>(var) << '@' << var.indx();
                    return os;
                }

            private:
                Y_Disable_Copy_And_Assign(Variable);
                void checkName() const;
            };

            const char * const Variable:: CallSign = "Fit::Variable";

            Variable:: ~Variable() noexcept {}

            void Variable:: checkName() const
            {
                if(size()<=0)
                    throw Specific::Exception(CallSign, "empty name");
            }

            const String  & Variable:: key() const noexcept
            {
                return *this;
            }

        }

    }

}

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {
            class PrimaryVariable : public Variable
            {
            public:
                template <typename NAME> inline
                explicit PrimaryVariable(const NAME &varName, const size_t varIndx) :
                Variable(varName),
                indx_(varIndx)
                {
                    checkIndx();
                }
                virtual ~PrimaryVariable() noexcept;

                virtual size_t indx() const noexcept;

            private:
                Y_Disable_Copy_And_Assign(PrimaryVariable);
                void checkIndx() const;
                const size_t indx_;
            };

            PrimaryVariable:: ~PrimaryVariable() noexcept
            {
            }

            void PrimaryVariable:: checkIndx() const
            {
                if( indx_ <= 0 ) throw Specific::Exception(CallSign, "invalid index");
            }

            size_t PrimaryVariable:: indx() const noexcept
            {
                assert(indx_>0);
                return indx_;
            }

        }

    }

}

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {
            class ReplicaVariable : public Variable
            {
            public:
                template <typename NAME> inline
                explicit ReplicaVariable(const NAME     &varName,
                                         const Variable &variable) :
                Variable(varName),
                ptr( CheckVariable(variable) )
                {
                }

                virtual ~ReplicaVariable() noexcept;

                virtual size_t indx() const noexcept;

                static Variable * CheckVariable(const Variable &);

            private:
                Y_Disable_Copy_And_Assign(ReplicaVariable);
                const Variable::Pointer ptr;
            };

            ReplicaVariable:: ~ReplicaVariable() noexcept
            {
            }


            Variable * ReplicaVariable:: CheckVariable(const Variable &var)
            {
                if(var.quantity()<=0)
                    throw Specific::Exception(Variable::CallSign, "not a dynamic variable");
                return & Coerce(var);
            }



            size_t ReplicaVariable:: indx() const noexcept
            {
                return ptr->indx();
            }


        }


    }

}

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

            Variables:: Variables() : vdb(), span(0)
            {
            }

            Variables:: Variables(const Variables &other) :
            vdb(other.vdb), span(other.span)
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

using namespace Yttrium;
using namespace MKL;


Y_UTEST(fit_variables)
{

    Fit::Variables vars;
    const Fit::Variable &D1 = vars("D1");
    const Fit::Variable &D2 = vars("D2");
    const Fit::Variable &t0 = vars("t0");

    Y_PRINTV(vars);

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
Y_UDONE()

