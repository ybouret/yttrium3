
//! \file

#ifndef Y_Cameo_Addition_Included
#define Y_Cameo_Addition_Included 1


#include "y/cameo/sum/operating.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        //______________________________________________________________________
        //
        //
        //
        //! Generic addition class
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Addition : public Sum::Operating<T>::Type
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef typename  Sum::Operating<T>::Type SummatorType; //!< alias
            static const bool IsSummator = Y_Is_SuperSubClass_Strict(Summator<T>,Addition); //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            inline explicit Addition() : SummatorType()                                    {} //!< setup
            inline explicit Addition(const size_t minCapacity) : SummatorType(minCapacity) {} //!< setup \param minCapacity compatibility
            inline Addition(const Addition &other) : SummatorType(other)                   {} //!< duplicate \param other another addition
            inline virtual ~Addition() noexcept                                            {} //!< cleanup

        private:
            Y_Disable_Assign(Addition); //!< discarded
        };
    }
}

#endif // !Y_Cameo_Addition_Included



