
#include "y/mpi++/carrier/scalar.hpp"

#include "y/utest/run.hpp"
#include <cstring>


#include "y/stream/memory/output.hpp"
#include "y/stream/memory/input.hpp"

using namespace Yttrium;

namespace Yttrium
{



   

   
    class MPI_Serial_Carrier : public MPI::Carrier
    {
    public:
        static const char * const CallSign;

        explicit MPI_Serial_Carrier(const size_t minCapacity) noexcept : Carrier(), buffer(CallSign,minCapacity) {}
        virtual ~MPI_Serial_Carrier() noexcept {}

        OutputMemoryStream buffer;

    protected:
        const Memory::ReadOnlyBuffer & load(MPI &mpi, const size_t source, const int tag)
        {
            const size_t blockSize = mpi.recvSize(source,tag);
            buffer->adjust(blockSize,0);
            mpi.recvBytes(buffer.rw(),blockSize,source,tag);
            return buffer;
        }

    private:
        Y_Disable_Copy_And_Assign(MPI_Serial_Carrier);
    };

    const char * const MPI_Serial_Carrier::CallSign = "MPI::SerialCarrier";


    template <typename T>
    class MPI:: SerialCarrier : public MPI_Serial_Carrier
    {
    public:
        Y_Args_Expose(T,Type);
        typedef void (*ReadProc)(MutableType &, InputStream &);
        static ReadProc const Read;

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
            InputMemoryStream fp(CallSign,load(mpi,source,tag));
            MutableType     * host = static_cast<MutableType *>(entry);
            for(size_t i=items;i>0;--i,++host)
                Read(*host,fp);

        }



    private:
        Y_Disable_Copy_And_Assign(SerialCarrier);
    };


    namespace
    {
        static inline void ReadString(String &s, InputStream &fp)
        {
            static const char * const varName = "String";
            String tmp = String::Read(fp,varName);
            s.xch(tmp);
        }
    }

    template<> MPI::SerialCarrier<String>::ReadProc const MPI::SerialCarrier<String>:: Read = ReadString;


}

#include "y/format/hexadecimal.hpp"

Y_UTEST(carrier)
{
    MPI & mpi = MPI::Init(&argc,&argv);


    MPI::SerialCarrier<String> cr(100);
    String str;
    if(mpi.primary)
    {
        str = "Hello, World!";
        for(size_t rank=1;rank<mpi.size;++rank)
        {
            cr.send(mpi,&str,1,rank,7);
        }
    }
    else
    {
        cr.recv(mpi,&str,1,0,7);
    }

    Y_MPI_ForEach(mpi, std::cerr << "@" << mpi << " : length=" << cr.buffer.length() << " | crc " << Hexadecimal(cr.buffer.crc()) << " => '" << str << "'" << std::endl );


}
Y_UDONE()

