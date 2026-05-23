#include "y/coven/compress.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

Y_UTEST(coven_compress)
{
    Core::Rand    ran;

    Matrix<int>   nu(4,3);

    {
        for(size_t i=1;i<=nu.rows;++i)
        {
            for(size_t j=1;j<=nu.cols;++j)
            {
                nu[i][j] = ran.in<int>(-1,1);
            }
        }
    }

    Matrix<apz> out;

    std::cerr << "nu=" << nu << std::endl;

    {
        if(Coven::Compress(out,nu,Coven::CompressDuplicate))
        {
            std::cerr << "dup=" << out << std::endl;
        }
        else
        {
            std::cerr << "no data..." << std::endl;
        }
    }


    {
        if(Coven::Compress(out,nu,Coven::CompressTranspose))
        {
            std::cerr << "trn=" << out << std::endl;
        }
        else
        {
            std::cerr << "no data..." << std::endl;
        }
    }





}
Y_UDONE()
