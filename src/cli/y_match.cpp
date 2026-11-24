#include "y/system/program.hpp"
#include "y/jive/pattern/matching.hpp"
#include "y/stream/libc/input.hpp"
#include "y/pointer/auto.hpp"
#include "y/format/decimal.hpp"

using namespace Yttrium;

Y_PROGRAM()
{
    if(argc<=2)
    {
        std::cout << "usage: " << program << " [exactly|somehow] expression [filename]" << std::endl;
        return 1;
    }

    // find request
    const String            manner  = argv[1];
    Jive::Matching::Request request = Jive::Matching::Exactly;
    if(manner=="exactly")
    {
    }
    else
    {
        if(manner=="somehow")
        {
            request = Jive::Matching::Somehow;
        }
        else
        {
            std::cerr << "unknow manner '" << manner << "'" << std::endl;
            return 2;
        }
    }

    // compile expression
    Jive::Matching       matching = argv[2];
    AutoPtr<InputStream> input = (argc>3) ? new InputFile(argv[3]) : new InputFile(StdIn);
    String               line;
    size_t               iline=0;
    while(input->gets(line))
    {
        const String name = *(input->title) + ':' + Decimal(++iline).c_str();
        if( matching(request,Jive::Module::OpenData(name,line)) )
        {
            std::cout << line << std::endl;
        }
    }




}
Y_EXECUTE()
