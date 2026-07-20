
//! \file

#ifndef Y_Ink_Bitmap_Included
#define Y_Ink_Bitmap_Included 1

#include "y/ink/area.hpp"
#include "y/ink/zero-flux.hpp"

namespace Yttrium
{
    namespace Ink
    {

        //______________________________________________________________________
        //
        //
        //
        //! light-weight row prototype
        //
        //
        //______________________________________________________________________
        class Bitrow
        {
        public:
            Bitrow(void * const, const ZeroFlux &) noexcept; //!< setup
            void * const   p; //!< address of first item
            const ZeroFlux f; //!< zero flux

        private:
            Y_Disable_Copy_And_Assign(Bitrow); //!< discarded
            ~Bitrow() noexcept;                //!< discarded
        };

        //______________________________________________________________________
        //
        //
        //
        //! Anonymous bitmap
        //
        //
        //______________________________________________________________________
        class Bitmap : public Area
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            class Code;
            typedef void (*Proc)(void*); //!< alias for ctor/dtor

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            /**
             \param W width
             \param H height
             \param D depth
             \param ctor pixel constructor
             \param dtor pixel destructor
             */
            explicit Bitmap(const unit_t   W,
                            const unit_t   H,
                            const unsigned D,
                            Proc const     ctor,
                            Proc const     dtor);
            Bitmap(const Bitmap &);     //!< shared copy of code, new rows
            virtual ~Bitmap() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const unsigned d;   //!< depth
            const unit_t   s;   //!< stride
            const ZeroFlux zfx; //!< zero x-flux
            const ZeroFlux zfy; //!< zero y-flux

        private:
            Y_Disable_Assign(Bitmap); //!< discarded
            Code   * const code;      //!< shared code
            const size_t   rlen;      //!< bytes for rows
        protected:
            Bitrow * const row_;      //!< rows

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
        private:
            void releaseCode() noexcept;
            void acquireRows();
            void releaseRows() noexcept;
			Bitmap & self_()   noexcept;
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
        };

    }

}

#endif // !Y_Ink_Bitmap_Included

