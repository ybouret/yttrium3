
//! \file

#ifndef Y_MKL_Fit_Variables_Included
#define Y_MKL_Fit_Variables_Included 1

#include "y/mkl/fit/variable/primary.hpp"
#include "y/mkl/fit/variable/replica.hpp"

#include "y/container/associative/suffix/set.hpp"
#include "y/type/proxy.hpp"

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
                Y_OSTREAM_PROTO(Variables);

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

               

            private:
                Y_Proxy_Decl();
                const Variable & insert( const Variable::Pointer &var );

                VarDB vdb;
            public:
                const size_t span;
            };


          



        }



    }
}


#endif // !Y_MKL_Fit_Variables_Included
