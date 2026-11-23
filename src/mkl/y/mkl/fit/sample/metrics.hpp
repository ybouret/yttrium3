//! \file

#ifndef Y_MKL_Fit_SampleMetrics_Included
#define Y_MKL_Fit_SampleMetrics_Included 1

#include "y/mkl/fit/variables.hpp"

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
            //! SampleMetrics
            //
            //
            //__________________________________________________________________
            class SampleMetrics : public String
            {
            public:
                template <typename NAME> inline
                explicit SampleMetrics(const NAME &name) :
                String(name),
                vars()
                {
                }

                virtual ~SampleMetrics() noexcept;


                virtual size_t cardinal()  const noexcept = 0;
                virtual void   save(OutputStream &) const = 0;

                void           checkSize() const;
                void           autoSave()  const;
                Variables      vars;

            private:
                Y_Disable_Copy_And_Assign(SampleMetrics);

            };

        }

    }

}

#endif

