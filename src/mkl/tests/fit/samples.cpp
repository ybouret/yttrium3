#include "y/mkl/fit/least-squares.hpp"
#include "y/mkl/fit/samples.hpp"
#include "y/utest/run.hpp"





using namespace Yttrium;
using namespace MKL;

namespace
{
    static const double _t1[]    = { 30,80,140,200,270,320,430,550,640,720,830,890 };
    static const double _x1[]    = { 4.414520,5.011710,5.632319,6.194379,6.721311,7.330211,8.009368,8.735363,9.297424,9.707260,10.339578,10.878220};
    static const size_t _n1      = sizeof(_t1)/sizeof(_t1[0]);

    static const double _t2[]    = { 60,120,200,270,360,460,580,670,790,920,1040 };
    static const double _x2[]    = { 5.199063,5.854801,6.662763,7.365340,8.067916,8.782201,9.578454,10.175644,10.878220,11.651054,12.213115};
    static const size_t _n2      = sizeof(_t2)/sizeof(_t2[0]);
}

namespace
{
    class Diffusion : public Fit::OrdinaryFunction<double,double>
    {
    public:

        inline explicit Diffusion()
        {
        }

        inline virtual ~Diffusion() noexcept
        {
        }

    private:
        Y_Disable_Copy_And_Assign(Diffusion);

        virtual double get(const double &t, const Fit::Variables &vars, const Readable<double> &aorg)
        {
            const double t0 = vars["t0"][aorg];
            const double D  = vars["D"][aorg];
            if(t<=t0)
                return 0;
            else
                return sqrt(D*(t-t0));
        }
    };

    class DiffusionGradient : public Fit::OrdinaryGradient<double,double>
    {
    public:
        inline explicit DiffusionGradient()
        {
        }

        inline virtual ~DiffusionGradient() noexcept
        {
        }
        
    private:
        Y_Disable_Copy_And_Assign(DiffusionGradient);

        virtual double get(Writable<double> &dFda,
                           const double &t,
                           const Fit::Variables &vars,
                           const Readable<double> &aorg,
                           const Readable<bool> &used)
        {
            const Fit::Variable &_t0 = vars["t0"];
            const Fit::Variable &_D  = vars["D"];
            const double t0 = _t0[aorg];
            const double D  = _D[aorg];
            if(t<=t0)
            {
                return 0;
            }
            else
            {
                const double dt = t-t0;
                const double f  = sqrt(D*dt);
                if( _t0[used] ) _t0[dFda] = 0.5 * dt/f;
                if( _D[used]  ) _D[dFda]  = 0.5 * D/f;
                return f;
            }
        }

    };

}

Y_UTEST(fit_samples)
{

    Fit::Samples<double,double> SA("samples");
    Fit::Sample<double,double> &S1 = SA("s1",_t1,_x1,_n1);
    Fit::Sample<double,double> &S2 = SA("s2",_t2,_x2,_n2);

    const Fit::Variable & t0 = SA.vars("t0");
    const Fit::Variable & D1 = SA.vars("D1");
    const Fit::Variable & D2 = SA.vars("D2");

    const size_t nvar = SA.vars.span;

    Y_PRINTV(SA.vars);
    Y_PRINTV(nvar);

    S1.vars(t0);
    S1.vars("D",D1);
    Y_PRINTV(S1.vars);
    Y_PRINTV(S1.cardinal());

    S2.vars(t0);
    S2.vars("D",D2);
    Y_PRINTV(S2.vars);
    Y_PRINTV(S2.cardinal());
    Y_PRINTV(SA.cardinal());

    CxxArray<double> aorg(nvar);
    SA.vars["t0"][aorg] = -100;
    SA.vars["D1"][aorg] = 0.15;
    SA.vars["D2"][aorg] = 0.20;

    Diffusion          F;
    DiffusionGradient  G;

    Fit::LeastSquares<double,double> fit;

    const double S1D2 = fit.D2(S1,F,aorg);
    const double S2D2 = fit.D2(S2,F,aorg);
    const double SAD2 = fit.D2(SA,F,aorg);

    Y_PRINTV(S1D2);
    Y_PRINTV(S2D2);
    Y_PRINTV(SAD2);

    std::cerr << std::endl;
    std::cerr << std::endl;
    CxxArray<bool> used(nvar,true);

    const double S1D2full = fit.D2full(S1, G, aorg, used);
    Y_PRINTV(S1D2full);
    Y_PRINTV(fit.beta);
    Y_PRINTV(fit.alpha);

    std::cerr << std::endl;
    const double S2D2full = fit.D2full(S2, G, aorg, used);
    Y_PRINTV(S2D2full);
    Y_PRINTV(fit.beta);
    Y_PRINTV(fit.alpha);

    std::cerr << std::endl;
    const double SAD2full = fit.D2full(SA, G, aorg, used);
    Y_PRINTV(SAD2full);
    Y_PRINTV(fit.beta);
    Y_PRINTV(fit.alpha);
    std::cerr << std::endl;

    if(false)
    {
        Y_PRINTV( Fit::LeastSquaresCore<float>::PMIN );
        Y_PRINTV( Fit::LeastSquaresCore<float>::PMAX );
        std::cerr << std::endl;

        Y_PRINTV( Fit::LeastSquaresCore<double>::PMIN );
        Y_PRINTV( Fit::LeastSquaresCore<double>::PMAX );
        std::cerr << std::endl;

        Y_PRINTV( Fit::LeastSquaresCore<long double>::PMIN );
        Y_PRINTV( Fit::LeastSquaresCore<long double>::PMAX );
        std::cerr << std::endl;

        Y_PRINTV( Fit::LeastSquaresCore< XReal<float> >::PMIN );
        Y_PRINTV( Fit::LeastSquaresCore< XReal<float> >::PMAX );
        std::cerr << std::endl;

        Y_PRINTV( Fit::LeastSquaresCore<XReal<double>>::PMIN );
        Y_PRINTV( Fit::LeastSquaresCore<XReal<double>>::PMAX );
        std::cerr << std::endl;

        Y_PRINTV( Fit::LeastSquaresCore< XReal<long double> >::PMIN );
        Y_PRINTV( Fit::LeastSquaresCore< XReal<long double> >::PMAX );
        std::cerr << std::endl;
    }

    {
        Fit::LeastSquaresCore<float> f;
        Y_PRINTV(*f.pLambda);
    }

}
Y_UDONE()

