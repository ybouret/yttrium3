
//! \file

#ifndef Y_Cameo_Sum_Raised
#define Y_Cameo_Sum_Raised 1


#include "y/apex/integer.hpp"
#include "y/cameo/summator.hpp"
#include "y/type/alternative.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        namespace Sum
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
#define Y_Cameo_Sum_Raised_Check() Y_STATIC_CHECK(ByRaisedAPI<MutableType>::IsProper,BadType)

            //__________________________________________________________________
            //
            //
            //
            //! Raised, Scalar summator: integral to arbitrary precision
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Raised : public Summator<T>
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                Y_Args_Expose(T,Type);                                        //!< aliases
                typedef typename ByRaisedAPI<MutableType>::Type Accumulator; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                inline explicit Raised()              : acc(0)         { Y_Cameo_Sum_Raised_Check(); } //!< setup
                inline explicit Raised(const size_t ) : acc(0)         { Y_Cameo_Sum_Raised_Check(); } //!< setup, compativility
                inline Raised(const Raised &other)    : acc(other.acc) { Y_Cameo_Sum_Raised_Check(); } //!< duplicate \param other another Raised
                inline virtual ~Raised() noexcept                      { acc.ldz(); }                  //!< cleanup

                //! display status
                inline friend std::ostream & operator<<(std::ostream &os, const Raised &self)
                {
                    return os << self.acc;
                }

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                inline virtual void ldz()       noexcept { acc.ldz(); }
                inline virtual void add(ConstType &data) { acc += data; }
                inline virtual Type operator()(void)
                {
                    ConstType res = acc.template cast<MutableType>(0,0);
                    acc.ldz();
                    return res;
                }

                inline virtual const char * callSign() const noexcept
                {
                    return "Cameo::Sum::Raised";
                }


            private:
                Y_Disable_Assign(Raised); //!< discarded
                Accumulator acc;          //!< inner accumulator
            };

        }

    }

}

#endif // !Y_Cameo_Sum_Raised
