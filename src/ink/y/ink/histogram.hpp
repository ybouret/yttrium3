
//! \file

#ifndef Y_Ink_Histogram_Included
#define Y_Ink_Histogram_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    class OutputStream;

    namespace Ink
    {
        //______________________________________________________________________
        //
        //
        //
        //! Histogram for bytes
        //
        //
        //______________________________________________________________________
        class Histogram
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            static const unsigned Bins = 256; //!< alias
            typedef size_t        freq_t;     //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Histogram() noexcept; //!< setup
            virtual ~Histogram() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void ldz() noexcept; //!< reset
            freq_t operator[](const uint8_t) const noexcept; //!< \return byte frequency

            void operator()(const uint8_t);            //!< increase byte frequency
            void merge(const freq_t * const) noexcept; //!< merge bytes frequency from local cache
            void save(OutputStream &)           const; //!< save to output, mostly to debug

            friend bool operator==(const Histogram &, const Histogram &) noexcept; //!< \return true iff same histograms
            friend bool operator!=(const Histogram &, const Histogram &) noexcept; //!< \return true iff different histograms
            
            const freq_t total;     //!< total bytes
        private:
            freq_t       bin[Bins];               //!< individual bins
            Y_Disable_Copy_And_Assign(Histogram); //!< discarded

        };

    }

}

#endif // !Y_Ink_Histogram_Included

