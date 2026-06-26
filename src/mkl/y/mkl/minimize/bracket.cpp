
#include "y/mkl/minimize/bracket.hpp"
#include "y/core/clamp.hpp"
#include "y/mkl/xreal.hpp"
#include "y/mkl/api/almost-equal.hpp"
#include "y/mkl/api/half.hpp"
#include "y/object.hpp"
#include "y/xml/element.hpp"

#include <iomanip>

namespace Yttrium
{
    namespace MKL
    {


#define real_t float
#include "bracket.hxx"
#undef real_t

#define real_t double
#include "bracket.hxx"
#undef real_t

#define real_t long double
#include "bracket.hxx"
#undef real_t

#define real_t XReal<float>
#include "bracket.hxx"
#undef real_t

#define real_t XReal<double>
#include "bracket.hxx"
#undef real_t

#define real_t XReal<long double>
#include "bracket.hxx"
#undef real_t

    }

}


