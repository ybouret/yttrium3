

//! \file

#ifndef Y_Cameo_Product_Raised
#define Y_Cameo_Product_Raised 1


#include "y/apex/integer.hpp"
#include "y/cameo/multiplier.hpp"
#include "y/type/alternative.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        namespace Product
        {
            //! compute raised parameters for given type
            template <typename T> struct ByRaisedAPI
            {
                static const bool UseSigned   = TypeTraits<T>::InStandardIntegers || TypeTraits<T>::InPlatformIntegers; //!< alias
                static const bool UseUnsigned = TypeTraits<T>::InStandardUnsigned || TypeTraits<T>::InPlatformUnsigned; //!< alias
                static const bool IsProper    =  UseSigned || UseUnsigned;                                              //!< acceptable
                typedef typename Alternative<UseSigned,apz,UseUnsigned,apn,NullType>::Type Type;                        //!< alias
            };

            //! helper for static check
#define Y_Cameo_Product_Raised_Check() Y_STATIC_CHECK(ByRaisedAPI<MutableType>::IsProper,BadType)

            //__________________________________________________________________
            //
            //
            //
            //! Raised, Scalar summator: integral to arbitrary precision
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Raised : public Multiplier<T>
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                Y_Args_Expose(T,Type);                                //!< aliases
                typedef typename ByRaisedAPI<MutableType>::Type Prod; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                inline explicit Raised()              : prod(0)          { Y_Cameo_Product_Raised_Check(); } //!< setup
                inline explicit Raised(const size_t ) : prod(0)          { Y_Cameo_Product_Raised_Check(); } //!< setup, compatibility
                inline Raised(const Raised &other)    : prod(other.prod) { Y_Cameo_Product_Raised_Check(); } //!< duplicate \param other another Raised
                inline virtual ~Raised() noexcept                        { prod.ld1(); }                  //!< cleanup

                //! display status
                inline friend std::ostream & operator<<(std::ostream &os, const Raised &self)
                {
                    return os << self.prod;
                }

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                inline virtual void ld1()       noexcept  { prod.ld1(); }
                inline virtual void mul(ConstType &data)  { prod *= data; }
                inline virtual Type operator()(void)
                {
                    ConstType res = prod.template cast<MutableType>(0,0);
                    prod.ld1();
                    return res;
                }

                inline virtual const char * callSign() const noexcept
                {
                    return "Cameo::Product::Raised";
                }


            private:
                Y_Disable_Assign(Raised); //!< discarded
                Prod prod;          //!< inner accumulator
            };

        }

    }

}

#endif // !Y_Cameo_Sum_Raised
