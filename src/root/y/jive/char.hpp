//! \file

#ifndef Y_Jive_Char_Included
#define Y_Jive_Char_Included 1

#include "y/jive/spot.hpp"
#include "y/object/light.hpp"


namespace Yttrium
{
    namespace Jive
    {

        class Char : public LightObject, public Spot
        {
        public:
            explicit Char(const Spot &, const uint8_t) noexcept;
            Char(const Char &) noexcept;
            virtual ~Char() noexcept;

            uint8_t       & operator*() noexcept;
            const uint8_t & operator*() const noexcept;

        private:
            Y_Disable_Assign(Char);
            uint8_t data;
        public:
            Char * next;
            Char * prev;
        };
    }

}


#endif // !Y_Jive_Char_Included
