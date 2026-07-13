
#include "y/mkl/algebra/xgj.hpp"
#include "y/core/min.hpp"

namespace Yttrium
{
    namespace MKL
    {


        apq XGJ::FindPivot(size_t            &ip,
                           const Matrix<apq> &a,
                           const size_t       i)
        {
            const size_t n  = a.rows;
            apq          pv = a[i][i];
            apq          pa = pv.abs();
            ip = i;
            for(size_t ii=i+1;ii<=n;++ii)
            {
                const apq tmp_v = a[ii][i];
                const apq tmp_a = tmp_v.abs();
                if(tmp_a>pa)
                {
                    pv  = tmp_v;
                    pa  = tmp_a;
                    ip  = ii;
                }
            }
            return pv;
        }


        size_t XGJ:: Build(Matrix<apq> &a, Matrix<apq> &b)
        {
            assert(a.rows==b.rows);
            const size_t n = a.rows; if(n<=0) return 0;
            const size_t c = a.cols; assert(c>0);
            const size_t l = b.cols; assert(l>0);
            const size_t m = Min(n,c);

            for(size_t i=1;i<=m;++i)
            {
                size_t    ip = 0;
                const apq pv = FindPivot(ip,a,i);
                if(pv.is0()) return i-1;

                if(ip!=i)
                {
                    std::cerr << "swap(" << i << "," << ip << ")" << std::endl;
                    a.swapRows(i,ip);
                    b.swapRows(i,ip);
                }

                assert(pv==a[i][i]);
                const size_t i1=i+1;
                for(size_t k=i1;k<=n;++k)
                {
                    Writable<apq> & a_k = a[k];
                    const apq       fac = a_k[i]/pv;
                    Writable<apq> & b_k = b[k];
                    a_k[i].ldz();
                    for(size_t j=i1;j<=c;++j) a_k[j] -= fac * a[i][j];
                    for(size_t j=l;j>0;--j)   b_k[j] -= fac * b[i][j];
                }
            }

            return m;
        }

    }
}


