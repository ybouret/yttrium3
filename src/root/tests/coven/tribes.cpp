
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

Y_UTEST(coven_tribes)
{
    Core::Rand    ran;
    bool          verbose = Environment::Flag("VERBOSE");
    XML::Log      xml(std::cerr,verbose);

    const size_t  nr = argc>1 ? ASCII::Convert::To<size_t>(argv[1],"nr",0) : 5;
    const size_t  nc = argc>2 ? ASCII::Convert::To<size_t>(argv[2],"nc",0) : 4;
    Coven::RCache rc;
    {
        Matrix<int>     mu(nr,nc);
        Coven::Metrics  metrics(nc);
        Coven::VCache   vc(metrics);

        for(size_t i=1;i<=nr;++i)
            for(size_t j=1;j<=nc;++j)
                mu[i][j] = ran.in<int>(-1,1);
        std::cerr << "mu=" << mu << std::endl;

        const apn maxGenerated = Coven::Tribes::MaxGenerated(nr);
        Y_PRINTV(maxGenerated);
        std::cerr << "-- full generation" << std::endl;
        Coven::StandardSurvey vec0;
        const apn             num0 = TestTribes(mu,
                                                0x00,
                                                vc,rc,xml,vec0);
        std::cerr << "#generated=" << num0 << "/ #vectors=" << vec0->size << " / #sampling=" << vec0.sampling << std::endl;


        std::cerr << "-- use NoMultiple" << std::endl;
        Coven::StandardSurvey vec1;
        const apn             num1 = TestTribes(mu,
                                                Coven::Tribes::NoMultiple,
                                                vc,rc,xml,vec1);
        std::cerr << "#generated=" << num1 << "/ #vectors=" << vec1->size << " / #sampling=" << vec1.sampling << std::endl;
        Y_CHECK(vec1==vec0);


        std::cerr << "-- use Precompile" << std::endl;
        Coven::StandardSurvey vec2;
        const apn             num2 = TestTribes(mu,
                                                Coven::Tribes::Precompile,
                                                vc,rc,xml,vec2);
        std::cerr << "#generated=" << num2 << "/ #vectors=" << vec2->size << " / #sampling=" << vec2.sampling << std::endl;
        Y_CHECK(vec2==vec0);

        std::cerr << "-- use RunTimeGTZ" << std::endl;
        Coven::StandardSurvey vec3;
        const apn             num3 = TestTribes(mu,
                                                Coven::Tribes::RunTimeGTZ,
                                                vc,rc,xml,vec3);
        std::cerr << "#generated=" << num3 << "/ #vectors=" << vec3->size << " / #sampling=" << vec3.sampling << std::endl;
        Y_CHECK(vec3==vec0);

#if 1
        std::cerr << "-- use NoColinear" << std::endl;
        Coven::StandardSurvey vec4;
        const apn             num4 = TestTribes(mu,
                                                Coven::Tribes::NoColinear,
                                                vc,rc,xml,vec4);
        std::cerr << "#generated=" << num4 << "/ #vectors=" << vec4->size << " / #sampling=" << vec4.sampling << std::endl;
        Y_CHECK(vec4==vec0);
#endif
        
        Y_PRINTV(maxGenerated);
    }


}
Y_UDONE()
