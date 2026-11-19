
//! \file

#ifndef Y_MKL_Fit_ReplicaVariable_Included
#define Y_MKL_Fit_ReplicaVariable_Included 1

#include "y/mkl/fit/variable.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {
            //__________________________________________________________________
            //
            //
            //
            //! Replica (a.k.a Local) variable
            //
            //
            //__________________________________________________________________
            class ReplicaVariable : public Variable
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param varName compatible name
                 \param variable existing DYNAMIC variable
                 */
                template <typename NAME> inline
                explicit ReplicaVariable(const NAME     &varName,
                                         const Variable &variable) :
                Variable(varName),
                ptr( CheckVariable(variable) )
                {
                }

                //! cleanup
                virtual ~ReplicaVariable() noexcept;

                //______________________________________________________________
                //
                //
                // interface
                //
                //______________________________________________________________
                virtual size_t indx() const noexcept;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! check DYNAMIC variable \return its address
                static Variable * CheckVariable(const Variable &);

            private:
                Y_Disable_Copy_And_Assign(ReplicaVariable); //!< disarded
                const Variable::Pointer ptr;                //!< inner pointer
            };

         


        }


    }

}
#endif // !Y_MKL_Fit_ReplicaVariable_Included

