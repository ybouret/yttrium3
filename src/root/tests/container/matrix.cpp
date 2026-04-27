#include "y/container/matrix.hpp"
#include "y/utest/run.hpp"
#include "y/apex/rational.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

namespace
{
    static size_t maxDim = 6;

    template <typename T> static inline
    void testMatrix(Core::Rand &ran)
    {
        for(size_t r=0;r<=maxDim;++r)
        {
            for(size_t c=0;c<=maxDim;++c)
            {
                if( (r==0 && c>0) || (r>0 && c==0) ) continue;

                std::cerr << "-- rows=" << r << ", cols=" << c << std::endl;
                Matrix<T> m(r,c);

                for(size_t i=1;i<=r;++i)
                {
                    for(size_t j=1;j<=c;++j)
                    {
                        m[i][j] = ran.in<int>(-10,10);
                    }
                }

                std::cerr << m << std::endl;

                {
                    const Matrix<T> mm(m);
                    std::cerr << mm << std::endl;
                }

                {
                    const Matrix<apq> mm(CopyOf,m);
                    std::cerr << mm << std::endl;
                }

                {
                    const Matrix<T> mm(TransposeOf,m);
                    std::cerr << mm << std::endl;
                }

                {
                    Matrix<T> mm(r,c); mm.assign(m);
                    std::cerr << mm << std::endl;
                }

                {
                    Matrix<apq> mm(c,r); mm.assignTranspose(m);
                    std::cerr << mm << std::endl;
                }

                if(r>0)
                {
                    m.swapRows( ran.in<size_t>(1,r), ran.in<size_t>(1,r) );
                    m.swapCols( ran.in<size_t>(1,c), ran.in<size_t>(1,c) );

                }

            }
        }

    }
}

Y_UTEST(container_matrix)
{
    Core::Rand ran;

    Y_SIZEOF( MatrixRow<int> );
    Y_SIZEOF( MatrixRow<apq> );

    testMatrix<int>(ran);
    testMatrix<apz>(ran);

}
Y_UDONE()


