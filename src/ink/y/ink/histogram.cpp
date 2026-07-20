
#include "y/ink/histogram.hpp"
#include <cstring>
#include <cassert>

namespace Yttrium
{
    namespace Ink
    {

        Histogram:: ~Histogram() noexcept
        {
            ldz();
        }


        Histogram:: Histogram() noexcept :
        total(0),
        bin()
        {
            ldz();
        }

        void Histogram:: ldz() noexcept
        {
            Coerce(total) = 0;
            memset(bin,0,sizeof(bin));
        }

        Histogram::freq_t Histogram:: operator[](const uint8_t i) const noexcept
        {
            return bin[i];
        }

        void Histogram:: operator()(const uint8_t i)
        {
            ++bin[i];
            ++Coerce(total);
        }

        void Histogram:: merge(const freq_t * const H) noexcept
        {
            assert(H);
            for(unsigned i=0;i<Bins;++i)
            {
                const freq_t h = H[i];
                bin[i]        += h;
                Coerce(total) += h;
            }
        }



    }

}
