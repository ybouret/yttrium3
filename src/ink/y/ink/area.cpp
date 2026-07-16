
#include "y/ink/area.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Ink
    {

        Area:: Area(const Area &a) noexcept :
        w(a.w),
        h(a.h),
        n(a.n),
        xt(a.xt),
        yt(a.yt)
        {
        }


        Area:: ~Area() noexcept
        {

        }

        namespace
        {
            static const char fn[] = "Ink::Area";

            static unit_t CheckW(const unit_t W)
            {
                if(W<=0) throw Specific::Exception(fn, "negative width");
                return W;
            }

            static unit_t CheckH(const unit_t H)
            {
                if(H<=0) throw Specific::Exception(fn, "negative height");
                return H;
            }

        }

        Area:: Area(const unit_t W, const unit_t H) :
        w( CheckW(W) ),
        h( CheckH(H) ),
        n( w*h ),
        xt(w-1),
        yt(h-1)
        {
        }

        Vertex Area:: getUpper() const noexcept
        {
            return Vertex(xt,yt);
        }


    }
}
