//! \file

#ifndef Y_MKL_Fit_SampleMetrics_Included
#define Y_MKL_Fit_SampleMetrics_Included 1

#include "y/mkl/fit/variables.hpp"
#include "y/concurrent/mutex.hpp"

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
            //! SampleMetrics : cardinal and name
            //
            //
            //__________________________________________________________________
            class SampleMetrics : public String
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                //! setup \param name compatible name
                template <typename NAME> inline
                explicit SampleMetrics(const NAME &name) :
                String(name),
                vars(),
                access()
                {
                }

                //! cleanup
                virtual ~SampleMetrics() noexcept;

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual size_t cardinal()  const noexcept = 0; //!< number of samples
                virtual void   save(OutputStream &) const = 0; //!< save content

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                void           checkCardinal() const; //!< check positive cardinal
                void           autoSave()      const; //!< save in name.data
                static size_t  AddendaSizeFor(const size_t nvar); //!< nvar + (n*(1+nvar))/2



                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                Variables         vars;   //!< own variables
                Concurrent::Mutex access; //!< access mutex

            private:
                Y_Disable_Copy_And_Assign(SampleMetrics); //!< discarded

            };

        }

    }

}

#endif // !Y_MKL_Fit_SampleMetrics_Included

