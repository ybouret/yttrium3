#include "y/string/core.hpp"
#include "y/object/light.hpp"
#include "y/string/stride.hpp"
#include "y/swap.hpp"
#include "y/stream/output.hpp"
#include "y/stream/input.hpp"

namespace Yttrium
{

    namespace Core
    {

        template <typename T>
        class String<T>:: Code : public LightObject, public Stride<T>
        {
        public:
            typedef Stride<T> StrideType;

            inline virtual ~Code() noexcept
            {

            }


            inline explicit Code(const Code &code) :
            LightObject(), StrideType(code)
            {

            }

            inline explicit Code(const size_t n) :
            LightObject(), StrideType(n)
            {

            }

            inline explicit Code(const T * const text) :
            LightObject(), StrideType(text)
            {

            }


            inline explicit Code(const T * const buffer,
                                 const size_t    buflen) :
            LightObject(), StrideType(buffer,buflen)
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
