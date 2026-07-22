
//! \file

#ifndef Y_Apex_KegDFT_Included
#define Y_Apex_KegDFT_Included 1

#include "y/apex/k/keg.hpp"
#include "y/core/max.hpp"
#include "y/dft/dft.hpp"
#include "y/exception.hpp"
#include "y/pointer/auto.hpp"



#include "y/memory/allocator/archon.hpp"


#if defined(Y_Apex_Trace)
#include "y/system/wall-time.hpp"
#endif

#include <cmath>

namespace Yttrium
{
    namespace Apex
    {

        typedef Memory::Archon DFT_Allocator; //!< alias
        
        template <typename T> struct Transfer;
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
        template <> struct Transfer<uint32_t>
        {
            static inline void Send(double * a, const uint32_t * word, const size_t words) noexcept
            {
                word += words;
                for(size_t i=words;i>0;--i)
                {
                    uint32_t w = *(--word);
                    *(++a) = (uint8_t)(w>>24);
                    *(++a) = (uint8_t)(w>>16);
                    *(++a) = (uint8_t)(w>>8);
                    *(++a) = (uint8_t)(w);
                }
            }

            static inline void Recv(uint32_t * word,  const uint8_t *w, const size_t mpn) noexcept
            {
                unsigned choice = 0;
                w += mpn;
                for(size_t k=mpn;k>0;--k)
                {
                    const uint32_t b = *(--w);
                    switch(choice)
                    {
                        case 0: *word      = b;         choice = 1; continue;
                        case 1: *word     |= (b << 8);  choice = 2; continue;
                        case 2: *word     |= (b << 16); choice = 3; continue;
                        case 3: *(word++) |= (b << 24); choice = 0; continue;
                    }
                }
            }
        };


        template <> struct Transfer<uint16_t>
        {
            static inline void Send(double * a, const uint16_t * word, const size_t words) noexcept
            {
                word += words;
                for(size_t i=words;i>0;--i)
                {
                    uint16_t w = *(--word);
                    *(++a) = (uint8_t)(w>>8);
                    *(++a) = (uint8_t)(w);
                }
            }

            static inline void Recv(uint16_t * word, const uint8_t *w, const size_t mpn) noexcept
            {
                unsigned choice = 0;
                w += mpn;
                for(size_t k=mpn;k>0;--k)
                {
                    const uint16_t b = *(--w);
                    switch(choice)
                    {
                        case 0: *word      = b;        choice = 1; continue;
                        case 1: *(word++) |= (b << 8); choice = 0; continue;
                    }
                }
            }

            
        };


        template <> struct Transfer<uint8_t>
        {
            static inline void Send(double * a, const uint8_t * word, const size_t words) noexcept
            {
                for(size_t i=words;i>0;--i) a[i] = *(word++);
            }

            static inline void Recv(uint8_t * word, const uint8_t *w, const size_t mpn) noexcept
            {
                word += mpn;
                for(size_t i=mpn;i>0;--i)
                {
                    *(--word) = *(w++);
                }
            }

        };



#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        //______________________________________________________________________
        //
        //
        //
        //! using Fourier Multiplication
        //
        //
        //______________________________________________________________________
        struct KegDFT
        {
            static uint64_t       Trace;                //!< to trace call ticks
            static const char     AlgebraicFailure[];  //!< "Algebraic Failure"


            //! compute lhs * rhs by Fourier transform
            /**
             \param  lhs first argument
             \param  rhs second argument
             \return lhs * rhs
             */
            template <typename WORD> static inline
            Keg<WORD> * Compute(const Keg<WORD> &lhs,
                                const Keg<WORD> &rhs)
            {
                static DFT_Allocator &mgr = DFT_Allocator::Instance();

                //--------------------------------------------------------------
                //
                // Check lengths
                //
                //--------------------------------------------------------------
                const size_t n = lhs.bytes;
                const size_t m = rhs.bytes; if(n<=0||m<=0) return new Keg<WORD>();

#if defined(Y_Apex_Trace)
                uint64_t mark = System::WallTime::Ticks();
#endif
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
#if defined(Y_Apex_Trace)
                Trace += System::WallTime::Ticks() - mark;
#endif
                AutoPtr< Keg<WORD> >  dft = new Keg<WORD>(mpn);

                //--------------------------------------------------------------
                //
                // Allocate enough memory
                //
                //--------------------------------------------------------------
                const unsigned blockShift = ns+1+IntegerLog2For<double>::Value;
                void   * const blockEntry = mgr.acquireBlock(blockShift);
                assert( (size_t(1) << blockShift) >= 2*nn*sizeof(double) );


                {
#if defined(Y_Apex_Trace)
                    mark = System::WallTime::Ticks();
#endif
                    double *  const a = static_cast<double *>(blockEntry)-1; // a[1:nn]
                    double *  const b = a+nn;                                // b[1:nn]
                    uint8_t * const w = static_cast<uint8_t*>(blockEntry);   // w[0:..] to use result memory



#define Y_APEX_DFT_RAW_SEND 1

#if defined(Y_APEX_DFT_RAW_SEND)
                    for(size_t i=n,j=0;i>0;--i) a[i] = lhs.getByte(j++);
                    for(size_t i=m,j=0;i>0;--i) b[i] = rhs.getByte(j++);
#else
                    Transfer<WORD>::Send(a,lhs.word,lhs.words);
                    Transfer<WORD>::Send(b,rhs.word,rhs.words);
#endif


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
                        throw Specific::Exception("DFT::Multiplication","%s",AlgebraicFailure);

                    

                    Coerce(dft->words) = Alignment::To<WORD>::Ceil(mpn) / sizeof(WORD);
                    assert(dft->words*sizeof(WORD)>=mpn);

//#define Y_APEX_DFT_RAW_RECV 1
#if defined(Y_APEX_DFT_RAW_RECV)
                    {
                        size_t top = mpn-1;
                        dft->or_(top, (uint8_t) cy);
                        for(size_t j=1;j<mpn;++j)
                            dft->or_(--top,w[j]);
                    }
#else
                    {
                        w[0] = (uint8_t)cy;
                        Transfer<WORD>::Recv(dft->word,w,mpn);
                    }
#endif
                    dft->update();

                }

#if defined(Y_Apex_Trace)
                Trace += System::WallTime::Ticks() - mark;
#endif
                mgr.releaseBlock(blockEntry,blockShift);

                return dft.yield();
            }

            //! square in place \param z replaced by z^2
            template <typename T>
            static inline void InSituSquared(T &z) noexcept
            {
                z *= z;
            }

            //! compute arg^2 by Fourier transform
            /**
             \param  arg   argument
             \return arg^2
             */
            template <typename WORD> static inline
            Keg<WORD> * Square(const Keg<WORD> &arg)
            {
                static DFT_Allocator  &mgr = DFT_Allocator::Instance();

                const size_t n  = arg.bytes; if(n<=0) return new Keg<WORD>();
                size_t       nn = 1;
                unsigned     ns = 0;
                while (nn < n)
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
                const size_t          mpn = n<<1; assert(mpn>=2);
                AutoPtr< Keg<WORD> >  dft = new Keg<WORD>(mpn);

                //--------------------------------------------------------------
                //
                // Allocate enough memory
                //
                //--------------------------------------------------------------
                const unsigned blockShift = ns+1+IntegerLog2For<double>::Value;
                void   * const blockEntry = mgr.acquireBlock(blockShift);
                {
                    double * const  b = (static_cast<double *>(blockEntry)-1)+nn; // b[1:nn]
                    uint8_t * const w = static_cast<uint8_t*>(blockEntry);        // w[0:..] to use result memory

                    //#define Y_APEX_DFT_RAW_SEND 1
#if defined(Y_APEX_DFT_RAW_SEND)
                    for(size_t i=n,j=0;i>0;--i) b[i] = arg.getByte(j++);
#else
                    Transfer<WORD>::Send(b,arg.word,arg.words);
#endif

                    DFT::RealForward(b,nn);


                    b[1] *= b[1];
                    b[2] *= b[2];
                    {
                        Complex<double> * zb = (Complex<double> *) &b[1];
                        for(size_t i=nc-1;i>0;--i)
                            InSituSquared( *(++zb) );
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
                        throw Specific::Exception("DFT::Square","%s",AlgebraicFailure);

                    Coerce(dft->words) = Alignment::To<WORD>::Ceil(mpn) / sizeof(WORD);
                    assert(dft->words*sizeof(WORD)>=mpn);

                    //#define Y_APEX_DFT_RAW_RECV 1
#if defined(Y_APEX_DFT_RAW_RECV)
                    {
                        size_t top = mpn-1;
                        dft->or_(top, (uint8_t) cy);
                        for(size_t j=1;j<mpn;++j)
                            dft->or_(--top,w[j]);
                    }
#else
                    {
                        w[0] = (uint8_t)cy;
                        Transfer<WORD>::Recv(dft->word,w,mpn);
                    }
#endif
                    dft->update();

                }

                mgr.releaseBlock(blockEntry,blockShift);
                return dft.yield();

            }


        };


    }

}

#endif // !Y_Apex_KegDFT_Included

