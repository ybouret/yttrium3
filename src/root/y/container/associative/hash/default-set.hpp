//! \file

#ifndef Y_Associative_DefaultHashSet_Inluded
#define Y_Associative_DefaultHashSet_Inluded 1

#include "y/container/associative/hash/set.hpp"


namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Default Key Hasher
    //
    //
    //__________________________________________________________________________
	typedef Hashing::KeyWith<Hashing::FNV> DefaultKeyHasher;

    //__________________________________________________________________________
    //
    //
    //
    //! HashSet with DefaultKeyHasher
    //
    //
    //__________________________________________________________________________
	template <typename KEY, typename T>
	class DefaultHashSet : public HashSet<KEY, T, DefaultKeyHasher >
	{
	public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
		typedef HashSet<KEY, T, DefaultKeyHasher> BaseType; //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup \param minTableSize optional minimal table size
        inline explicit DefaultHashSet(const size_t minTableSize = 0) : BaseType(minTableSize) {}

        //! duplicate \param other another HashSet
		inline DefaultHashSet(const DefaultHashSet& other) : BaseType(other) {}

        //! cleanup
		inline virtual ~DefaultHashSet() noexcept {}

	private:
		Y_Disable_Assign(DefaultHashSet); //!< discarded
	};

}

#endif // !Y_Associative_DefaultHashSet_Inluded
