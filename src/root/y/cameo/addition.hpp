
//! \file

#ifndef Y_Cameo_Addition_Included
#define Y_Cameo_Addition_Included 1


#include "y/cameo/sum/operating.hpp"
#include "y/mkl/api/adaptor.hpp"
#include "y/mkl/api/mod2.hpp"

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
            typedef typename  Sum::Operating<T>::Type SummatorType;                         //!< alias
            static const bool IsSummator = Y_Is_SuperSubClass_Strict(Summator<T>,Addition); //!< alias
            Y_Args_Declare(T,Type);                                                         //!< aliases

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

            //! set \param param value \return *this
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
            // Methods
            //
            //__________________________________________________________________

            //! single product addition of lhs*rhs  \param lhs lhs \param rhs
            template <typename LHS, typename RHS> inline
            void addProd(LHS &lhs, RHS &rhs)
            {
                static const TypeToType<T> Mine = { };
                ConstType prod = MKL::AdaptedTo(Mine,lhs) * MKL::AdaptedTo(Mine,rhs);
                this->add(prod);
            }

            //! single product subtraction of lhs*rhs  \param lhs lhs \param rhs
            template <typename LHS, typename RHS> inline
            void subProd(LHS &lhs, RHS &rhs)
            {
                static const TypeToType<T> Mine = { };
                ConstType prod = (MKL::AdaptedTo(Mine,lhs) * MKL::AdaptedTo(Mine,rhs));
                this->sub(prod);
            }

            //! dot product of same-sized arrays
            /**
             \param lhs array
             \param rhs array
             \return <lhs|rhs>
             */
            template <typename LARRAY, typename RARRAY> inline
            Type dot(LARRAY &lhs, RARRAY &rhs)
            {
                assert(lhs.size()==rhs.size());
                SummatorType &self = *this;
                self.ldz();
                for(size_t i=lhs.size();i>0;--i) addProd(lhs[i],rhs[i]);
                return self();
            }

            //! dot product minus value of same-sized arrays
            /**
             \param lhs array
             \param rhs array
             \param arg subtracted
             \return <lhs|rhs> - arg
             */
            template <typename LARRAY, typename RARRAY, typename ARG> inline
            Type dotsub(LARRAY &lhs, RARRAY &rhs, ARG &arg)
            {
                assert(lhs.size()==rhs.size());
                SummatorType &self = *this;
                self.ldz();
                for(size_t i=lhs.size();i>0;--i) addProd(lhs[i],rhs[i]);
                self -= arg;
                return self();
            }

            //! mod2 of array whose scalar type is Type \param arr compatible array \return |arr|^2
            template <typename ARRAY> inline
            Type mod2(ARRAY &arr)
            {
                SummatorType &self = *this;
                self.ldz();
                for(size_t i=arr.size();i>0;--i) self += MKL::Mod2<typename ARRAY::Type>( arr[i] );
                return self();
            }

            inline Type sum(ParamType a, ParamType b, ParamType c)
            {
                SummatorType &self = *this;
                self.ldz();
                self << a << b << c;
                return self();
            }

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



