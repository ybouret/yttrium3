
//! \file

#ifndef Y_MPI_SerialCarrier_Included
#define Y_MPI_SerialCarrier_Included 1

#include "y/mpi++/carrier/serdcl.hpp"
#include "y/stream/memory/input.hpp"

namespace Yttrium
{
    template <typename T>
    class MPI:: SerialCarrier : public MPI_Serial_Carrier
    {
    public:
        Y_Args_Expose(T,Type);
        typedef void (*ReadProc)(MutableType &, InputStream &);
        static ReadProc const Read;

        inline explicit SerialCarrier(const size_t minCapacity) noexcept :
        MPI_Serial_Carrier(minCapacity)
        {}

        inline virtual ~SerialCarrier() noexcept {}

        // Interface
        inline virtual void send(MPI &              mpi,
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

        inline virtual void recv(MPI &         mpi,
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
}


#endif // !Y_MPI_SerialCarrier_Included

