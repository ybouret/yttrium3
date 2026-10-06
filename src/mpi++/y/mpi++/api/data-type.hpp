
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
