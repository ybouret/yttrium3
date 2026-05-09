
#include "y/coven/tribes.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/ascii/convert.hpp"

using namespace Yttrium;

namespace
{
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


    template <typename T> static inline
    apn TestTribes(const Matrix<T>  & mu,
                   const unsigned    strategy,
                   Coven::VCache   & vc,
                   Coven::RCache   & rc,
                   XML::Log        & xml,
                   Coven::Vectors  & vlist)
    {
        Coven::Tribes tribes(mu,vc,rc,OnVec,&vlist);
        tribes.toXML(xml);
        apn num = tribes->size;
        while(true)
        {
            const size_t gen = tribes.generate(mu,strategy,OnVec,&vlist);
            tribes.toXML(xml);
            if(gen<=0) break;
            num += gen;
        }
        vlist.sort(Coven::Vector::Cmp);
        {
            Y_XML_Element_Attr(xml, Vectors, Y_XML_Attr(vlist.size) );
            for(const Coven::Vector *node=vlist.head;node;node=node->next)
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
                mu[i][j] = ran.in<int>(-2,2);
        std::cerr << "mu=" << mu << std::endl;

        Coven::Vectors  vec0;
        const apn       num0 = TestTribes(mu,0x00,vc,rc,xml,vec0);
        std::cerr << "#generated=" << num0 << "/ #vectors=" << vec0.size << std::endl;


        Coven::Vectors vec1;
        const apn num1 = TestTribes(mu,Coven::Tribes::NoMultiple,vc,rc,xml,vec1);
        std::cerr << "#generated=" << num1 << "/ #vectors=" << vec1.size << std::endl;
        

    }


}
Y_UDONE()
