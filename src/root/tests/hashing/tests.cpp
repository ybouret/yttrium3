#include "y/hashing/sha1.hpp"
#include "y/hashing/md5.hpp"
#include "y/hashing/pjw.hpp"
#include "y/hashing/rmd160.hpp"
#include "y/hashing/sha256.hpp"

#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(hashing_tests)
{
    Hashing::SHA1::Tests();
    Hashing::MD5::Tests();
    Hashing::PJW::Tests();
    Hashing::RMD160::Tests();
    Hashing::SHA224::Tests();
    Hashing::SHA256::Tests();

}
Y_UDONE()
