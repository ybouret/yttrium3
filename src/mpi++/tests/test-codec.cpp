#include "y/mpi++/codecs.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{
    template <typename T>
    static inline void show(const char * const Type)
    {
        typedef MPI_Codec_Select<T> CS;
        Y_PRINTV(Type);
        Y_PRINTV(CS::IsLegacyScalar);
        Y_PRINTV(CS::IsLegacyVector) ;
        Y_PRINTV(CS::IsSerializable);
        std::cerr << std::endl;
    }

#define SHOW(TYPE) show<TYPE>( #TYPE )

}

Y_UTEST(codec)
{
    SHOW(int);
    SHOW(XReal<float>);
    SHOW(String);
    SHOW(Complex<long double>);
    SHOW(V3D<int32_t>);
    
}
Y_UDONE()

