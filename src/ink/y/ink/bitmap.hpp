
//! \file

#ifndef Y_Ink_Bitmap_Included
#define Y_Ink_Bitmap_Included 1

#include "y/ink/area.hpp"

namespace Yttrium
{
    namespace Ink
    {


    
        class Bitmap : public Area
        {
        public:
            class Code;
            typedef void (*Proc)(void*);
            class Row
            {
            public:
                Row(void * const, const unit_t) noexcept;

                void * const p;
                const unit_t w;

            private:
                Y_Disable_Copy_And_Assign(Row);
                ~Row() noexcept;
            };

            explicit Bitmap(const unit_t   W,
                            const unit_t   H,
                            const unsigned D,
                            Proc const     ctor,
                            Proc const     dtor);
            Bitmap(const Bitmap &);
            virtual ~Bitmap() noexcept;

            const unsigned d; //!< depth
            const unit_t   s; //!< stride

        private:
            Y_Disable_Assign(Bitmap);
            Code   * const code;
            const size_t   rlen;
            Row * const    row_;

            void releaseCode() noexcept;
            void acquireRows();
            void releaseRows() noexcept;
        };

    }

}

#endif // !Y_Ink_Bitmap_Included

