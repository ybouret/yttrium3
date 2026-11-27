
//! \file

#ifndef Y_MKL_Fit_Variables_Included
#define Y_MKL_Fit_Variables_Included 1

#include "y/mkl/fit/variable/primary.hpp"
#include "y/mkl/fit/variable/replica.hpp"

#include "y/container/associative/suffix/set.hpp"
#include "y/type/proxy.hpp"
#include "y/format/justify.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {
            //__________________________________________________________________
            //
            //
            //! Base Proxy for Variables
            //
            //__________________________________________________________________
            typedef SuffixSet<String,Variable::Pointer> VarDB;

            //__________________________________________________________________
            //
            //
            //
            //! Set of variables
            //
            //
            //__________________________________________________________________
            class Variables : public Proxy<const VarDB>
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef VarDB::Iterator      Iterator;      //!< alias
                typedef VarDB::ConstIterator ConstIterator; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Variables();                      //!< setup empty
                virtual ~Variables() noexcept;             //!< cleanup
                Variables(const Variables &);              //!< duplicate
                Variables & operator=( const Variables &); //!< assign
                Y_OSTREAM_PROTO(Variables);                //!< display

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

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

                //! insert primary of aliased variable
                /**
                 \param rhs compatible name of variable
                 \return *this*
                 */
                template <typename RHS> inline
                Variables & operator<<(const RHS &rhs)
                {
                    Variables &self = *this;
                    (void)self(rhs);
                    return self;
                }

                const Variable & operator[](const String &)     const; //!< \return named variable
                const Variable & operator[](const char * const) const; //!< \return named variable
                const Variable & operator[](const char)         const; //!< \return named variable

                //! transfer matching data
                /**
                 \param target target array
                 \param source source array
                 \return target
                 */
                template <typename TARGET, typename SOURCE>
                inline TARGET & transfer(TARGET &target, SOURCE &source) const
                {
                    const size_t  n  = vdb.size();
                    ConstIterator it = vdb.begin();
                    for(size_t i=n;i>0;--i,++it)
                    {
                        const Variable &var = **it;
                        var[target] = var[source];
                        
                    }
                    return target;
                }

                template <typename ARRAY> inline
                std::ostream & display(std::ostream      & os,
                                       const char * const  sfx,
                                       ARRAY             & array,
                                       const char * const  pfx,
                                       const Justify::Type J = Justify::Center) const
                {
                    const size_t  n  = vdb.size();
                    ConstIterator it = vdb.begin();
                    for(size_t i=n;i>0;--i,++it)
                    {
                        const Variable &var = **it;
                        if(sfx) os << sfx;
                        os << Justify(var,wfmt,J);
                        if(pfx) os << pfx;
                        os << " = ";
                        os << var[array];
                        os << std::endl;
                    }
                    return os;
                }


            private:
                Y_Proxy_Decl(); //!< helper
                const Variable & insert( const Variable::Pointer & ); //!< \return inserted variable

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                VarDB vdb;         //!< inner database
            public:
                const size_t span; //!< maximum index
                const size_t wfmt; //!< width format
            };


          



        }



    }
}


#endif // !Y_MKL_Fit_Variables_Included
