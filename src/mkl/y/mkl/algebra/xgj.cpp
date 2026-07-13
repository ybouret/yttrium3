
#include "y/mkl/algebra/xgj.hpp"

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


        size_t XGJ:: Build(Matrix<apq> &a)
        {
            const size_t n = a.rows; if(n<=0) return 0;
            const size_t c = a.cols; assert(c>0);

            std::cerr << "a=" << a << std::endl;
            for(size_t i=1;i<=n;++i)
            {
                size_t    ip = 0;
                const apq pv = FindPivot(ip,a,i);
                std::cerr << "pivot=" << pv << " @" << ip << "/" << i << std::endl;
                if(pv.is0()) return i-1;

                if(ip!=i)
                {
                    a.swapRows(i,ip);
                }
                assert(pv==a[i][i]);
                std::cerr << "a[" << i << "]=" << a[i] << std::endl;
                const size_t i1=i+1;
                for(size_t k=i1;k<=n;++k)
                {
                    const apq fac = a[k][i]/pv;
                    a[k][i].ldz();
                    for(size_t j=i1;j<=c;++j)
                    {
                        a[k][j] -= fac * a[i][j];
                    }
                    std::cerr << "a[" << k << "]=" << a[k] << std::endl;
                }
            }

            return n;
        }

    }
}


