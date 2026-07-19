
//! \file

#ifndef Y_Ink_Pixmap_Included
#define Y_Ink_Pixmap_Included 1

#include "y/ink/bitmap.hpp"
#include "y/ink/broker.hpp"
#include "y/type/destruct.hpp"
#include "y/check/static.hpp"
#include "y/hide.hpp"

namespace Yttrium
{
    namespace Ink
    {

        template <typename T>
        class Pixmap : public Bitmap
        {
        public:
            Y_Args_Declare(T,Type);
            class Row
            {
                private: Type * const   p;
                public:  const ZeroFlux f;

                inline Type & operator[](const unit_t i) noexcept {
                    return p[ f[i] ];
                }

                inline ConstType & operator[](const unit_t i) const noexcept {
                    return p[ f[i] ];
                }

                inline Type & operator()(const unit_t i) noexcept {
                    assert(i>=0); assert(i<f.count); return p[i];
                }

                inline ConstType & operator()(const unit_t i) const noexcept {
                    assert(i>=0); assert(i<f.count); return p[i];
                }


            private:
                Y_Disable_Copy_And_Assign(Row);
                Row() noexcept;
                ~Row() noexcept;
            };

            inline explicit Pixmap(const unit_t W, const unit_t H) :
            Bitmap(W,H,sizeof(T), CTor, DTor),
            row( Hide::Cast<Row>(row_) )
            {
                Y_STATIC_CHECK(sizeof(Row)==sizeof(Bitrow),BadRowSize);
            }


            inline virtual ~Pixmap() noexcept
            {
            }

            inline Pixmap(const Pixmap &pxm) noexcept :
            Bitmap(pxm),
            row( Hide::Cast<Row>(row_) )
            {
            }


            inline Row & operator[](const unit_t j) noexcept
            {
                return row[ zfy[j] ];
            }

            inline const Row & operator[](const unit_t j) const noexcept
            {
                return row[ zfy[j] ];
            }

            inline Row & operator()(const unit_t j) noexcept
            {
                assert(j>=0); assert(j<h); return row[j];
            }

            inline const Row & operator()(const unit_t j) const noexcept
            {
                assert(j>=0); assert(j<h); return row[j];
            }

        private:
            Y_Disable_Assign(Pixmap);
            Row * const row;

            static inline void CTor(void *addr) {
                assert(addr);
                new (addr) MutableType();
            }

            static inline void DTor(void *addr) noexcept
            {
                assert(addr);
                Destruct( static_cast<MutableType *>(addr) );
            }

        };
    }

}

#endif // !Y_Ink_Pixmap_Included

