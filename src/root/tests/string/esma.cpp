
#include "y/stream/libc/input.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

#include <cstdio>

namespace
{

#define XSIZE 256
#define OUTPUT(X) printf("%d\n",(X))

    void preKmp(const char * const x, int m, int kmpNext[]) {
        int i, j;

        i = 0;
        j = kmpNext[0] = -1;
        while (i < m) {
            while (j > -1 && x[i] != x[j])
                j = kmpNext[j];
            i++;
            j++;
            if (x[i] == x[j])
                kmpNext[i] = kmpNext[j];
            else
                kmpNext[i] = j;
        }
    }


    void KMP(const char * const x, const int m,
             const char * const y, const int n) {
        int i, j, kmpNext[XSIZE];

        std::cerr << "KMP: " << std::endl;
        /* Preprocessing */
        preKmp(x, m, kmpNext);

        /* Searching */
        i = j = 0;
        while (j < n) {
            while (i > -1 && x[i] != y[j])
                i = kmpNext[i];
            i++;
            j++;
            if (i >= m) {
                OUTPUT(j - i);
                i = kmpNext[i];
            }
        }
    }

}

Y_UTEST(string_esma)
{
    if(argc>1)
    {
        const String       motif = argv[1];
        const char * const x     = motif.c_str();
        const int          m     = (int)motif.size();

        if(argc>2)
        {
            InputFile fp(argv[2]);
            String    line;
            while( fp.gets(line) )
            {
                const char * const y = line.c_str();
                const int          n = (int)line.size();
                if(n>=m)
                    KMP(x,m,y,n);
            }
        }
    }
}
Y_UDONE()
