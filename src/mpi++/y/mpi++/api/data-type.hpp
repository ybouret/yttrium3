
//______________________________________________________________________________
//
//
//
//! DataType
//
//
//______________________________________________________________________________
class DataType : public CountedObject
{
public:
    //__________________________________________________________________________
    //
    //
    // Definitions
    //
    //__________________________________________________________________________
    typedef ArcPtr<DataType>        Pointer; //!< alias
    typedef HashMap<String,Pointer> Table;   //!< hash table of types

    //! identifies genre as BuiltIn or user Defined
    enum Genre
    {
        BuiltIn, //!< pre-committed data type
        Defined  //!< user defined data type
    };


    //__________________________________________________________________________
    //
    //
    // C++
    //
    //__________________________________________________________________________

    //! setup with built-in type and size
    explicit DataType(const MPI_Datatype, const size_t) noexcept;

    //! setup with user's metrics
    /**
     \param mpi instance to get individual bytes
     \param count number of fields in all subsequent arrays, count>0
     \param array_of_block_lengths consecutive block lengths
     \param array_of_displacements  offsets of previous blocks
     \param array_of_types          types of preivous blocks
     */
    explicit DataType(MPI &              mpi,
                      const int          count,
                      const int          array_of_block_lengths[],
                      const MPI_Aint     array_of_displacements[],
                      const MPI_Datatype array_of_types[]);

    virtual ~DataType()                        noexcept; //!< cleanup

    //__________________________________________________________________________
    //
    //
    // Members
    //
    //__________________________________________________________________________
    const MPI_Datatype value; //!< the data type value
    const size_t       bytes; //!< bytes per transmitted item
    const Genre        genre; //!< type genre

private:
    Y_Disable_Copy_And_Assign(DataType); //!< discard
};


//! \return data type from type info of MPI supported type
const DataType & getDataType(const std::type_info &) const;

//! \return data type from type of T
template <typename T> inline
const DataType & getDataTypeOf() const {
    static const DataType & _ = getDataType(typeid(T));
    return _;
};

//! \return retrieve matching datatype
MPI_Datatype _Datatype(const std::type_info &) const;

//! \return matching MPI_Datatype
template <typename T>
inline MPI_Datatype _DatatypeOf() const
{
    static const MPI_Datatype _ = _Datatype( typeid(T) );
    return _;
}

//! \return bytes for given MPI_Datatype, throw if not found
size_t bytesFor(const MPI_Datatype) const;

//! define a new type
/**
 \param tid new type identifier
 \param count                  see DataType(...)
 \param array_of_block_lengths see DataType(...)
 \param array_of_displacements see DataType(...)
 \param array_of_types         see DataType(...)
 */
void decl(const std::type_info &tid,
          const int             count,
          const int             array_of_block_lengths[],
          const MPI_Aint        array_of_displacements[],
          const MPI_Datatype    array_of_types[]);


//! helper to define a new type
template <typename T> inline
void decl(const int             count,
          const int             array_of_block_lengths[],
          const MPI_Aint        array_of_displacements[],
          const MPI_Datatype    array_of_types[])
{
    decl(typeid(T),count,array_of_block_lengths,array_of_displacements,array_of_types);
}

//! helper to define a new heterogeneous pair
template <typename T> inline
void declAsPair(const std::type_info &u,
                const MPI_Aint        uoff,
                const std::type_info &v,
                const MPI_Aint        voff)
{
    static const int   count = 2;
    static const int   array_of_block_lengths[] = {1,1};
    const MPI_Aint     array_of_displacements[] = {uoff,voff};
    const MPI_Datatype array_of_types[]         = {_Datatype(u), _Datatype(v) };
    decl<T>(count,array_of_block_lengths,array_of_displacements,array_of_types);
}
