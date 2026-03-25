#include "y/xml/log.hpp"
#include "y/xml/element.hpp"

#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{

    static inline void TestXML(XML::Log &xml)
    {

        const int value = 7;
        XML::Element elem(xml,"elem");
        elem << Y_XML_Attr(xml.verbose);
        elem.end();
        XML::Element sub(xml,"sub");
        sub.end();
        {
            XML::Element mark(xml,"mark",true);
            mark << Y_XML_Attr(value);
            mark.end();
        }


    }

}

Y_UTEST(xml)
{
    bool     verbose = true;
    XML::Log xml(std::cerr,verbose);


    TestXML(xml);
    xml.verbose = false; Y_ASSERT(false == verbose);
    TestXML(xml);
    
}
Y_UDONE()

