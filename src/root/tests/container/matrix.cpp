#include "y/container/matrix.hpp"
#include "y/utest/run.hpp"
#include "y/apex/rational.hpp"

using namespace Yttrium;

namespace
{
    static size_t maxDim = 4;

    template <typename T> static inline
    void testMatrix()
    {
        for(size_t r=0;r<=maxDim;++r)
        {
            for(size_t c=0;c<=maxDim;++c)
            {
                if( (r==0 && c>0) || (r>0 && c==0) ) continue;

                std::cerr << "-- rows=" << r << ", cols=" << c << std::endl;
                Matrix<T> m(r,c);

                std::cerr << m << std::endl;
            }
        }

    }
}

Y_UTEST(container_matrix)
{
    Y_SIZEOF( MatrixRow<int> );
    Y_SIZEOF( MatrixRow<apq> );

    testMatrix<int>();

}
Y_UDONE()


