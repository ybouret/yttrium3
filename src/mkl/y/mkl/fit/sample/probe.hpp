
//! \file

#ifndef Y_MKL_Fit_SampleProbe_Included
#define Y_MKL_Fit_SampleProbe_Included 1

#include "y/mkl/fit/sample/core.hpp"
#include "y/container/matrix.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/cameo/addenda.hpp"

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
            //! Interface to probe D2 values
            //
            //
            //__________________________________________________________________
            template <typename ABSCISSA>
            class Probe
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef SampleCore<ABSCISSA>                    SampleCoreType; //!< alias
                typedef typename SampleCoreType::AdditionType   AdditionType;   //!< alias
                typedef typename SampleCoreType::AdditionHandle AdditionHandle; //!< alias
                typedef Cameo::Addenda<ABSCISSA>                AddendaType;    //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Probe();           //!< setup
                virtual ~Probe() noexcept;  //!< cleanup

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                void readyFor(const size_t nvar); //!< adjust and clear memory \param nvar dimensions

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                AdditionType           sumD2;    //!< gather D2
                Vector<AdditionHandle> sumBeta;  //!< gather beta
                Matrix<AdditionHandle> sumAlpha; //!< gather alpha
                AddendaType            addenda;  //!< inner additions

            private:
                Y_Disable_Copy_And_Assign(Probe); //!< discarded


            };
        }

    }

}


#endif // !Y_MKL_Fit_SampleProbe_Included
