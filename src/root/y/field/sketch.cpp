
#include "y/field/sketch.hpp"
#include "y/swap.hpp"
#include <cassert>

namespace Yttrium
{

    namespace Field
    {
        static const size_t SketchZeroed[4] = { 0,0,0,0 };
        const void * const Sketch:: Zeroed = &SketchZeroed[0];

        Sketch::  Sketch() noexcept {}
        Sketch:: ~Sketch() noexcept {}

        size_t Sketch:: Setup(size_t *       width,
                              unit_t * const lower,
                              unit_t * const upper,
                              size_t * const shift,
                              const unsigned dims) noexcept
        {
            static const unit_t _1 = 1;
            assert(dims>0);
            assert(width);
            assert(lower),
            assert(upper);
            assert(shift);
            size_t prod = 1;
            for(size_t i=0;i<dims;++i)
            {
                unit_t &lo = lower[i];
                unit_t &hi = upper[i];
                if(hi<lo) Swap(lo,hi);
                prod *= ( width[i] = (size_t)(_1+hi-lo) );
                shift[i] = prod;
            }
            return prod;
        }
    }

}
