
//! \file

#ifndef Y_Coven_Vector_Included
#define Y_Coven_Vector_Included 1

#include "y/coven/metrics.hpp"
#include "y/container/cxx/array.hpp"
#include "y/apex/rational.hpp"

namespace Yttrium
{

    namespace Coven
    {

        //______________________________________________________________________
        //
        //
        //
        //! Base class for vector
        //
        //
        //______________________________________________________________________
        typedef CxxArray<apz> zVector;

        //______________________________________________________________________
        //
        //
        //
        //! Vector of space
        //
        //
        //______________________________________________________________________
        class Vector : public Object, public Metrics, public zVector
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Vector(const Metrics&);    //!< setup from metrics
            virtual ~Vector() noexcept;         //!< cleanup
            Vector(const Vector &);             //!< duplicate
            Vector & operator=(const Vector &); //!< assign (with same metrics) \return *this

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! generic dot product
            /**
             \param a compatible array with same metrics
             \return a*(*this)
             */
            template <typename READABLE> inline
            apz dot( READABLE &a ) const
            {
                assert(a.size() == dimensions);
                const zVector &b = *this;
                apz            sum;
                for(size_t i=dimensions;i>0;--i) sum += b[i] * a[i];
                return sum;
            }

            //! check is A has an orthogonal component to *this
            /**
             \param Q output UNIVOCAL orthogonal vector
             \param A input compatible array
             \return true iff Q != 0
             */
            template <typename READABLE> inline
            bool keepOrtho(Vector &Q, READABLE &A) const
            {
                //--------------------------------------------------------------
                // sanity check
                //--------------------------------------------------------------
                assert(A.size() == dimensions);
                assert(Q.size() == dimensions);

                //--------------------------------------------------------------
                // compute integer, raw orthogonal component
                //--------------------------------------------------------------
                {
                    const zVector &V  = *this;
                    const apz      d  = dot(A);

                    //! Q = A - (<A|V>/V^2) V
                    for(size_t i=dimensions;i>0;--i) {
                        apz &q = (Q[i]=A[i]); q *= mod2; q -= d * V[i];
                    }
                }

                //--------------------------------------------------------------
                // check and compute
                //--------------------------------------------------------------
                return Q.univocal();
            }


            void ldz() noexcept; //!< zero everything
            void update();       //!< simple update
            bool univocal();     //!< univocal+update \return true iff not empty/nul

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t ncof; //!< number of non-zero coefs
            const apn    mod2; //!< norm2
            Vector *     next; //!< for list/pool
            Vector *     prev; //!< for list

        };


    }

}

#endif // !Y_Coven_Vector_Included

