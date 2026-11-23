#include "y/mkl/fit/variables.hpp"
#include "y/utest/run.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/container/matrix.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            //__________________________________________________________________
            //
            //
            //
            //! SampleMetrics
            //
            //
            //__________________________________________________________________
            class SampleMetrics : public String
            {
            public:
                template <typename NAME> inline
                explicit SampleMetrics(const NAME &name) :
                String(name),
                vars()
                {
                }

                virtual ~SampleMetrics() noexcept;


                virtual size_t cardinal()  const noexcept = 0;
                virtual void   save(OutputStream &) const = 0;

                void           checkSize() const;
                void           autoSave() const;
                Variables      vars;

            private:
                Y_Disable_Copy_And_Assign(SampleMetrics);

            };

        }

    }

}


#include "y/stream/libc/output.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            void SampleMetrics:: checkSize() const
            {
                if( size() <= 0 ) throw Specific::Exception(c_str(),"empty sample");
            }

            SampleMetrics:: ~SampleMetrics() noexcept
            {
            }

            void SampleMetrics:: autoSave() const
            {
                const String fileName = *this + ".dat";
                OutputFile   fp(fileName);
                save(fp);
            }


        }

    }

}


namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            template <typename ABSCISSA, typename ORDINATE>
            class Function
            {
            public:

                inline explicit Function() noexcept {}
                inline virtual ~Function() noexcept {}

                virtual ORDINATE start(const ABSCISSA &, const Variables &, const Readable<ABSCISSA> &) = 0;
                virtual ORDINATE value(const ABSCISSA &, const Variables &, const Readable<ABSCISSA> &) = 0;

            private:
                Y_Disable_Copy_And_Assign(Function);
            };

            template <typename ABSCISSA, typename ORDINATE>
            class OrdinaryFunction : public Function<ABSCISSA,ORDINATE>
            {
            public:

                inline explicit OrdinaryFunction() noexcept {}
                inline virtual ~OrdinaryFunction() noexcept {}

                inline virtual ORDINATE start(const ABSCISSA &x, const Variables &vars, const Readable<ABSCISSA> &aorg)
                {
                    return get(x,vars,aorg);
                }

                inline virtual ORDINATE value(const ABSCISSA &x, const Variables &vars, const Readable<ABSCISSA> &aorg)
                {
                    return get(x,vars,aorg);
                }

                inline ORDINATE operator()(const ABSCISSA x, const Variables &vars, const Readable<ABSCISSA> &aorg)
                {
                    return get(x,vars,aorg);
                }

            private:
                Y_Disable_Copy_And_Assign(OrdinaryFunction);
                virtual ORDINATE get(const ABSCISSA &, const Variables &, const Readable<ABSCISSA> &) = 0;
            };

        }

    }
}

#include "y/stream/output.hpp"
#include "y/format/decimal.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {
            template <typename ABSCISSA, typename ORDINATE>
            struct WriteXY
            {
                static const size_t DIMENSIONS = sizeof(ORDINATE)/sizeof(ABSCISSA);

                static inline void Emit(OutputStream &fp, const ORDINATE &y)
                {
                    const ABSCISSA * const p = (const ABSCISSA *) &y;
                    for(size_t i=0;i<DIMENSIONS;++i)
                        fp(" %.15g", (double) p[i]);
                }


                static inline void To(OutputStream   &fp,
                                                const ABSCISSA &x,
                                                const ORDINATE &y,
                                                const ORDINATE &yf,
                                                const size_t    tag)
                {
                    fp("%.15g",(double)x);
                    Emit(fp,y);
                    Emit(fp,yf);
                    if(tag)
                        fp(" %s",Decimal(tag).c_str());
                    fp << '\n';
                }

            };


        }

    }

}


#include "y/cameo/addition.hpp"
#include "y/mkl/api/mod2.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            template <typename ABSCISSA, typename ORDINATE>
            class Sample : public SampleMetrics
            {
            public:
                typedef Function<ABSCISSA,ORDINATE>  FunctionType;
                typedef Cameo::Addition<ABSCISSA>    AdditionType;
                typedef Keyed<String,ArcPtr<Sample>> Pointer;

                template <typename NAME> inline
                explicit Sample(const NAME &name) :
                SampleMetrics(name),
                xadd()
                {

                }

                inline virtual ~Sample() noexcept {}


                virtual void collectD2(AdditionType             &sumD2,
                                       FunctionType             &F,
                                       const Readable<ABSCISSA> &aorg) = 0;


                inline ABSCISSA D2(FunctionType &F, const Readable<ABSCISSA> &aorg)
                {
                    xadd.ldz();
                    collectD2(xadd,F,aorg);
                    return xadd();
                }

                AdditionType xadd;

            private:
                Y_Disable_Copy_And_Assign(Sample);

            protected:
                inline ABSCISSA collect(const ORDINATE &lhs, const ORDINATE &rhs)
                {
                    const ORDINATE delta = lhs-rhs;
                    return Mod2<ORDINATE>(delta);
                }
            };

        }

    }

}

#include "y/container/cxx/light-array.hpp"
#include "y/container/cxx/array.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            template <typename ABSCISSA, typename ORDINATE>
            class DataSample : public Sample<ABSCISSA,ORDINATE>
            {
            public:
                typedef Sample<ABSCISSA,ORDINATE>          SampleType;
                typedef typename SampleType::FunctionType  FunctionType;
                typedef typename SampleType::AdditionType  AdditionType;

                using SampleType::checkSize;
                using SampleType::vars;

                template <typename NAME> inline
                explicit DataSample(const NAME &           name,
                                    const ABSCISSA * const xa,
                                    const ORDINATE * const ya,
                                    const size_t           na) :
                SampleType(name),
                x( (ABSCISSA *) xa, na ),
                y( (ORDINATE *) ya, na ),
                yf(na),
                tag(0)
                {
                    checkSize();
                }

                inline virtual ~DataSample() noexcept {}

                inline virtual size_t cardinal() const noexcept
                {
                    assert( x.size() == y.size() );
                    assert( x.size() == yf.size() );
                    return x.size();
                }

                virtual void save(OutputStream &fp) const
                {
                    const size_t n = cardinal();
                    for(size_t i=1;i<=n;++i)
                        WriteXY<ABSCISSA,ORDINATE>::To(fp,x[i], y[i], yf[i], tag);
                }

                const LightArray<ABSCISSA> x;
                const LightArray<ORDINATE> y;
                CxxArray<ORDINATE>         yf;
                const size_t               tag;

            private:
                Y_Disable_Copy_And_Assign(DataSample);

                inline virtual void collectD2(AdditionType             & sumD2,
                                              FunctionType             & F,
                                              const Readable<ABSCISSA> & aorg)
                {
                    const size_t n = cardinal(); assert(n>0);
                    sumD2 << this->collect(y[1],yf[1] = F.start(x[1],vars,aorg));
                    for(size_t i=2;i<=n;++i)
                        sumD2 << this->collect(y[i],yf[i] = F.value(x[i],vars,aorg));
                }


            };




        }

    }
}


namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {
            template <typename ABSCISSA, typename ORDINATE>
            class Samples :
            public Sample<ABSCISSA,ORDINATE>,
            public Proxy< SuffixSet<String, typename Sample<ABSCISSA,ORDINATE>::Pointer > >
            {
            public:
                typedef Sample<ABSCISSA,ORDINATE>          SampleType;
                typedef typename SampleType::Pointer       SamplePointer;
                typedef typename SampleType::FunctionType  FunctionType;
                typedef typename SampleType::AdditionType  AdditionType;

                typedef SuffixSet<String,SamplePointer>    SampleDB;
                typedef typename SampleDB::Iterator        Iterator;
                typedef typename SampleDB::ConstIterator   ConstIterator;
                typedef DataSample<ABSCISSA,ORDINATE>      DataSampleType;

                using SampleType::vars;

                template <typename NAME>
                inline explicit Samples(const NAME &name) :
                SampleType(name),
                Proxy<SampleDB>(),
                db()
                {
                }


                inline virtual ~Samples() noexcept {}


                virtual size_t cardinal() const noexcept
                {
                    size_t ns = 0;
                    for(ConstIterator it=db.begin();it != db.end();++it)
                    {
                        ns += (**it).cardinal();
                    }
                    return ns;
                }

                inline virtual void save(OutputStream &fp) const
                {
                    for(ConstIterator it=db.begin();it != db.end();++it)
                    {
                        (**it).save(fp);
                        fp << '\n';
                    }
                }


                template <typename NAME>
                inline SampleType & operator()(const NAME &           name,
                                               const ABSCISSA * const xa,
                                               const ORDINATE * const ya,
                                               const size_t           na)
                {
                    DataSampleType * const ds   = new DataSampleType(name,xa,ya,na);
                    {
                        SamplePointer sp   = ds;
                        if(!db.insert(sp)) throw Specific::Exception(this->c_str(),"multiple '%s'", sp->c_str());
                    }
                    Coerce(ds->tag) = db.size();
                    return *ds;
                }


            private:
                Y_Disable_Copy_And_Assign(Samples);
                SampleDB db;

                inline virtual const SampleDB & locus() const noexcept { return db; }

                inline virtual void collectD2(AdditionType             &sumD2,
                                              FunctionType             &F,
                                              const Readable<ABSCISSA> &aorg)
                {
                    for(Iterator it=db.begin();it != db.end();++it)
                    {
                        (**it).collectD2(sumD2,F,aorg);
                    }

                }
            };

        }

    }

}



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

