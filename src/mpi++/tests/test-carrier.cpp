
#include "y/mpi++/api.hpp"
#include "y/utest/run.hpp"
#include <cstring>


#include "y/stream/memory/output.hpp"

using namespace Yttrium;

namespace Yttrium
{

    class MPI::Carrier : public CountedObject
    {
    public:
        explicit Carrier() noexcept {}
        virtual ~Carrier() noexcept {}

        virtual void send(MPI &                mpi,
                          const void * const   entry,
                          const size_t         items,
                          const MPI::DataType &dtype,
                          const size_t         target,
                          const int            tag) = 0;


    private:
        Y_Disable_Copy_And_Assign(Carrier);
    };

    //! for arrays of scalar type
    class MPI::  ScalarCarrier : public Carrier
    {
    public:
        explicit ScalarCarrier() noexcept {}
        virtual ~ScalarCarrier() noexcept {}

        virtual void send(MPI &                mpi,
                          const void * const   entry,
                          const size_t         items,
                          const MPI::DataType &dtype,
                          const size_t         target,
                          const int            tag)
        {
            mpi.send(entry,items,dtype.value,dtype.bytes*items,target,tag);
        }

    private:
        Y_Disable_Copy_And_Assign(ScalarCarrier);
    };

    //! for arrays of vector type
    class MPI::  VectorCarrier : public Carrier
    {
    public:
        explicit VectorCarrier(const size_t dim) noexcept : dimensions(dim)
        {
            assert(dimensions>0);
        }

        virtual ~VectorCarrier() noexcept {}

        const size_t dimensions;

        virtual void send(MPI &                mpi,
                          const void * const   entry,
                          const size_t         items,
                          const MPI::DataType &dtype,
                          const size_t         target,
                          const int            tag)
        {
            const size_t words = items * dimensions;
            mpi.send(entry,words,dtype.value,dtype.bytes*words,target,tag);
        }

    private:
        Y_Disable_Copy_And_Assign(VectorCarrier);
    };

    class MPI:: SerialCarrier : public Carrier
    {
    public:
        static const char * const CallSign;
        explicit SerialCarrier(const size_t minCapacity) noexcept : Carrier(), buffer(CallSign,minCapacity) {}
        virtual ~SerialCarrier() noexcept {}

        OutputMemoryStream buffer;
        


    private:
        Y_Disable_Copy_And_Assign(SerialCarrier);
    };

    const char * const MPI:: SerialCarrier::CallSign = "MPI::SerialCarrier";



}

Y_UTEST(carrier)
{
    MPI & mpi = MPI::Init(&argc,&argv);
    Y_MPI_ForEach(mpi,std::cerr << "@" << mpi << std::endl);

}
Y_UDONE()

