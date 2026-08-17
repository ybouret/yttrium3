
//! \file

#ifndef Y_Random_Uniform32_Included
#define Y_Random_Uniform32_Included 1

#include "y/ability/identifiable.hpp"
#include "y/random/coin-flip.hpp"
#include "y/mkl/xreal.hpp"
#include "y/object/counted.hpp"
#include "y/pointer/arc.hpp"
#include "y/calculus/integer-log2.hpp"

namespace Yttrium
{
    namespace Random
    {

        template <typename T> struct Alea;

        //! select T for XReal<T>
        template <typename T> struct Alea< XReal<T> > { typedef T Type; /*!< alias */ };

        //! select T for real T
        template <typename T> struct Alea { typedef T Type; /*!< alias */ };




        //______________________________________________________________________
        //
        //
        //
        //! 32-bits uniform generator
        //
        //
        //______________________________________________________________________
        class Bits : public CountedObject, public Identifiable
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            class Code;
            typedef TL::IsoFloatingPoint                               IsoFloatingPoint; //!< floating point list
            typedef TL3(XReal<float>,XReal<double>,XReal<long double>) ExtFloatingPoint; //!< extended reals list

            //! compute method
            enum Property
            {
                UseF, //!< produce iso floating point
                UseX, //!< produce ext floating point
                UseI, //!< produce integers
                UseU  //!< produce unsigned
            };

            //! property selector
            template <typename T> struct Select
            {
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
                static const bool IsIsoFloatingPoint = ( TL::IndexOf<IsoFloatingPoint,T>::Value >= 0 );
                static const bool IsExtFloatingPoint = ( TL::IndexOf<ExtFloatingPoint,T>::Value >= 0 );

                static const bool InStandardIntegers = ( TL::IndexOf<TL::StandardIntegers,T>::Value >= 0 );
                static const bool InStandardUnsigned = ( TL::IndexOf<TL::StandardUnsigned,T>::Value >= 0 );
                static const bool InPlatformIntegers = ( TL::IndexOf<TL::PlatformIntegers,T>::Value >= 0 );
                static const bool InPlatformUnsigned = ( TL::IndexOf<TL::PlatformUnsigned,T>::Value >= 0 );

                static const bool InWhateverIntegers = InStandardIntegers || InPlatformIntegers;
                static const bool InWhateverUnsigned = InStandardUnsigned || InPlatformUnsigned;

                static const size_t    One      = 1;
                static const size_t    UseF_Bit = IsIsoFloatingPoint ? (One << UseF) : 0x00;
                static const size_t    UseX_Bit = IsExtFloatingPoint ? (One << UseX) : 0x00;
                static const size_t    UseI_Bit = InWhateverIntegers ? (One << UseI) : 0x00;
                static const size_t    UseU_Bit = InWhateverUnsigned ? (One << UseU) : 0x00;
                static const size_t    Guess = UseF_Bit | UseX_Bit | UseI_Bit | UseU_Bit;
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
                static const Property  PPTY = (Property) IntegerLog2<Guess>::Value; //!< property for given type
            };




            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Bits(const uint32_t); //!< setup with max32
            virtual ~Bits()               noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual uint32_t next32() noexcept = 0; //!< \return next 32 bits word in [0:max32]

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \return float|double|long double|uint[8|16|32|64]_t
            template <typename T>  T get() noexcept;

            double operator()() noexcept; //!< \return default double precision uniform ]0:1[


            //! \return any type from Select
            template <typename T> inline T to() noexcept
            {
                static const IntToType< Select<T>::PPTY > ppty = {};
                return make<T>(ppty);
            }


            //! \return ]-1:1[ for [XReal] float|double|long double
            template <typename T> inline T symm() noexcept
            {
                typedef typename Alea<T>::Type CoreType;
                static const CoreType _1 = 1;
                const CoreType        uu = to<CoreType>();
                return _1 - (uu+uu);
            }


            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
        private:
            Y_Disable_Copy_And_Assign(Bits); //!< discarded
            Code * const code;               //!< inner code

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

            template <typename T> inline
            T make(const IntToType<UseF> &) noexcept { return get<T>(); }

            template <typename T> inline
            T make(const IntToType<UseX> &) noexcept { return get<T>(); }

            template <typename T> inline
            T make(const IntToType<UseU> &) noexcept
            {
                typedef typename IntegerFor<T>::UnsignedAlias::Type UType;
                return static_cast<T>( get<UType>() );
            }

            template <typename T> inline
            T make(const IntToType<UseI> &) noexcept
            {
                typedef typename IntegerFor<T>::UnsignedAlias::Type UType;
                return static_cast<T>( get<UType>() );
            }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
        };

        typedef ArcPtr<Bits> SharedBits; //!< alias for allocated Bits

    }
}

#endif // !Y_Random_Uniform32_Included
