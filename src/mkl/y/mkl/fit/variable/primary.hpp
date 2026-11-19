//! \file

#ifndef Y_MKL_Fit_PrimaryVariable_Included
#define Y_MKL_Fit_PrimaryVariable_Included 1

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
            //! Primary (a.k.a Global) variable
            //
            //
            //__________________________________________________________________
            class PrimaryVariable : public Variable
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
                 \param varIndx positive index
                */
                template <typename NAME> inline
                explicit PrimaryVariable(const NAME &varName, const size_t varIndx) :
                Variable(varName),
                indx_(varIndx)
                {
                    checkIndx();
                }

                //! cleanup
                virtual ~PrimaryVariable() noexcept;

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual size_t indx() const noexcept;

            private:
                Y_Disable_Copy_And_Assign(PrimaryVariable); //!< discard
                void checkIndx() const;                     //!< positive index
                const size_t indx_;                         //!< unique index
            };

           
        }

    }

}


#endif // !Y_MKL_Fit_PrimaryVariable_Included

