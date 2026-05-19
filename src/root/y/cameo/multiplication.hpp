
//! \file

#ifndef Y_Cameo_Multiplication_Included
#define Y_Cameo_Multiplication_Included 1

#include "y/cameo/product/operating.hpp"

namespace Yttrium
{
    namespace Cameo
    {

        //__________________________________________________________________
        //
        //
        //
        //! Multiplication algorithms
        //
        //
        //__________________________________________________________________
        template <typename T>
        class Multiplication : public Product::Operating<T>::Type
        {
        public:
            //______________________________________________________________
            //
            //
            // Definitions
            //
            //______________________________________________________________
            typedef typename Product::Operating<T>::Type MulType; //!< alias


            //______________________________________________________________
            //
            //
            // C++
            //
            //______________________________________________________________

            //! setup
            inline explicit Multiplication() : MulType() {}

            //! setup \param minCapacity compatibility
            inline explicit Multiplication(const size_t minCapacity) : MulType(minCapacity) {}

            //! duplicate \param m another multiplication
            inline Multiplication(const Multiplication &m) : MulType(m) {}

            //! cleanup
            inline virtual ~Multiplication() noexcept    {}

        private:
            Y_Disable_Assign(Multiplication); //!< discarded
        };

    }

}

#endif // !Y_Cameo_Multiplication_Included

