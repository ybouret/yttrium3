
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


        virtual void send(MPI &              mpi,
                          const void * const entry,
                          const size_t       items,
                          const size_t       target,
                          const int          tag) = 0;

        virtual void recv(MPI &         mpi,
                          void * const  entry,
                          const size_t  items,
                          const size_t  source,
                          const int     tag) = 0;


    private:
        Y_Disable_Copy_And_Assign(Carrier);
    };

    //! for arrays of scalar type
    class MPI::  ScalarCarrier : public Carrier
    {
    public:
        explicit ScalarCarrier(const MPI::DataType &mdt) noexcept : dataType(mdt) {}
        virtual ~ScalarCarrier() noexcept {}

        virtual void send(MPI &              mpi,
                          const void * const entry,
                          const size_t       items,
                          const size_t       target,
                          const int          tag)
        {
            mpi.send(entry,items,dataType.value,dataType.bytes*items,target,tag);
        }

        virtual void recv(MPI &         mpi,
                          void * const  entry,
                          const size_t  items,
                          const size_t  source,
                          const int     tag)
        {
            mpi.recv(entry,items,dataType.value,dataType.bytes*items,source,tag);
        }

        const MPI::DataType &dataType;


    private:
        Y_Disable_Copy_And_Assign(ScalarCarrier);
    };

    //! for arrays of vector type
    class MPI::  VectorCarrier : public Carrier
    {
    public:
        explicit VectorCarrier(const MPI::DataType &mdt,
                               const size_t         dim) noexcept :
        scalarType(mdt),
        dimensions(dim)
        {
            assert(dim>0);
        }

        virtual ~VectorCarrier() noexcept {}

        virtual void send(MPI &              mpi,
                          const void * const entry,
                          const size_t       items,
                          const size_t       target,
                          const int          tag)
        {
            const size_t words = items * dimensions;
            mpi.send(entry,words,scalarType.value,scalarType.bytes*words,target,tag);
        }

        virtual void recv(MPI &         mpi,
                          void * const  entry,
                          const size_t  items,
                          const size_t  source,
                          const int     tag)
        {
            const size_t words = items * dimensions;
            mpi.recv(entry,words,scalarType.value,scalarType.bytes*words,source,tag);
        }

        const MPI::DataType & scalarType;
        const size_t          dimensions;



    private:
        Y_Disable_Copy_And_Assign(VectorCarrier);
    };

    class MPI_Serial_Carrier : public MPI::Carrier
    {
    public:
        static const char * const CallSign;

        explicit MPI_Serial_Carrier(const size_t minCapacity) noexcept : Carrier(), buffer(CallSign,minCapacity) {}
        virtual ~MPI_Serial_Carrier() noexcept {}

        OutputMemoryStream buffer;

    private:
        Y_Disable_Copy_And_Assign(MPI_Serial_Carrier);
    };

    const char * const MPI_Serial_Carrier::CallSign = "MPI::SerialCarrier";


    template <typename T>
    class MPI:: SerialCarrier : public MPI_Serial_Carrier
    {
    public:
        Y_Args_Expose(T,Type);

        explicit SerialCarrier(const size_t minCapacity) noexcept : MPI_Serial_Carrier(minCapacity) {}
        virtual ~SerialCarrier() noexcept {}

        virtual void send(MPI &              mpi,
                          const void * const entry,
                          const size_t       items,
                          const size_t       target,
                          const int          tag)
        {
            // initialize buffer
            buffer->free();

            // collect data
            {
                ConstType * host = static_cast<ConstType *>(entry);
                for(size_t i=items;i>0;--i)
                    (void) host->serialize(buffer);
            }

            // send buffer
            mpi.sendBuffer(buffer,target,tag);
        }

        virtual void recv(MPI &         mpi,
                          void * const  entry,
                          const size_t  items,
                          const size_t  source,
                          const int     tag)
        {

        }



    private:
        Y_Disable_Copy_And_Assign(SerialCarrier);
    };




}

Y_UTEST(carrier)
{
    MPI & mpi = MPI::Init(&argc,&argv);
    Y_MPI_ForEach(mpi,std::cerr << "@" << mpi << std::endl);


    MPI::SerialCarrier<String> cr(100);


}
Y_UDONE()

