
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


        bool operator==(const Histogram &lhs, const Histogram &rhs) noexcept
        {
            return lhs.total == rhs.total && 0==memcmp(lhs.bin,rhs.bin, Histogram::Bins * sizeof(Histogram::freq_t) );
        }

        bool operator!=(const Histogram &lhs, const Histogram &rhs) noexcept
        {
            return lhs.total != rhs.total || 0!=memcmp(lhs.bin,rhs.bin, Histogram::Bins * sizeof(Histogram::freq_t) );
        }


    }

}

#include "y/stream/output.hpp"
#include "y/format/decimal.hpp"

namespace Yttrium
{
    namespace Ink
    {
        void Histogram:: save(OutputStream &fp) const
        {
            for(unsigned i=0;i<Bins;++i)
            {
                fp("%u %s\n", i, Decimal(bin[i]).c_str());
            }
        }

    }

}
