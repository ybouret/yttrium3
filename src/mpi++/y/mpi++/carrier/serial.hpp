//______________________________________________________________________________
//
//
//
//! SerialCarrier base class
//
//
//______________________________________________________________________________
class SerialCarrier_ : public Carrier
{
public:
    //__________________________________________________________________________
    //
    //
    // Definitions
    //
    //__________________________________________________________________________
    static const char * const BufferName; //!< "MPI::SerialCarrier"

    //__________________________________________________________________________
    //
    //
    // C++
    //
    //__________________________________________________________________________
    explicit SerialCarrier_(const size_t minCapacity); //!< setup \param minCapacity bytes for buffer
    virtual ~SerialCarrier_() noexcept;                //!< cleanup

    //__________________________________________________________________________
    //
    //
    // Members
    //
    //__________________________________________________________________________
    OutputMemoryStream selfBuffer; //!< I/O buffer
    OutputMemoryStream peerBuffer; //!< I/O buffer

protected:
    //__________________________________________________________________________
    //
    //
    // Methods
    //
    //__________________________________________________________________________
    //! read buffer from source and tag \return loaded buffer
    const Memory::ReadOnlyBuffer & load(MPI &,const size_t,const int);

    //! exchange sizes
    /**
     \param mpi MPI
     \param sendSize number of bytes to send
     \param sendRank target rank
     \param recvRank source rank
     \param tag      communication tag
     \return number of bytes to recv
     */
    size_t sendRecvSizes(MPI &        mpi,
                         const size_t sendSize,
                         const size_t sendRank,
                         const size_t recvRank,
                         const int    tag);

private:
    Y_Disable_Copy_And_Assign(SerialCarrier_); //!< dicarded
};

//______________________________________________________________________________
//
//
//
//! Generic SerialCarrier
//
//
//______________________________________________________________________________
template <typename T>
class SerialCarrier : public SerialCarrier_
{
public:
    //__________________________________________________________________________
    //
    //
    // Definitions
    //
    //__________________________________________________________________________
    Y_Args_Expose(T,Type); //!< alias
    typedef void (*ReadProc)(MutableType &, InputStream &); //!< alias
    static ReadProc const Read; //!< to be implemented

    //__________________________________________________________________________
    //
    //
    // C++
    //
    //__________________________________________________________________________

    //! setup \param minCapacity for inner buffer
    inline explicit SerialCarrier(const size_t minCapacity) noexcept :
    SerialCarrier_(minCapacity)
    {}

    //! cleanup
    inline virtual ~SerialCarrier() noexcept {}

    //__________________________________________________________________________
    //
    //
    // Interface
    //
    //__________________________________________________________________________
    inline virtual void send(MPI &              mpi,
                             const void * const entry,
                             const size_t       items,
                             const size_t       target,
                             const int          tag)
    {
        (void)encode(entry,items);
        mpi.sendBuffer(selfBuffer,target,tag);
    }

    inline virtual void recv(MPI &         mpi,
                             void * const  entry,
                             const size_t  items,
                             const size_t  source,
                             const int     tag)
    {
        decode(entry,items,load(mpi,source,tag));
    }

    inline virtual void sendrecv(MPI        &       mpi,
                                 const void * const sendEntry,
                                 const size_t       sendItems,
                                 const size_t       sendRank,
                                 void * const       recvEntry,
                                 const size_t       recvItems,
                                 const size_t       recvRank,
                                 const int          tag)
    {
        const size_t sendSize = encode(sendEntry,sendItems);
        const size_t recvSize = sendRecvSizes(mpi,sendSize,sendRank,recvRank,tag);
        peerBuffer->adjust(recvSize,0);
        mpi.sendrecvBytes(selfBuffer.ro(), sendSize, sendRank,
                          peerBuffer.rw(), recvSize, recvRank,
                          tag,tag);
        decode(recvEntry,recvItems,peerBuffer);
    }

    inline virtual void bcast(MPI &        mpi,
                              void * const entry,
                              const size_t items,
                              const size_t root)
    {
        // prepare root buffer
        size_t sendSize = (root==mpi.rank) ? encode(entry,items) : 0;

        // broadcast sendSize
        mpi.bcastSize(sendSize,root);

        // adjust other buffer(s)
        if(root!=mpi.rank) selfBuffer->adjust(sendSize,0);

        // broacast root content
        mpi.bcastBytes(selfBuffer.rw(),sendSize,root);

        // decode other buffer(s)
        if(root!=mpi.rank) decode(entry,items,selfBuffer);
    }



private:
    Y_Disable_Copy_And_Assign(SerialCarrier); //!< discarded

    //! encode objects
    /**
     \param entry first object address
     \param items number of objects
     \return encoded bytes
     */
    inline size_t encode(const void * const entry,
                         const size_t       items)
    {
        //----------------------------------------------------------------------
        // initialize buffer
        //----------------------------------------------------------------------
        selfBuffer->free();

        //----------------------------------------------------------------------
        // collect data
        //----------------------------------------------------------------------
        {
            ConstType * host = static_cast<ConstType *>(entry);
            for(size_t i=items;i>0;--i,++host)
                (void) host->serialize(selfBuffer);
        }

        return selfBuffer.length();
    }

    //! decode serialized buffer
    /**
     \param entry first object address
     \param items objects to decode
     \param robuf read data
     */
    inline void decode(void * const                  entry,
                       const size_t                  items,
                       const Memory::ReadOnlyBuffer &robuf)
    {
        InputMemoryStream fp(CallSign,robuf);
        MutableType     * host = static_cast<MutableType *>(entry);
        for(size_t i=items;i>0;--i,++host)
            Read(*host,fp);
    }

};

