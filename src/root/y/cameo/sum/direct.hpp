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

#define Y_Cameo_Sum_Direct_Check() Y_STATIC_CHECK(ByDirectAPI<MutableType>::IsProper,BadType)

            template <typename T>
            class Direct : public Summator<T>
            {
            public:
                Y_Args_Expose(T,Type);

                inline explicit Direct()             : acc(0)         { Y_Cameo_Sum_Direct_Check(); }
                inline explicit Direct(const size_t) : acc(0)         { Y_Cameo_Sum_Direct_Check(); }
                inline Direct(const Direct &other)   : acc(other.acc) { Y_Cameo_Sum_Direct_Check(); }
                inline virtual ~Direct() noexcept { acc.ldz(); }


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
                Y_Disable_Assign(Direct);
                MutableType acc;
            };


        }
    }
}

#endif // !Y_Cameo_Sum_Direct

