
//! \file

#ifndef Y_MKL_Fit_Variable_Included
#define Y_MKL_Fit_Variable_Included 1

#include "y/string.hpp"
#include "y/pointer/arc.hpp"
#include "y/pointer/keyed.hpp"

namespace Yttrium
{
    template <typename> class Matrix;

    namespace MKL
    {
        namespace Fit
        {

            //__________________________________________________________________
            //
            //
            //
            //! Variable interface
            //
            //
            //__________________________________________________________________
            class Variable : public String
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const char * const                CallSign; //!< "Fit::Variable"
                typedef Keyed< String,ArcPtr<Variable> > Pointer;  //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param varName compatible variable name
                template <typename NAME>
                inline   Variable(const NAME &varName) :
                String(varName)
                {
                    checkName();
                }

                virtual ~Variable() noexcept; //!< cleanup
                Y_OSTREAM_PROTO(Variable);    //!< display

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual size_t indx() const noexcept = 0; //!< \return unique index

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                const String  & key() const noexcept; //!< \return *this*


                //! \param arr array-like \return arr[indx()]
                template <typename ARRAY> inline
                typename ARRAY::Type & operator[](ARRAY &arr) const
                {
                    const size_t i = indx(); assert(i>0); assert(i<=arr.size());
                    return arr[i];
                }

                //! \param arr array-like \return arr[indx()]
                template <typename ARRAY> inline
                typename ARRAY::ConstType & operator[](const ARRAY &arr) const
                {
                    const size_t i = indx(); assert(i>0); assert(i<=arr.size());
                    return arr[i];
                }

                //! \param m matrix \return m[indx()]
                template <typename T> inline
                typename Matrix<T>::RowType & operator[](Matrix<T> &m) const
                {
                    const size_t i = indx(); assert(i>=1); assert(i<=m.rows);
                    return m[i];
                }

                //! \param m matrix \return m[indx()]
                template <typename T> inline
                const typename Matrix<T>::RowType & operator[](const Matrix<T> &m) const
                {
                    const size_t i = indx(); assert(i>=1); assert(i<=m.rows);
                    return m[i];
                }

            private:
                Y_Disable_Copy_And_Assign(Variable); //!< discard
                void checkName() const;              //!< exclude empty name
            };

          

        }

    }

}

#endif // !Y_MKL_Fit_Variable_Included
