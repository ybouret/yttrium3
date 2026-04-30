
//! \file

#ifndef Y_Apex_KegDFT_Included
#define Y_Apex_KegDFT_Included 1

#include "y/apex/k/keg.hpp"
#include "y/core/max.hpp"
#include "y/memory/allocator/archon.hpp"
#include "y/dft/dft.hpp"
#include "y/exception.hpp"

#if defined(Y_Apex_Trace)
#include "y/system/wall-time.hpp"
#endif

namespace Yttrium
{
    namespace Apex
    {

        struct KegDFT
        {
            static uint64_t Trace;


            template <typename WORD> static inline
            Keg<WORD> * Compute(const Keg<WORD> &lhs,
                                const Keg<WORD> &rhs)
            {
                static Memory::Archon  &archon = Memory::Archon::Instance();
                const size_t n = lhs.bytes;
                const size_t m = rhs.bytes; if(n<=0||m<=0) return new Keg<WORD>();
                const size_t mn = Max(m,n);
                size_t       nn = 1;
                unsigned     ns = 0;
                while (nn < mn)
                {
                    nn <<= 1; ++ns; assert( size_t(1) << ns == nn);
                }
                const size_t nc = nn; // number of complexes
                nn <<= 1; ++ns;       // number of reals

                assert( size_t(1) << ns == nn);

                const unsigned blockShift = ns+1+IntegerLog2For<double>::Value; std::cerr << "nn=" << nn << " => 2^" << blockShift << " = " << (1<<blockShift) << std::endl;
                double * const blockEntry = static_cast<double *>( archon.acquireBlock(blockShift) );
                double * const a          = blockEntry-1;
                double * const b          = a+nn;

                //CxxArray<double> a(nn);
                //CxxArray<double> b(nn);
                for(size_t i=n;i>0;--i) a[i] = lhs.getByte(n-i);
                for(size_t i=m;i>0;--i) b[i] = rhs.getByte(m-i);

                Core::Display(std::cerr << "a=",a+1,nn) << std::endl;
                Core::Display(std::cerr << "b=",b+1,nn) << std::endl;


                DFT::RealForward(a,b,nn);

                b[1] *= a[1];
                b[2] *= a[2];
                {
                    Complex<double> * zb = (Complex<double> *) b+1;
                    Complex<double> * za = (Complex<double> *) a+1;
                    for(size_t i=nc-1;i>0;--i)
                    {
                        *(++zb) *= *(++za);
                    }
                }

                DFT::RealReverse(b,nn);
                double              cy  = 0;
                static const double RX  = 256.0;
                Core::Display(std::cerr << "p=",b+1,nn) << std::endl;

                for(size_t j=nn;j>0;--j) {
                    const double t = floor( b[j]/(double)nc+cy+0.5 );
                    cy=(unsigned long) (t*0.00390625);
                    *(uint8_t *)&b[j]= (uint8_t)(t-cy*RX);
                }

                if (cy >= RX) {
                    throw Exception("cannot happen in DFT Multiplication");
                }

#if 0
                w[1]=(uint8_t) cy;
                for(size_t j=2;j<=n+m;++j)
                    w[j] = *(const uint8_t *) &b[j-1];
#endif
                
                archon.releaseBlock(blockEntry,blockShift);

                return 0;
            }
        };

    }

}

#endif // !Y_Apex_KegDFT_Included

