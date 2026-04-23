//! \file

#ifndef Y_Coven_Metrics_Included
#define Y_Coven_Metrics_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{

    namespace Coven
    {
        //______________________________________________________________________
        //
        //
        //
        //! Metrics for a vector space
        //
        //
        //______________________________________________________________________
        class Metrics
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________

            //! describe quality
            enum Quality
            {
                Degenerate, //!< no vectors
                Fragmental, //!< vectors bu below hyperplane
                HyperPlane, //!< hyperplane, codimension=1
                TotalSpace  //!< matches full space (a.k.a basis)
            };

            //! \return textual quality
            static const char * HumanReadableQuality(const Quality) noexcept;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Metrics(const size_t dims) noexcept; //!< setup \param dims dims > 0
            virtual ~Metrics()                  noexcept; //!< cleanup
            Metrics(const Metrics &)            noexcept; //!< duplicate


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \param size \return qualit according to size w.r.t dimension
            Quality computeQuality(const size_t size) const noexcept;

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t dimension; //!< dimension of space
            const size_t hyperSize; //!< dimension-1

        private:
            Y_Disable_Assign(Metrics); //!< discarded
        };

    }

}

#endif // !Y_Coven_Metrics_Included
