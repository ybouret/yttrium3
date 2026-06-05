//! file

#ifndef Y_Field_Sketch_Included
#define Y_Field_Sketch_Included 1

#include "y/object/counted.hpp"

namespace Yttrium
{

    namespace Field
    {
        //______________________________________________________________________
        //
        //
        //
        //! base class for layouts
        //
        //
        //______________________________________________________________________
        class Sketch : public CountedObject
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definition
            //
            //__________________________________________________________________
            static const void * const Zeroed; //!< holds zeroed V4D<size_t>

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Sketch() noexcept; //!< setup
            virtual ~Sketch() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! setup metrics
            /**
             \param width computed width per dimension
             \param lower (fixed) lower coordinates
             \param upper (fixed) upper coordinates
             \param shift partial products
             \param dims  dimensions
             \return number of items
             */
            static size_t Setup(size_t *       width,
                                unit_t * const lower,
                                unit_t * const upper,
                                size_t * const shift,
                                const unsigned dims) noexcept;


        private:
            Y_Disable_Copy_And_Assign(Sketch); //!< discarded
        };
    }

}

#endif // !Y_Field_Sketch_Included

