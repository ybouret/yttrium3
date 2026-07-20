
//! \file

#ifndef Y_Ink_Histogram_Build_Included
#define Y_Ink_Histogram_Build_Included 1

#include "y/ink/histogram.hpp"
#include "y/ink/pixmap.hpp"
#include <cstring>

namespace Yttrium
{
    namespace Ink
    {
        //______________________________________________________________________
        //
        //
        //
        //! Building Histograms
        //
        //
        //______________________________________________________________________
        struct BuildHistogram
        {
            typedef Histogram::freq_t freq_t; //!< alias


            //______________________________________________________________________
            //
            //
            //! Ops class
            //
            //______________________________________________________________________
            class Ops
            {
            public:
                static const unsigned     Bins  = Histogram::Bins;        //!< alias
                static const size_t       Bytes = sizeof(freq_t) * Bins; //!< alias

                explicit Ops() noexcept; //!< setup
                virtual ~Ops() noexcept; //!< cleanup

                //! collect data in local cache
                /**
                 \param tile tile to scan
                 \param source source to read
                 \param proc   pixel to byte value
                 */
                template <typename T, typename PIXEL_TO_BYTE> inline
                void collect(Tile &tile, const Pixmap<T> &source, PIXEL_TO_BYTE &proc)
                {
                    assert(tile.bytes>=Bytes);
                    assert(tile.entry);
                    freq_t * const H = static_cast<freq_t *>( memset(tile.entry,0,Bytes) );
                    for(unit_t k=tile.span;k>0;--k)
                    {
                        const Segment                  s = tile[k];
                        const typename Pixmap<T>::Row &r = source(s.start.y);
                        for(unit_t x=s.start.x,i=s.width;i>0;--i,++x)
                        {
                            const T &     data = r(x);
                            const uint8_t byte = proc(data);
                            ++H[byte];
                        }
                    }
                }

            private:
                Y_Disable_Copy_And_Assign(Ops); //!< discarded
            };

            //! add histogram from source to given histogram
            /**
             \param H      target histogram
             \param broker broker
             \param source source pixmap
             \param proc   pixel to byte value
             */
            template <typename T, typename PIXEL_TO_BYTE> static inline
            void Add(Histogram       & H,
                     Broker          & broker,
                     const Pixmap<T> & source,
                     PIXEL_TO_BYTE   & proc)
            {
                {
                    Ops ops;
                    broker.ensureCache(Ops::Bytes);
                    broker(source, ops, & Ops::collect<T,PIXEL_TO_BYTE>, proc);
                }
                Merge(H,broker);
            }

        private:
            static void Merge(Histogram &, Broker &); //!< merge local histograms


        };
    }

}

#endif // !Y_Ink_Histogram_Build_Included
