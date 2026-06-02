//! \file

#ifndef Y_Associative_DefaultHashSet_Inluded
#define Y_Associative_DefaultHashSet_Inluded 1

#include "y/container/associative/hash/set.hpp"


namespace Yttrium
{
	typedef Hashing::KeyWith<Hashing::FNV> DefaultKeyHasher;

	template <typename KEY, typename T>
	class DefaultHashSet : public HashSet<KEY, T, DefaultKeyHasher >
	{
	public:
		typedef HashSet<KEY, T, DefaultKeyHasher> BaseType;

		inline explicit DefaultHashSet(const size_t minTableSize = 0) : BaseType(minTableSize) {}
		inline DefaultHashSet(const DefaultHashSet& other) : BaseType(other) {}
		inline virtual ~DefaultHashSet() noexcept {}

	private:
		Y_Disable_Assign(DefaultHashSet);
	};

}

#endif 