
#include "y/ink/bitmap.hpp"
#include "y/utest/run.hpp"
#include "y/type/destruct.hpp"

using namespace Yttrium;

namespace
{
    template <typename T>
    struct TIO
    {
        static inline void Ctor(void *p)          { new (p) T(); }
        static inline void Dtor(void *p) noexcept { Destruct( static_cast<T *>(p) ); }

    };
}

Y_UTEST(bitmap)
{
    Ink::Bitmap bmp(32,16,4,TIO<int32_t>::Ctor,TIO<int32_t>::Dtor);
}
Y_UDONE()
