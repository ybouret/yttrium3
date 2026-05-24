
#include "y/coven/tribes.hpp"
#include "y/coven/survey/standard.hpp"

#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/ascii/convert.hpp"

using namespace Yttrium;

namespace
{
#if 0
    static inline void OnVec(const Coven::Vector &v, void * const args)
    {
        //std::cerr << "[+] " << v << std::endl;
        assert(args);
        Coven::Vectors  & vlist = *static_cast<Coven::Vectors *>(args);
        bool              found = false;
        for(const Coven::Vector *node=vlist.head;node;node=node->next)
        {
            if( *node == v ) {
                found = true;
                break;
            }
        }
        if(!found)
            vlist.pushTail( new Coven::Vector(v) );
    }
#endif

    template <typename T> static inline
    apn TestTribes(const Matrix<T>  & mu,
                   const unsigned    strategy,
                   Coven::VCache   & vc,
                   Coven::RCache   & rc,
                   XML::Log        & xml,
                   Coven::Survey   & survey)
    {
        Coven::Tribes tribes(mu,strategy,vc,rc,Coven::Survey::Callback,&survey);
        tribes.toXML(xml);


        apn num = tribes->size;
         while(true)
        {
            const size_t gen = tribes.generate(mu,strategy,Coven::Survey::Callback,&survey);
            tribes.toXML(xml);
            if(gen<=0) break;
            num += gen;
        }

        {
            const size_t approved = survey->size;
            const size_t sampling = survey.sampling;
            Y_XML_Element_Attr(xml,Survey, Y_XML_Attr(approved) << Y_XML_Attr(sampling) );
            for(const Coven::Vector *node=survey->head;node;node=node->next)
            {
                Y_XMLog(xml,*node);
            }
        }
        return num;
    }

}

#include "y/string/env.hpp"

namespace
{
    static inline void Print(const apn           & num,
                             const Coven::Survey & vec)
    {
        std::cerr
        << "#generated="   << std::setw(8) << num
        << "/ #vectors="   << std::setw(8) << vec->size
        << " / #sampling=" << std::setw(8) << vec.sampling << std::endl;
    }
}

Y_UTEST(coven_tribes)
{
    //Coven::Survey::Trace = true;
    Core::Rand    ran;
    bool          verbose = Environment::Flag("VERBOSE");
    XML::Log      xml(std::cerr,verbose);

    const size_t  nr = argc>1 ? ASCII::Convert::To<size_t>(argv[1],"nr",0) : 5;
    const size_t  nc = argc>2 ? ASCII::Convert::To<size_t>(argv[2],"nc",0) : 4;
    const int     va = argc>3 ? ASCII::Convert::To<int>(argv[3],"va",0) : 1;

    Coven::RCache rc;
    {
        Matrix<int>     mu(nr,nc);
        Coven::Metrics  metrics(nc);
        Coven::VCache   vc(metrics);

        for(size_t i=1;i<=nr;++i)
            for(size_t j=1;j<=nc;++j)
                mu[i][j] = ran.in<int>(-va,va);
        std::cerr << "mu=" << mu << std::endl;

        const apn maxGenerated = Coven::Tribes::MaxGenerated(nr);
        Y_PRINTV(maxGenerated);
        (std::cerr << "-- all generated : ").flush();

        Coven::StandardSurvey vec0(1);
        const apn             num0 = TestTribes(mu,
                                                0x00,
                                                vc,rc,xml,vec0);
        Print(num0,vec0);

        (std::cerr << "-- use NoMultiple: ").flush();
        Coven::StandardSurvey vec1(1);
        const apn             num1 = TestTribes(mu,
                                                Coven::Tribes::NoMultiple,
                                                vc,rc,xml,vec1);
        Print(num1,vec1);
        Y_ASSERT(vec1==vec0);


        (std::cerr << "-- use Precompile: ").flush();
        Coven::StandardSurvey vec2(1);
        const apn             num2 = TestTribes(mu,
                                                Coven::Tribes::Precompile,
                                                vc,rc,xml,vec2);
        Print(num2,vec2);
        Y_ASSERT(vec2==vec0);

        (std::cerr << "-- use NoColinear: ").flush();
        Coven::StandardSurvey vec3(1);
        const apn             num3 = TestTribes(mu,
                                                Coven::Tribes::NoColinear,
                                                vc,rc,xml,vec3);
        Print(num3,vec3);
        Y_ASSERT(vec3==vec0);


        (std::cerr << "-- use HyperPlane: ").flush();
        Coven::StandardSurvey vec4(1);
        const apn             num4 = TestTribes(mu,
                                                Coven::Tribes::HyperPlane,
                                                vc,rc,xml,vec4);
        Print(num4,vec4);
        Y_ASSERT(vec4==vec0);


        (std::cerr << "-- use Optimizing: ").flush();

        Coven::StandardSurvey vec5(1);
        const apn             num5 = TestTribes(mu,
                                                Coven::Tribes::Optimizing,
                                                vc,rc,xml,vec5);
        Print(num5,vec5);
        Y_ASSERT(vec5==vec0);
        vec0.print(std::cerr);
        std::cerr << "-- done" << std::endl;
    }


}
Y_UDONE()
