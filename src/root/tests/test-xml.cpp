#include "y/xml/log.hpp"
#include "y/xml/attribute.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{

    static inline void TestXML(XML::Log &xml)
    {



    }

}

Y_UTEST(xml)
{
    bool     verbose = true;
    XML::Log xml(std::cerr,verbose);

    std::cerr << Y_XML_Attr(verbose) << std::endl;

    TestXML(xml);
    xml.verbose = false; Y_ASSERT(false == verbose);
    TestXML(xml);
    
}
Y_UDONE()

