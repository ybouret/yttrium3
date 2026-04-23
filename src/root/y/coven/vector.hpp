
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
            Y_OSTREAM_PROTO(Vector);            //!< display

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! strategic comparison
            /**
             - first compare by INCREASING ncof to detect orthogonality as fast as possible
             - then  compare by INCREASING mod2 to produce smaller coefficients
             - and then by LEXICOGRAPHIC order to ensure uniqueness
             \return comparison value
             **/
            static SignType Compare(const Vector & , const Vector & ) noexcept;
            
            //! optimized dot product
            /**
             \param a compatible array with same metrics
             \return a*(*this)
             */
            template <typename READABLE> inline
            apz dot( READABLE &a ) const
            {
                assert(a.size() == dimension);
                const zVector &b = *this;
                apz            sum;
                for(size_t i=dimension;i>0;--i)
                {
                    const apz p = b[i]*a[i];
                    switch(p.s)
                    {
                        case __Zero__: continue;
                        case Positive: sum += p.n; continue;
                        case Negative: sum -= p.n; continue;
                    }
                }
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
                assert(A.size() == dimension);
                assert(Q.size() == dimension);

                //--------------------------------------------------------------
                // compute integer, raw orthogonal component
                //--------------------------------------------------------------
                {
                    const zVector &V  = *this;
                    const apz      d  = dot(A);

                    //! Q = A - (<A|V>/V^2) V
                    for(size_t i=dimension;i>0;--i) {
                        apz &q = (Q[i]=A[i]); q *= mod2; q -= d * V[i];
                    }
                }

                //--------------------------------------------------------------
                // check and compute
                //--------------------------------------------------------------
                return Q.univocal();
            }

            //! load compatible array and check univocal
            /**
             \param A source vector
             \return true iff A  was not empty
             */
            template <typename READABLE> inline
            bool ld(READABLE &A)
            {
                assert(A.size() == dimension);
                try
                {
                    for(size_t i=dimension;i>0;--i) (*this)[i] = A[i];
                }
                catch(...) { ldz(); throw; }
                return univocal();
            }


            void exchange(Vector &) noexcept; //!< exchange contents
            void ldz()              noexcept; //!< zero everything
            void update();                    //!< simple update
            bool univocal();                  //!< univocal+update \return true iff not empty/nul

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

