

#ifndef Y_MPI_Codec_Included
#define Y_MPI_Codec_Included 1

#include "y/mpi++/api.hpp"
#include "y/system/rtti.hpp"
#include "y/container/associative/addr-key.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! MPI Codec for a given type
    //
    //
    //__________________________________________________________________________
    class MPI:: Codec : public CountedObject
    {
    public:

        //int LegacyScalar;
        //int LegacyVector;
        //int SerializedIO;


        explicit Codec(const std::type_info &);
        virtual ~Codec() noexcept; //!< cleanup

        const AddrKey & key() const noexcept;


        const RTTI    & rtti; //!< unique system rtti
        const AddrKey   tkey; //!< rtti as unique key



    private:
        Y_Disable_Copy_And_Assign(Codec); //!< discard
    };

}

#endif // !Y_MPI_Codec_Included
