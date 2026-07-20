
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
        //______________________________________________________________________
        //
        //
        //
        //! Pixel map
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Pixmap : public Bitmap
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Declare(T,Type); //!< aliases

            //__________________________________________________________________
            //
            //! data row, matching Bitrow
            //__________________________________________________________________
            class Row
            {
                private: Type * const   p; //!< first item address
                public:  const ZeroFlux f; //!< zero-flux

                //! \param i index \return zero-flux item
                inline Type & operator[](const unit_t i) noexcept {
                    return p[ f[i] ];
                }

                //! \param i index \return zero-flux item
                inline ConstType & operator[](const unit_t i) const noexcept {
                    return p[ f[i] ];
                }

                //! \param i index \return direct item
                inline Type & operator()(const unit_t i) noexcept {
                    assert(i>=0); assert(i<f.count); return p[i];
                }

                //! \param i index \return direct item
                inline ConstType & operator()(const unit_t i) const noexcept {
                    assert(i>=0); assert(i<f.count); return p[i];
                }


            private:
                Y_Disable_Copy_And_Assign(Row); //!< discarded
                Row() noexcept;                 //!< discarded
                ~Row() noexcept;                //!< discarded
            };

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup with default type constructor
            /**
             \param W width
             \param H height
             */
            inline explicit Pixmap(const unit_t W, const unit_t H) :
            Bitmap(W,H,sizeof(T), CTor, DTor),
            row( Hide::Cast<Row>(row_) )
            {
                Y_STATIC_CHECK(sizeof(Row)==sizeof(Bitrow),BadRowSize);
            }

            //! cleanup
            inline virtual ~Pixmap() noexcept
            {
            }


            //! shared copy \param pxm source
            inline Pixmap(const Pixmap &pxm) noexcept :
            Bitmap(pxm),
            row( Hide::Cast<Row>(row_) )
            {
            }


            //! hard copy \param broker broker \param pxm source
            template <typename U>
            explicit Pixmap(Broker &broker, const CopyOf_ &, const Pixmap<U> &pxm) :
            Bitmap(pxm.w,pxm.h,sizeof(T), CTor, DTor),
            row( Hide::Cast<Row>(row_) )
            {
                (void)copy(broker,pxm);
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \param j row index \return zero-flux row index
            inline Row & operator[](const unit_t j) noexcept {
                return row[ zfy[j] ];
            }

            //! \param j row index \return zero-flux row index
            inline const Row & operator[](const unit_t j) const noexcept {
                return row[ zfy[j] ];
            }

            //! \param j row index \return direct row index
            inline Row & operator()(const unit_t j) noexcept {
                assert(j>=0); assert(j<h); return row[j];
            }

            //! \param j row index \return direct row index
            inline const Row & operator()(const unit_t j) const noexcept {
                assert(j>=0); assert(j<h); return row[j];
            }

            //! copy \param broker broker \param pxm source \return *this
            template <typename U> inline
            Pixmap<T> & copy(Broker &broker, const Pixmap<U> &pxm)
            {
                assert(gotSameWxH(pxm));
                broker(*this, *this, & Pixmap<T>::copyProc<U>, pxm);
                return *this;
            }


        private:
            Y_Disable_Assign(Pixmap); //!< discarded
            Row * const row;          //!< inner rows

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            static inline void CTor(void *addr) {
                assert(addr);
                new (addr) MutableType();
            }

            static inline void DTor(void *addr) noexcept
            {
                assert(addr);
                Destruct( static_cast<MutableType *>(addr) );
            }

            template <typename U>
            inline void copyProc(const Tile &tile, Pixmap<T> &target, const Pixmap<U> &source)
            {
                assert(this == &target);
                assert(target.gotSameWxH(source));
                for(size_t k=tile.span;k>0;--k)
                {
                    const Segment                   s   = tile[k];
                    const unit_t                    y   = s.start.y;
                    Pixmap<T>::Row                & tgt = target(y);
                    const typename Pixmap<U>::Row & src = source(y);
                    for(unit_t x=s.start.x,i=s.width;i>0;--i,++x)
                    {
                        tgt(x) = src(x);
                    }
                }
            }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)



        };
    }

}

#endif // !Y_Ink_Pixmap_Included

