#include "y/string/core.hpp"
#include "y/object/light.hpp"
#include "y/string/stride.hpp"

namespace Yttrium
{

    namespace Core
    {

        template <typename T>
        class String<T>:: Code : public LightObject, public Stride<T>
        {
        public:
            static const size_t _0 = 0;

            inline virtual ~Code() noexcept {}

            inline explicit Code() : LightObject(), Stride<T>(_0) {}

            inline explicit Code(const Code &code) :
            LightObject(), Stride<T>(code)
            {

            }


        private:
            Y_Disable_Assign(Code);
        };

#undef  CH

        
#define CH char
#include "core.hxx"
#undef  CH

#define CH uint32_t
#include "core.hxx"
#undef  CH

    }



}
