//! \file

#ifndef Y_Cameo_Product_Direct
#define Y_Cameo_Product_Direct 1


#include "y/apex/number.hpp"
#include "y/type/conversion.hpp"
#include "y/cameo/multiplier.hpp"
#include "y/check/static.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        namespace Product
        {
            //! compute parameters for given SCALAR type
            template <typename T>
            struct ByDirectAPI
            {
                static const bool IsProper = Y_Is_SuperSubClass_Strict(Apex::Number,T); //!< alias
            };

            //! helper for static check
#define Y_Cameo_Product_Direct_Check() Y_STATIC_CHECK(ByDirectAPI<MutableType>::IsProper,BadType)

            //__________________________________________________________________
            //
            //
            //
            //! Direct, Scalar summator
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Direct : public Multiplier<T>
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                Y_Args_Expose(T,Type);

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                inline explicit Direct() :             prod() { Y_Cameo_Product_Direct_Check(); }
                inline explicit Direct(const size_t) : prod() { Y_Cameo_Product_Direct_Check();}
                inline Direct(const Direct &other) : Multiplier<T>(), prod(other.prod)
                { Y_Cameo_Product_Direct_Check(); }

                inline virtual ~Direct() noexcept { ld1(); }

                //! display status
                inline friend std::ostream & operator<<(std::ostream &os, const Direct &self)
                {
                    return os << self.acc;
                }

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                inline virtual void ld1() noexcept       { prod.ld1();   }
                inline virtual void mul(ConstType &args) { prod *= args; }
                inline virtual Type operator()(void)
                {
                    ConstType saved = prod;
                    ld1();
                    return saved;
                }

                inline virtual const char * callSign() const noexcept
                {
                    return "Cameo::Product::Direct";
                }


            private:
                Y_Disable_Assign(Direct); //!< discarded
                MutableType         prod; //!< inner
            };

        }

    }

}

#endif // !Y_Cameo_Product_Direct
