#include "y/mpi++/carrier/scalar.hpp"
#include "y/mpi++/carrier/vector.hpp"

#include "y/random/type-gen.hpp"

#include "y/utest/run.hpp"
#include <cstring>



using namespace Yttrium;

#include "y/format/hexadecimal.hpp"
#include "y/core/rand.hpp"
#include "y/system/rtti.hpp"

#include "y/check/crc32.hpp"

namespace
{

    template <typename T> static inline
    void testCarrier(MPI              & mpi,
                     Random::CoinFlip & ran,
                     MPI::Carrier     & cr,
                     const bool         chk)
    {

        size_t       items = 5 + ran.toss<size_t>(5);
        mpi.bcastSize(items,0);

        Vector<T>             vec(WithAtLeast,items);

        if(mpi.primary)
        {
            for(size_t i=items;i>0;--i)
            {
                const T tmp  = Random::Gen<T>::Get(ran);
                vec << tmp;
            }
            Y_ASSERT(items==vec.size());
            for(size_t i=1;i<mpi.size;++i)
            {
                cr.send(mpi,vec(),items,i,0x07);
            }
        }
        else
        {

            vec.adjust(items);
            Y_ASSERT(items==vec.size());
            cr.recv(mpi,vec(),items,0,0x07);
        }

        if(chk)
        {
            const uint32_t crc = CRC32::Of( vec(), vec.size() * sizeof(T) );
            Y_MPI_ForEach(mpi, std::cerr << "@" << mpi << ": " << vec << " | " << Hexadecimal(crc) << std::endl);
        }
        else
        {
            Y_MPI_ForEach(mpi, std::cerr << "@" << mpi << ": " << vec << std::endl);
        }
    }


    template <typename T> static inline
    void testSerial(MPI &mpi, Random::CoinFlip &ran)
    {
        Y_MPI_Trace(mpi, std::cerr << std::endl << "testSerial<" << RTTI::Name<T>() << ">" << std::endl);
        MPI::Carrier &cr =  mpi.getSerialCarrier<T>();
        testCarrier<T>(mpi,ran,cr,false);
    }


    template <typename T> static inline
    void testScalar(MPI &mpi, Random::CoinFlip &ran)
    {
        Y_MPI_Trace(mpi, std::cerr << std::endl << "testScalar<" << RTTI::Name<T>() << ">" << std::endl);
        MPI::Carrier & cr = mpi.getScalarCarrier<T>();
        testCarrier<T>(mpi,ran,cr,true);
    }

    template <typename T, template <typename> class VEC> static inline
    void testVector(MPI &mpi, Random::CoinFlip &ran)
    {
        Y_MPI_Trace(mpi, std::cerr << std::endl << "testVector<" << RTTI::Name< VEC<T> >() << "> DIM=" << VEC<T>::DIMENSIONS << std::endl);
        MPI::Carrier & cr = mpi.getVectorCarrier< VEC<T> >();
        testCarrier< VEC<T> >(mpi,ran,cr,true);
    }

    template <typename T> static inline
    void testWithAPI(MPI &mpi, Random::CoinFlip &ran)
    {
        Y_MPI_Trace(mpi, std::cerr << std::endl << "testWithAPI<" << RTTI::Name<T>() << ">" << std::endl);
        static MPI::Carrier & cr = mpi.getCarrier<T>();
        testCarrier<T>(mpi,ran,cr,false);
    }


}


Y_UTEST(carrier)
{
    MPI &      mpi = MPI::Init(&argc,&argv);
    Core::Rand ran;

    testScalar<float>(mpi,ran);
    testScalar<int16_t>(mpi,ran);

    testVector<double,Complex>(mpi,ran);
    testVector<float,V2D>(mpi,ran);
    testVector<double,V3D>(mpi,ran);
    testVector<float,V4D>(mpi,ran);


    testSerial<String>(mpi,ran);
    testSerial<apn>(mpi,ran);
    testSerial<apz>(mpi,ran);
    testSerial<apq>(mpi,ran);

    
    XRealOutput::Mode = XRealOutput::Compact;
    testScalar< XReal<double> >(mpi,ran);


    testWithAPI<float>(mpi,ran);
    testWithAPI<String>(mpi,ran);
    testWithAPI< XReal<float> >(mpi,ran);
    testWithAPI< Complex<float> >(mpi,ran);



}
Y_UDONE()

