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


private:
    Y_Disable_Copy_And_Assign(Carrier); //!< discarded
};


const Carrier * queryCarrier(const String&) const noexcept;
const Carrier * queryCarrier(const std::type_info&) const;

template <typename T> inline const Carrier * queryCarrierOf() const
{
    return queryCarrier(typeid(T));
}

void storeCarrier(const String &, Carrier * const);


static Carrier * CreateScalarCarrier(const DataType&);
static Carrier * CreateVectorCarrier(const DataType&, const size_t);

//! \return carrier for T
template <typename T> static inline
Carrier * ScalarCarrierProc(MPI &mpi)
{
    static const DataType& _ = mpi.getDataTypeOf<T>();
    return CreateScalarCarrier(_);
}

//! \return carrier for VEC<T>
template <template <typename> class VEC, typename T> static inline
Carrier * VectorCarrierProc(MPI &mpi)
{
    static const DataType& _ = mpi.getDataTypeOf<T>();
    return CreateVectorCarrier(_, VEC<T>::DIMENSIONS);
}

//! \return carrier for Serializable
template <typename T> static inline
Carrier * SerialCarrierProc(MPI &)
{
    return new SerialCarrier<T>(BUFSIZ);
}
