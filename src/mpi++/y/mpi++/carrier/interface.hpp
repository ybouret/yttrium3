//______________________________________________________________________________
//
//
//
//! Carrier interface
//
//
//______________________________________________________________________________
class  Carrier : public CountedObject
{
public:
    //__________________________________________________________________________
    //
    //
    // Definitions
    //
    //__________________________________________________________________________
    typedef ArcPtr<Carrier>        Handle; //!< alias
    typedef HashMap<String,Handle> Table;  //!< alias

    //__________________________________________________________________________
    //
    //
    // C++
    //
    //__________________________________________________________________________
    explicit Carrier() noexcept; //!< setup
    virtual ~Carrier() noexcept; //!< cleanup

    //__________________________________________________________________________
    //
    //
    // Interface
    //
    //__________________________________________________________________________


    //! send array of objects
    /**
     \param mpi    instance
     \param entry  first object address
     \param items  number of objects
     \param target target rank
     \param tag    channel
     */
    virtual void send(MPI &              mpi,
                      const void * const entry,
                      const size_t       items,
                      const size_t       target,
                      const int          tag) = 0;

    //! receive array of objects
    /**
     \param mpi    instance
     \param entry  first object address
     \param items  number of objects
     \param source source rank
     \param tag    channel
     */
    virtual void recv(MPI &         mpi,
                      void * const  entry,
                      const size_t  items,
                      const size_t  source,
                      const int     tag) = 0;

    //! send/recv arrays of objects
    /**
     \param mpi        instance
     \param sendEntry  address of first object to send
     \param sendItems  number of objects to send
     \param sendRank   target rank
     \param recvEntry  address of first object to recv
     \param recvItems  number of objects to recv
     \param recvRank   source rank
     \param tag        channel
     */
    virtual void sendrecv(MPI        &       mpi,
                          const void * const sendEntry,
                          const size_t       sendItems,
                          const size_t       sendRank,
                          void * const       recvEntry,
                          const size_t       recvItems,
                          const size_t       recvRank,
                          const int          tag) = 0;


    //! bcast arrays of objects
    virtual void bcast(MPI &mpi,
                       void * const entry,
                       const size_t items,
                       const size_t root) = 0;

private:
    Y_Disable_Copy_And_Assign(Carrier); //!< discarded
};


//______________________________________________________________________________
//
//
// Carrier query/store with carriers
//
//______________________________________________________________________________

//! \return carrier by key
Carrier * queryCarrier(const String&) noexcept;

//! \return carrier by type_info
Carrier * queryCarrier(const std::type_info&)  ;

//! \return carrier based on typeid(T)
template <typename T> inline   Carrier * queryCarrierOf()
{
    return queryCarrier(typeid(T));
}

//! store a new carrier with key
Carrier & storeCarrier(const String &, Carrier * const);



//______________________________________________________________________________
//
//
// Carriers creation
//
//______________________________________________________________________________

//! \return new carrier for given scalar data type
static Carrier * CreateScalarCarrier(const DataType&);

//! \return new carrier for given vector of data type
static Carrier * CreateVectorCarrier(const DataType&, const size_t);

//! \return get/create scalar carrier for T
template <typename T> inline
Carrier & getScalarCarrier()
{
    const String    key = typeid(T).name();
    Carrier * const cr  = queryCarrier(key);
    if(cr)
        return *cr;
    else
        return storeCarrier(key,CreateScalarCarrier( getDataType(key) ));
}

//! \return get/create vector carrier for VECTOR<T>

template <typename T> inline
Carrier & getVectorCarrier()
{
    const String      key = typeid(T).name();
    Carrier * const   cr  = queryCarrier(key);
    if(cr)
        return *cr;
    else
    {
        typedef typename T::Type ScalarType;
        return storeCarrier(key,CreateVectorCarrier( getDataTypeOf<ScalarType>(), T::DIMENSIONS ));
    }
}



//! \return get/create a serial carrier for serializable T
template <typename T> inline
Carrier & getSerialCarrier()
{
    const String    key = typeid(T).name();
    Carrier * const cr  = queryCarrier(key);
    if(cr)
        return *cr;
    else
        return storeCarrier(key, new SerialCarrier<T>(BUFSIZ)  );
}




