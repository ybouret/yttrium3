
//! \file

#ifndef Y_MKL_Fit_Variable_Included
#define Y_MKL_Fit_Variable_Included 1

#include "y/string.hpp"
#include "y/pointer/arc.hpp"
#include "y/pointer/keyed.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            class Variable : public String
            {
            public:
                static const char * const                CallSign;
                typedef Keyed< String,ArcPtr<Variable> > Pointer;

                template <typename NAME>
                inline   Variable(const NAME &varName) :
                String(varName)
                {
                    checkName();
                }

                virtual ~Variable() noexcept;
                Y_OSTREAM_PROTO(Variable);

                virtual size_t indx() const noexcept = 0;
                const String  & key() const noexcept;

               

                template <typename ARRAY> inline
                typename ARRAY::Type & operator[](ARRAY &arr) const
                {
                    const size_t i = indx(); assert(i>0); assert(i<=arr.size());
                    return arr[i];
                }

                template <typename ARRAY> inline
                typename ARRAY::ConstType & operator[](const ARRAY &arr) const
                {
                    const size_t i = indx(); assert(i>0); assert(i<=arr.size());
                    return arr[i];
                }

            private:
                Y_Disable_Copy_And_Assign(Variable);
                void checkName() const;
            };

          

        }

    }

}

#endif // !Y_MKL_Fit_Variable_Included
