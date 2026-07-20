
//! \file

#ifndef Y_Ink_Histogram_Included
#define Y_Ink_Histogram_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Ink
    {

        class Histogram
        {
        public:
            static const unsigned Bins = 256;
            typedef size_t        freq_t;

            explicit Histogram() noexcept;
            virtual ~Histogram() noexcept;

            void ldz() noexcept;
            freq_t operator[](const uint8_t) const noexcept;

            void operator()(const uint8_t);
            void merge(const freq_t * const H) noexcept;
            

            const freq_t total;
        private:
            Y_Disable_Copy_And_Assign(Histogram);

            freq_t bin[Bins];
        };

    }

}

#endif // !Y_Ink_Histogram_Included

