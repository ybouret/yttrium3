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
            explicit Char(const Spot &, const char) noexcept;
            Char(const Char &) noexcept;
            virtual ~Char() noexcept;

            char       & operator*() noexcept;
            const char & operator*() const noexcept;

        private:
            Y_Disable_Assign(Char);
            char data;
        public:
            Char * next;
            Char * prev;
        };
    }

}


#endif // !Y_Jive_Char_Included
