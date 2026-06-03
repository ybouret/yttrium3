//! file

#ifndef Y_Field_Sketch_Included
#define Y_Field_Sketch_Included 1

#include "y/object/counted.hpp"

namespace Yttrium
{

    namespace Field
    {
        class Sketch : public CountedObject
        {
        public:
            static const void * const Zeroed;
            explicit Sketch() noexcept;
            virtual ~Sketch() noexcept;

            static size_t Setup(size_t *       width,
                                unit_t * const lower,
                                unit_t * const upper,
                                const unsigned dims) noexcept;


        private:
            Y_Disable_Copy_And_Assign(Sketch);
        };
    }

}

#endif // !Y_Field_Sketch_Included

