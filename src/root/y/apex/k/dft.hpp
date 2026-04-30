
//! \file

#ifndef Y_Apex_KegDFT_Included
#define Y_Apex_KegDFT_Included 1

#include "y/apex/k/keg.hpp"
#include "y/core/max.hpp"
#include "y/memory/allocator/archon.hpp"
#include "y/dft/dft.hpp"
#include "y/exception.hpp"
#include "y/pointer/auto.hpp"

#if defined(Y_Apex_Trace)
#include "y/system/wall-time.hpp"
#endif

#include <cmath>

namespace Yttrium
{
    namespace Apex
    {

        //! using Fourier Multiplication
        struct KegDFT
        {
            static uint64_t Trace; //!< to trace call ticks




            //! compute lhs * rhs by fourier transform
            /**
             \param lhs first argument
             \param rhs second argument
             \return lhs * rhs
             */
            template <typename WORD> static inline
            Keg<WORD> * Compute(const Keg<WORD> &lhs,
                                const Keg<WORD> &rhs)
            {
                static Memory::Archon  &archon = Memory::Archon::Instance();

                //--------------------------------------------------------------
                //
                // Check lengths
                //
                //--------------------------------------------------------------
                const size_t n = lhs.bytes;
                const size_t m = rhs.bytes; if(n<=0||m<=0) return new Keg<WORD>();

                //--------------------------------------------------------------
                //
                // Compute minimal common size
                //
                //--------------------------------------------------------------
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

                //--------------------------------------------------------------
                //
                // Allocate result
                //
                //--------------------------------------------------------------
                const size_t          mpn = m+n; assert(mpn>=2);
                AutoPtr< Keg<WORD> >  dft = new Keg<WORD>(mpn);

                //--------------------------------------------------------------
                //
                // Allocate enough memory
                //
                //--------------------------------------------------------------
                const unsigned blockShift = ns+1+IntegerLog2For<double>::Value;
                void   * const blockEntry = archon.acquireBlock(blockShift);
                {
                    double * const  a = static_cast<double *>(blockEntry)-1; // a[1:nn]
                    double * const  b = a+nn;                                // b[1:nn]
                    uint8_t * const w = static_cast<uint8_t*>(blockEntry)-1; // w[1:nn]

                    for(size_t i=n,j=0;i>0;--i) a[i] = lhs.getByte(j++);
                    for(size_t i=m,j=0;i>0;--i) b[i] = rhs.getByte(j++);


                    DFT::RealForward(a,b,nn);

                    b[1] *= a[1];
                    b[2] *= a[2];
                    {
                        Complex<double> * zb = (Complex<double> *) &b[1];
                        Complex<double> * za = (Complex<double> *) &a[1];
                        for(size_t i=nc-1;i>0;--i)
                        {
                            *(++zb) *= *(++za);
                        }
                    }


                    DFT::RealReverse(b,nn);
                    double              cy  = 0;
                    static const double RX  = 256.0;
                    for(size_t j=nn;j>0;--j) {
                        const double t = floor( b[j]/(double)nc+cy+0.5 );
                        cy=(unsigned long) (t*0.00390625);
                        w[j] = (uint8_t)(t-cy*RX);
                    }
                    if (cy >= RX)
                        throw Exception("cannot happen in DFT Multiplication");
                    
                    {
                        size_t top = mpn-1;
                        Coerce(dft->words) = Alignment::To<WORD>::Ceil(mpn) / sizeof(WORD);
                        dft->or_(top, (uint8_t) cy);
                        for(size_t j=1;j<mpn;++j)
                            dft->or_(--top,w[j]);
                    }
                    dft->update();
                }

                archon.releaseBlock(blockEntry,blockShift);

                return dft.yield();
            }
        };

    }

}

#endif // !Y_Apex_KegDFT_Included

