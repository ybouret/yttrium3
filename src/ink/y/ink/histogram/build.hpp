
//! \file

#ifndef Y_Ink_Histogram_Build_Included
#define Y_Ink_Histogram_Build_Included 1

#include "y/ink/histogram.hpp"
#include "y/ink/pixmap.hpp"

namespace Yttrium
{
    namespace Ink
    {
        struct BuildHistogram
        {
            class Ops
            {
            public:
                typedef Histogram::freq_t freq_t;
                static const unsigned     Bins  = Histogram::Bins;
                static const size_t       Bytes = sizeof(freq_t) * Bins;

                explicit Ops() noexcept;
                virtual ~Ops() noexcept;

                template <typename T, typename PIXEL_TO_BYTE> inline
                void add(Tile &tile, const Pixmap<T> &source, PIXEL_TO_BYTE &proc)
                {
                    assert(tile.bytes>=Bytes);
                    
                }

            private:
                Y_Disable_Copy_And_Assign(Ops);
            };

            template <typename T, typename PIXEL_TO_BYTE> static inline
            void Add(Histogram       & H,
                     Broker          & broker,
                     const Pixmap<T> & source,
                     PIXEL_TO_BYTE   & proc)
            {
                Ops ops;
                broker.ensureCache(Ops::Bytes);
                broker(source, ops, & Ops::add<T,PIXEL_TO_BYTE>, proc);
            }



        };
    }

}

#endif // !Y_Ink_Histogram_Build_Included
