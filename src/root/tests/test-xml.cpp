#include "y/stream/xmlog.hpp"

#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{

    static inline void TestXML(XML::Log &xml)
    {

        const int value = 7;
        Y_XML_Element_Attr(xml,top,Y_XML_Attr(xml.verbose) << Y_XML_Attr(value));
        Y_XMLog(xml, "message in " << top.tag);
        Y_XML_Element(xml,sub);
        Y_XMLog(xml, "message in " << sub.tag);
        Y_XML_Standalone(xml,mark, Y_XML_Attr(value));
        Y_XMLog(xml, "message in " << sub.tag);

    }

}

Y_UTEST(xml)
{
    bool     verbose = true;
    XML::Log xml(std::cerr,verbose);


    std::cerr << "-- verbose" << std::endl;
    TestXML(xml);
    xml.verbose = false; Y_ASSERT(false == verbose);

    std::cerr << "--quiet" << std::endl;
    TestXML(xml);
    
}
Y_UDONE()

