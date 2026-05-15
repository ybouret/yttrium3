//! \file

#ifndef Y_Cameo_Add_Straight_Included
#define Y_Cameo_Add_Straight_Included 1


#include "y/cameo/summator.hpp"
#include "y/apex/number.hpp"
#include "y/type/conversion.hpp"
#include "y/check/static.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        //______________________________________________________________________
        //
        //
        //
        //! Summator for SCALAR Cameo::Straight API
        //
        //
        //______________________________________________________________________
        template <typename T>
        class StraightSummator : public Summator<T>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Declare(T,Type); //!< aliases

            //! flag to test consistentcy
            static const bool Applicable = Y_Is_SuperSubClass_Strict(Apex::Number,MutableType);

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            inline explicit StraightSummator() : sum(0)             { Y_STATIC_CHECK(Applicable,BadType); } //!< setup empty
            inline explicit StraightSummator(const size_t) : sum(0) { Y_STATIC_CHECK(Applicable,BadType); } //!< setup empty (compatibility version)
            inline virtual ~StraightSummator() noexcept                             { sum.ldz(); }          //!< cleanup
            inline StraightSummator(const StraightSummator &other) : sum(other.sum) {}                      //!< duplicate \param other another summator

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            inline void ldz() noexcept       { sum.ldz(); }
            inline Type operator()(void)     { ConstType res = sum; sum.ldz(); return res; }
            inline void add(ConstType &data) { sum += data; }

        private:
            Y_Disable_Assign(StraightSummator); //!< discarded
            T sum; //!< inner accumulator
        };
    }
}

#endif // !Y_Cameo_Add_Straight_Included

