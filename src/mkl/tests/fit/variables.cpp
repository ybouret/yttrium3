
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

            class Variable : public CountedObject
            {
            public:
                static const char * const                CallSign;
                typedef Keyed< String,ArcPtr<Variable> > Pointer;

                template <typename NAME>
                inline   Variable(const NAME &varName) :
                CountedObject(), name(varName)
                {
                    checkName();
                }

                virtual ~Variable() noexcept;

                const String name;

                virtual size_t indx() const noexcept = 0;
                const String  & key() const noexcept;

                friend std::ostream & operator<<(std::ostream &os, const Variable &var)
                {

                    os << var.name << '@' << var.indx();
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
                if(name.size()<=0)
                    throw Specific::Exception(CallSign, "empty name");
            }

            const String  & Variable:: key() const noexcept
            {
                return name;
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

            private:
                Y_Disable_Copy_And_Assign(ReplicaVariable);
                const Variable::Pointer ptr;
                static Variable * CheckVariable(const Variable &);
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

                template <typename NAME>
                const Variable & operator()(const NAME &alias, const Variable &source)
                {
                    const Variable::Pointer var = new ReplicaVariable(alias,source);
                    return insert(var);
                }




            private:
                VarDB vdb;
                Y_Proxy_Decl();
                const Variable & insert( const Variable::Pointer &var );
            };


            Y_Proxy_Impl(Variables,vdb)

            Variables:: ~Variables() noexcept
            {
            }

            Variables:: Variables() : vdb()
            {
            }

            Variables:: Variables(const Variables &other) :
            vdb(other.vdb)
            {
            }

            Variables & Variables:: operator=( const Variables &other )
            {
                VarDB _(other.vdb);
                vdb.xch(_);
                return *this;
            }

            const Variable & Variables:: insert( const Variable::Pointer &var )
            {
                const String & name = var->name;
                const size_t   indx = var->indx();
                for(Iterator it=vdb.begin();it!=vdb.end();++it)
                {
                    const Variable &v = **it;

                    if(v.name==name)
                        throw Specific::Exception(Variable::CallSign, "multiple '%s'", name.c_str());

                    if(v.indx()==indx)
                        throw Specific::Exception(Variable::CallSign, "'%s' has same index #%s than '%s'", name.c_str(), Decimal(indx).c_str(), v.name.c_str() );

                }

                if(!vdb.insert(var))
                    throw Specific::Exception(Variable::CallSign,"unexpect insertion failure of '%s'", name.c_str());

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

    std::cerr << vars << std::endl;


}
Y_UDONE()

