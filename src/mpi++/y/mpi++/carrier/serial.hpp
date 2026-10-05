
//! \file

#ifndef Y_MPI_SerialCarrier_Included
#define Y_MPI_SerialCarrier_Included 1

#include "y/mpi++/carrier/serdcl.hpp"
#include "y/stream/memory/input.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Carrier for Serializable objects
    //
    //
    //__________________________________________________________________________
    template <typename T>
    class MPI:: SerialCarrier : public MPI_Serial_Carrier
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Expose(T,Type); //!< alias
        typedef void (*ReadProc)(MutableType &, InputStream &); //!< alias
        static ReadProc const Read; //!< to be implemented

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup \param minCapacity for inner buffer
        inline explicit SerialCarrier(const size_t minCapacity) noexcept :
        MPI_Serial_Carrier(minCapacity)
        {}

        //! cleanup
        inline virtual ~SerialCarrier() noexcept {}

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
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
        Y_Disable_Copy_And_Assign(SerialCarrier); //!< discarded
    };

#define Y_MPI_Serial_Decl(CLASS) \
template<> MPI::SerialCarrier<CLASS>::ReadProc const MPI::SerialCarrier<CLASS>:: Read

    Y_MPI_Serial_Decl(String);

    namespace Apex { class Natural; class Integer; class Rational; }
    Y_MPI_Serial_Decl(Apex::Natural);
    Y_MPI_Serial_Decl(Apex::Integer);
    Y_MPI_Serial_Decl(Apex::Rational);
    
}


#endif // !Y_MPI_SerialCarrier_Included

