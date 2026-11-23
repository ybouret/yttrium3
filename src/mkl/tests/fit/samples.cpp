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

    Diffusion F;

    const double S1D2 = S1.D2(F,aorg);
    const double S2D2 = S2.D2(F,aorg);
    const double SAD2 = SA.D2(F,aorg);


    Y_PRINTV(S1D2);
    Y_PRINTV(S2D2);
    Y_PRINTV(SAD2);

    S1.autoSave();
    S2.autoSave();
    SA.autoSave();

}
Y_UDONE()

