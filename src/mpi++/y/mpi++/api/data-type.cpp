
#include "y/mpi++/api.hpp"




namespace Yttrium
{


    MPI:: DataType:: ~DataType() noexcept
    {
        switch(genre)
        {
            case BuiltIn: break;
            case Defined:
                (void) MPI_Type_free( &Coerce(value) );
                break;
        }
    }

    MPI::DataType:: DataType(const MPI_Datatype datatype, const size_t datasize) noexcept :
    CountedObject(),
    value(datatype),
    bytes(datasize),
    genre(BuiltIn)
    {

    }


    MPI:: DataType:: DataType(MPI &              mpi,
                              const int          count,
                              const int          array_of_block_lengths[],
                              const MPI_Aint     array_of_displacements[],
                              const MPI_Datatype array_of_types[]) :
    CountedObject(),
    value(MPI_BYTE),
    bytes(0),
    genre(Defined)
    {
        assert(count>0);
        assert(array_of_block_lengths);
        assert(array_of_displacements);
        assert(array_of_types);

        Y_MPI_Call( MPI_Type_create_struct(count,
                                           array_of_block_lengths,
                                           array_of_displacements,
                                           array_of_types,
                                           &Coerce(value)) );

        try
        {
            // commit type for MPI
            Y_MPI_Call( MPI_Type_commit(&Coerce(value) ) );


            // compute bytes...
            for(int i=0;i<count;++i)
            {
                const int    block_length     = array_of_block_lengths[i];       assert(block_length>0);
                const size_t bytes_per_block  = mpi.bytesFor(array_of_types[i]); assert( bytes_per_block>0);
                Coerce(bytes) += block_length * bytes_per_block;
            }
        }
        catch(...)
        {
            (void) MPI_Type_free( &Coerce(value) );
            throw;
        }
    }

}
