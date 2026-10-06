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
    OutputMemoryStream buffer; //!< I/O buffer

protected:
    //__________________________________________________________________________
    //
    //
    // Methods
    //
    //__________________________________________________________________________
    //! read buffer from source and tag \return loaded buffer
    const Memory::ReadOnlyBuffer & load(MPI &,const size_t,const int);

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
        // initialize buffer
        buffer->free();

        // collect data
        {
            ConstType * host = static_cast<ConstType *>(entry);
            for(size_t i=items;i>0;--i,++host)
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

