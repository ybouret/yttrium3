//! \file

#ifndef Y_Cameo_Sum_Direct
#define Y_Cameo_Sum_Direct 1


#include "y/apex/number.hpp"
#include "y/type/conversion.hpp"
#include "y/cameo/summator.hpp"
#include "y/check/static.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        namespace Sum
        {
            //! compute parameters for given SCALAR type
            template <typename T>
            struct ByDirectAPI
            {
                static const bool IsProper = Y_Is_SuperSubClass_Strict(Apex::Number,T); //!< alias
            };

            //! helper for static check
#define Y_Cameo_Sum_Direct_Check() Y_STATIC_CHECK(ByDirectAPI<MutableType>::IsProper,BadType)

            //__________________________________________________________________
            //
            //
            //
            //! Direct, Scalar summator
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Direct : public Summator<T>
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                Y_Args_Expose(T,Type); //!< aliases

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                inline explicit Direct()             : acc(0)         { Y_Cameo_Sum_Direct_Check(); } //!< setup
                inline explicit Direct(const size_t) : acc(0)         { Y_Cameo_Sum_Direct_Check(); } //!< setup, compatibility
                inline Direct(const Direct &other)   : acc(other.acc) { Y_Cameo_Sum_Direct_Check(); } //!< duplicate \param other another Direct
                inline virtual ~Direct() noexcept                     { acc.ldz(); }                  //!< cleanup

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
                inline virtual void ldz()       noexcept { acc.ldz(); }
                inline virtual void add(ConstType &data) { acc += data; }
                inline virtual Type operator()(void)
                {
                    ConstType saved  = acc;
                    acc.ldz();
                    return saved;
                }

                inline virtual const char * callSign() const noexcept
                {
                    return "Cameo::Sum::Direct";
                }


            private:
                Y_Disable_Assign(Direct); //!< discarded
                MutableType acc;          //!< inner accumulator
            };


        }
    }
}

#endif // !Y_Cameo_Sum_Direct

