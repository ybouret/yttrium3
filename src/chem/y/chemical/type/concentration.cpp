#include "y/chemical/type/concentration.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        xreal_t   Concentration:: Get(Random::Uniform32 &ran,
                                      const real_t       probaZ,
                                      const real_t       probaN) noexcept
        {
            static const double minLog10 = MinLog10;
            static const double maxLog10 = MaxLog10;

            if( ran() <= probaZ ) return 0.0;
            const double r = ran();
            const double p = minLog10 + r * (maxLog10 - minLog10);
            //std::cerr << "r=" << r << ",p=" << p << std::endl;
            const double c = pow(10.0,p);
            return ( ran() <= probaN ? -c : c);
        }

        void Concentration:: Fill(Random::Uniform32 &ran,
                                  XWritable &C,
                                  const size_t M,
                                  const real_t probaZ,
                                  const real_t probaN) noexcept
        {
            for(size_t i=M;i>0;--i) C[i] = Get(ran,probaZ,probaN);
        }



    }

}
