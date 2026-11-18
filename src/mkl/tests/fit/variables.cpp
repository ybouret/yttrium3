
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

                explicit Variable(const String &varName);
                virtual ~Variable() noexcept;

                const String name;

                virtual size_t indx() const noexcept = 0;
                const String  & key() const noexcept;

            private:
                Y_Disable_Copy_And_Assign(Variable);
            };

            const char * const Variable:: CallSign = "Fit::Variable";

            Variable:: ~Variable() noexcept {}
            Variable:: Variable(const String &varName) :
            CountedObject(),
            name(varName)
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
                explicit PrimaryVariable(const String &varName, const size_t varIndx);

                virtual ~PrimaryVariable() noexcept;

                virtual size_t indx() const noexcept;

            private:
                Y_Disable_Copy_And_Assign(PrimaryVariable);
                const size_t indx_;
            };

            PrimaryVariable:: ~PrimaryVariable() noexcept
            {
            }

            PrimaryVariable:: PrimaryVariable(const String &varName, const size_t varIndx) :
            Variable(varName),
            indx_( varIndx )
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
                explicit ReplicaVariable(const String &varName, const Variable::Pointer &primaryVar);

                virtual ~ReplicaVariable() noexcept;
            private:
                Y_Disable_Copy_And_Assign(ReplicaVariable);
                const Variable::Pointer primary;
            };

            ReplicaVariable:: ~ReplicaVariable() noexcept
            {
            }

            ReplicaVariable:: ReplicaVariable(const String &varName, const Variable::Pointer &primaryVar) :
            Variable(varName),
            primary(primaryVar)
            {

            }
        }


    }

}

#include "y/container/associative/suffix/set.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {
            typedef SuffixSet<String,Variable::Pointer> VarDB;

            class Variables : public VarDB
            {
            public:
                explicit Variables();
                virtual ~Variables() noexcept;
                Variables(const Variables &);
                Variables & operator=( const Variables &);
            };

            Variables:: ~Variables() noexcept
            {
            }

            Variables:: Variables() : VarDB()
            {
            }

            Variables:: Variables(const Variables &other) :
            VarDB(other)
            {
            }

            Variables & Variables:: operator=( const Variables &other )
            {
                Variables _(other);
                xch(_);
                return *this;
            }




        }



    }
}

#include "y/utest/run.hpp"

Y_UTEST(fit_variables)
{

}
Y_UDONE()

