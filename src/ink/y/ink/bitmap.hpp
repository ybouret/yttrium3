
//! \file

#ifndef Y_Ink_Bitmap_Included
#define Y_Ink_Bitmap_Included 1

#include "y/ink/area.hpp"
#include "y/ink/zero-flux.hpp"

namespace Yttrium
{
    namespace Ink
    {

        class Bitrow
        {
        public:
            Bitrow(void * const, const ZeroFlux &) noexcept;
            void * const   p;
            const ZeroFlux f;

        private:
            Y_Disable_Copy_And_Assign(Bitrow);
            ~Bitrow() noexcept;
        };

        class Bitmap : public Area
        {
        public:
            class Code;
            typedef void (*Proc)(void*);


            explicit Bitmap(const unit_t   W,
                            const unit_t   H,
                            const unsigned D,
                            Proc const     ctor,
                            Proc const     dtor);
            Bitmap(const Bitmap &);
            virtual ~Bitmap() noexcept;

            const unsigned d;   //!< depth
            const unit_t   s;   //!< stride
            const ZeroFlux zfx; //!< zero x-flux
            const ZeroFlux zfy; //!< zero y-flux

        private:
            Y_Disable_Assign(Bitmap);
            Code   * const code;
            const size_t   rlen;
        protected:
            Bitrow * const row_;

        private:
            void releaseCode() noexcept;
            void acquireRows();
            void releaseRows() noexcept;
        };

    }

}

#endif // !Y_Ink_Bitmap_Included

