
#include "y/mkl/algebra/lu.hpp"
#include "y/mkl/algebra/ortho-space.hpp"
#include "y/apex/rational.hpp"

namespace Yttrium
{
    namespace MKL
    {

        bool OrthoSpace::Compute(Matrix<apz> &Q, const Matrix<apz> &P)
        {
            const size_t n = P.rows; if(n<=0) { Q.release(); return false;}
            const size_t m = P.cols; if(n>=m) { Q.release(); return false;}

            Matrix<apz> P2(n,n); P2.gram(P);
            LU<apq>     lu(n);
            const apz   dP2 =     lu.determinant(P2); if(dP2.is0()) { Q.release(); return false;}
            Matrix<apz> aP2(n,n); lu.adjoint(aP2,P2);

            Q.make(m,m);
            {
                Matrix<apz>       P3(n,m);P3.mmul(aP2,P);
                const Matrix<apz> PT(TransposeOf,P);
                Q.mmul(PT,P3);
            }

            for(size_t i=m;i>0;--i)
            {
                Q[i][i] = dP2 - Q[i][i];
                for(size_t j=m;j>i;--j)   Sign::MakeOpposite( Coerce(Q[i][i].s) );
                for(size_t j=i-1;j>0;--j) Sign::MakeOpposite( Coerce(Q[i][i].s) );
            }
            
            return true;
        }
    }

}

