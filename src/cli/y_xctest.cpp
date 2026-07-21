

#include "y/stream/libc/input.hpp"
#include "y/system/program.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/string/tokenizer.hpp"
#include "y/core/hsort.hpp"
#include "y/container/algorithm/replace.hpp"

using namespace Yttrium;

Y_PROGRAM()
{
    if(argc<=1)
    {
        std::cerr << "usage: " << program << " ctest.out" << std::endl;
        return 1;
    }

    Vector<String> ctest;

    {
        InputFile fp(argv[1]);
        String line;
        Vector<String> words;
        while( fp.gets(line) )
        {
            words.free();
            Tokenizer::AppendTo(words,line, " \t");
            if(3==words.size() && "Test" == words[1])
                ctest << words[3];
        }
    }
    Core::HSort::Increasing( ctest(), ctest.size() );
    {
        const char source = ':';
        const char target = '_';
        for(size_t i=1;i<=ctest.size();++i)
        {
            Algorithm::Replace(ctest[i],source,target);
            std::cout << ctest[i] << "\t #" << i << std::endl;
        }
    }
    std::cerr << "#ctest=" << ctest.size() << std::endl;


}
Y_EXECUTE()
