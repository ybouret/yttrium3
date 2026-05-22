
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
        class Addition : public Object, public Sum::Operating<T>::Type
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
            Y_Args_Declare(T,Type);

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            //! setup
            inline explicit Addition() :
            Object(),
            SummatorType(),
            next(0),
            prev(0) {}

            //! setup \param minCapacity compatibility
            inline explicit Addition(const size_t minCapacity) :
            Object(),
            SummatorType(minCapacity),
            next(0),
            prev(0)
            {}

            //! duplicate \param other another addition
            inline Addition(const Addition &other) :
            Object(),
            SummatorType(other),
            next(0),
            prev(0)
            {}

            inline Addition & operator=(ParamType param)
            {
                this->set(param);
                return *this;
            }

           


            //! cleanup
            inline virtual ~Addition() noexcept {}

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            Addition * next; //!< for list
            Addition * prev; //!< for list
        private:
            Y_Disable_Assign(Addition); //!< discarded
        };
    }
}

#endif // !Y_Cameo_Addition_Included



