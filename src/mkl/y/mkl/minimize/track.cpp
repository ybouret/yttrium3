#include "y/mkl/minimize/track.hpp"
#include "y/core/clamp.hpp"
#include "y/mkl/xreal.hpp"
#include "y/mkl/api/almost-equal.hpp"
#include "y/mkl/api/half.hpp"
#include "y/object.hpp"
#include "y/type/destroy.hpp"
#include "y/cameo/addition.hpp"
#include "y/core/hsort.hpp"
#include "y/stream/libc/output.hpp"

#include <iomanip>

namespace Yttrium
{
    namespace MKL
    {
        template <typename T> class MinTrack<T>:: Code : public Object
        {
        public:
            static const size_t NMAX = 8;

            inline explicit Code() :
            Object(),
            zero(0),
            one(1),
            nn(0),
            xx(),
            ff(),
            verbose(true)
            {

            }

            inline virtual ~Code() noexcept
            {
            }


            inline T step(Triplet<T>    &x,
                          Triplet<T>    &f,
                          Function<T,T> &F)
            {

                /*      */ assert(x.isOrdered());    assert(f.isLocalMinimum());
                x.sort(f); assert(x.isIncreasing()); assert(f.isLocalMinimum());
                if(verbose) std::cerr << "-- ini: " << x << " => " << f << std::endl;
                {
                    OutputFile fp("mintrack.data");
                    const unsigned np = 1000;
                    for(unsigned i=0;i<=np;++i)
                    {
                        const T  w = ( (double)i )/np;
                        const T  X = x.a * (one-w) + x.c * w;
                        fp("%.15g %.15g\n", (double) X, (double) F(X));
                    }
                }

                // load initial
                ld(x,f);

                // probe
                {
                    const T lw = Max(x.b-x.a,zero);
                    const T rw = Max(x.c-x.b,zero);
                    switch( Sign::Of(lw,rw) )
                    {
                        case Negative: assert(lw<rw); sample(F, Half<T>::Of(x.b,x.c) ); break;
                        case Positive: assert(rw<lw); sample(F, Half<T>::Of(x.a,x.b) ); break;
                        case __Zero__:
                            sample(F, Half<T>::Of(x.a,x.b) );
                            sample(F, Half<T>::Of(x.b,x.c) );
                            break;
                    }
                }

                // extract new triplet
                extract(x,f);

                switch( Sign::Of(f.a,f.c) )
                {
                    case __Zero__: break;
                    case Negative: assert(f.a<f.c); break;
                    case Positive: assert(f.c<f.a); break;
                }

                return x.c-x.a;
            }

            const T zero;
            const T one;
            size_t  nn;
            T       xx[NMAX];
            T       ff[NMAX];
            bool    verbose;

        private:
            Y_Disable_Copy_And_Assign(Code);

            inline void ld(const Triplet<T> &x, const Triplet<T> &f) noexcept
            {
                x.save(xx);
                f.save(ff);
                nn = 3;
            }

            inline void sample(Function<T,T> &F, const T xt)
            {
                assert(nn<NMAX);
                ff[nn] = F(xx[nn]=xt);
                if(verbose) std::cerr << "-- add " << xx[nn] << " => " << ff[nn] << std::endl;
                ++nn;
            }

            inline void extract(Triplet<T> &x, Triplet<T> &f) noexcept
            {
                assert(nn>3);
                // sort
                Core::HSort::Make(xx,nn,Sign::Increasing<T>,ff);

                // search
                const size_t top = nn-1;
                size_t       im = 0;
                T            fm = ff[0];
                for(size_t it=1;it<=top;++it)
                {
                    const T ft = ff[it];
                    if(ft<fm)
                    {
                        fm = ft;
                        im = it;
                    }
                }

                if(0==im)
                {
                    x.a = x.b = xx[0]; x.c = xx[1];
                    f.a = f.b = ff[0]; f.c = ff[1];
                    assert(x.isIncreasing());
                    assert(f.isLocalMinimum());
                }
                else
                {
                    if(top==im)
                    {
                        const size_t prv = top-1;
                        x.a = xx[prv]; x.b = x.c = xx[top];
                        f.a = ff[prv]; f.b = f.c = ff[top];
                        assert(x.isIncreasing());
                        assert(f.isLocalMinimum());
                    }
                    else
                    {
                        const size_t ia = im-1;
                        x.load(xx+ia);
                        f.load(ff+ia);
                        assert(x.isIncreasing());
                        assert(f.isLocalMinimum());
                    }
                }

                {
                    OutputFile fp("min-step.data");
                    for(size_t i=1;i<=3;++i)
                    {
                        fp("%.15g %.15g\n", (double) x[i], (double) f[i]);
                    }
                    fp("%.15g %.15g\n", (double) x[1], (double) f[1]);
                }

            }

        };


#define real_t float
#include "track.hxx"
#undef real_t

#define real_t double
#include "track.hxx"
#undef real_t

#define real_t long double
#include "track.hxx"
#undef real_t

#define real_t XReal<float>
#include "track.hxx"
#undef real_t

#define real_t XReal<double>
#include "track.hxx"
#undef real_t

#define real_t XReal<long double>
#include "track.hxx"
#undef real_t

    }

}


