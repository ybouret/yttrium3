

#include "y/stream/libc/input.hpp"
#include "y/system/program.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/string/tokenizer.hpp"
#include "y/core/hsort.hpp"
#include "y/container/algorithm/replace.hpp"

using namespace Yttrium;

namespace
{
    static inline
    void loadCTest(Vector<String> &ctest, const char * const fileName)
    {
        {
            const char source = ':';
            const char target = '_';
            InputFile fp(fileName);
            String line;
            Vector<String> words;
            while( fp.gets(line) )
            {
                words.free();
                Tokenizer::AppendTo(words,line, " \t");
                if(3==words.size() && words[2].size()>0 && words[2][1] == '#' && "Test" == words[1])
                {
                    ctest << Algorithm::Replace(words[3],source,target);
                }
            }
        }
        Core::HSort::Increasing( ctest(), ctest.size() );
        std::cerr << "#ctest=" << ctest.size() << std::endl;
    }

    static inline
    void loadTest(Vector<String>    & test,
                  const char * const  fileName)
    {
        {
            InputFile      fp(fileName);
            String         line;
            Vector<String> words;
            while( fp.gets(line) )
            {
                words.free();
                Tokenizer::AppendTo(words,line, " \t");
                if(words.size()==2)
                {
                    String &word = words[1];
                    if(word.size()>2 && '[' == word.head() && ']' == word.tail() )
                    {
                        word.popTail();
                        word.popHead();
                        test << word;
                        std::cerr << word << std::endl;
                    }
                }
            }
        }
        Core::HSort::Increasing( test(), test.size() );
        std::cerr << "#test=" << test.size() << std::endl;

    }

    static bool FindIn(const Readable<String> &ctest, const String &id)
    {
        for(size_t i=ctest.size();i>0;--i)
        {
            if(id==ctest[i]) return true;
        }
        return false;
    }

}


Y_PROGRAM()
{
    if(argc<=2)
    {
        std::cerr << "usage: " << program << " ctest.out test.out" << std::endl;
        return 1;
    }

    // load tests from ctest.out
    Vector<String> ctest;
    loadCTest(ctest,argv[1]);

    // load test
    Vector<String> test;
    loadTest(test,argv[2]);

    for(size_t i=1;i<=test.size();++i)
    {
        const String &id = test[i];
        if(!FindIn(ctest,id))
        {
            std::cerr << "Missing '" << id << "'" << std::endl;
        }
    }




}
Y_EXECUTE()
