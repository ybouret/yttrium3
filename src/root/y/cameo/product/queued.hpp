
//! \file

#ifndef Y_Cameo_Product_Queued
#define Y_Cameo_Product_Queued 1


#include "y/cameo/multiplier.hpp"
#include "y/mkl/xreal.hpp"
#include "y/mkl/complex.hpp"
#include "y/mkl/api/fabs.hpp"


namespace Yttrium
{
    namespace Cameo
    {
        namespace Product
        {
            namespace Pith
            {
                typedef TL3(float,double,long double)                                                 StandardFloats;    //!< \return alias
                typedef TL3(XReal<float>,XReal<double>,XReal<long double>)                            ExtendedFloats;    //!< \return alias
                typedef TL3(Complex<float>,Complex<double>,Complex<long double>)                      StandardComplexes; //!< \return alias
                typedef TL3(Complex<XReal<float>>,Complex<XReal<double>>,Complex<XReal<long double>>) ExtendedComplexes; //!< \return alias

            }

            //! compute parameters for given type
            template <typename T>
            struct ByQueuedAPI
            {
                static const bool StandardF    = ( TL::IndexOf<Pith::StandardFloats,T>::Value    >= 0 ); //!< alias
                static const bool ExtendedF    = ( TL::IndexOf<Pith::ExtendedFloats,T>::Value    >= 0 ); //!< alias
                static const bool StandardC    = ( TL::IndexOf<Pith::StandardComplexes,T>::Value >= 0 ); //!< alias
                static const bool ExtendedC    = ( TL::IndexOf<Pith::ExtendedComplexes,T>::Value >= 0 ); //!< alias
                static const bool IsProper     = StandardF || ExtendedF || StandardC || ExtendedC;       //!< alias
            };

            //! helper for static check
#define Y_Cameo_Product_Queued_Check() Y_STATIC_CHECK(ByQueuedAPI<MutableType>::IsProper,BadType)


            namespace Pith
            {
                template <typename T> struct Rank
                {
                    static inline int Of(const T &f) noexcept
                    {
                        int rank = 0;
                        (void) std::frexp(f,&rank);
                        return rank;
                    }
                };

                template <typename T> struct Rank< XReal<T> >
                {
                    static inline int Of(const XReal<T> &x) noexcept
                    {
                        return x.exponent;
                    }
                };

                template <typename T> struct Rank< Complex<T> >
                {
                    static inline int Of(const Complex<T> &z) noexcept
                    {
                        const T az = MKL::Fabs<T>(z.re) + MKL::Fabs<T>(z.im);
                        return Rank<T>::Of(az);
                    }
                };

                template <typename T> static inline
                int GetRank(const T &value) noexcept
                {
                    return Rank<T>::Of(value);
                }

            }

        }

    }

}

#endif // !Y_Cameo_Product_Queued

