//! \file

#ifndef Y_ASCII_Convert_Included
#define Y_ASCII_Convert_Included 1

#include "y/type/ints.hpp"
#include "y/int-to-type.hpp"
#include "y/type/traits.hpp"
#include "y/exception.hpp"
#include "y/apex/integer.hpp"

namespace Yttrium
{

    namespace ASCII
    {
        //______________________________________________________________________
        //
        //
        //
        //! ASCII conversions
        //
        //
        //______________________________________________________________________
        struct Convert
        {
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "ASCII::Convert"

            enum Category
            {
                UseIP,
                UseAP,
                UseFP,
                UseNA
            };

            template <typename T>
            struct CategoryOf
            {
                static const bool      MatchIP = TypeTraits<T>::IsIntegral;
                static const bool      MatchAP = IsSameType<T,apn>::Value || IsSameType<T,apz>::Value;
                static const bool      MatchFP = TypeTraits<T>::IsIsoFloatingPoint;
                static const Category  Value = MatchIP ? UseIP : ( MatchAP ? UseAP : ( MatchFP ? UseFP : UseNA)  );
            };



            //__________________________________________________________________
            //
            //
            //! conversion to uint64_t
            /**
             \param text ascii string text != NULL, with optional hexa
             \param size text length, size>0
             \param varName optional var name \param varPart optional var part
             \return parsed uint64_t
             */
            //__________________________________________________________________
            static uint64_t ToU64(const char *       text,
                                  const size_t       size);

            //__________________________________________________________________
            //
            //
            //! conversion to int64_t
            /**
             \param text ascii string text != NULL
             \param size text length, size>0
             \param varName optional var name \param varPart optional var part
             \return parsed int64_t
             */
            //__________________________________________________________________
            static int64_t ToI64(const char *       text,
                                 const size_t       size);

            //__________________________________________________________________
            //
            //
            //! conversion to any integral
            /**
             \param text ascii string text != NULL, with optional hexa prefix
             \param size text length, size>0
             \param varName optional var name \param varPart optional var part
             \return parsed integral
             */
            //
            //__________________________________________________________________
            template <typename T> static inline
            T ToIntegral(const char *       text,
                         const size_t       size)
            {
                static const IntToType< IsSignedInt<T>::Value > Choice = {};
                return ToIntegral<T>(Choice,text,size);
            }

            //__________________________________________________________________
            //
            //
            //! decimal string to apn
            /**
             \param text ascii string text != NULL
             \param size text length, size>0
             \param varName optional var name \param varPart optional var part
             \return parsed apn
             */
            //__________________________________________________________________
            static apn ToDecAPN(const char *       text,
                                const size_t       size);

            //__________________________________________________________________
            //
            //
            //! hexadecimal string to apn
            /**
             \param text ascii string text != NULL
             \param size text length, size>0
             \param varName optional var name \param varPart optional var part
             \return parsed apn
             */
            //__________________________________________________________________
            static apn ToHexAPN(const char *       text,
                                const size_t       size);

            //__________________________________________________________________
            //
            //
            //! convert to apn
            /**
             \param text ascii string text != NULL, with optional hexa prefix
             \param size text length, size>0
             \param varName optional var name \param varPart optional var part
             \return parsed apn
             */
            //__________________________________________________________________
            static apn ToAPN(const char * const text,
                             const size_t       size);

            //__________________________________________________________________
            //
            //
            //! convert to apz
            /**
             \param text ascii string text != NULL
             \param size text length, size>0
             \param varName optional var name \param varPart optional var part
             \return parsed apz
             */
            //__________________________________________________________________
            static apz ToAPZ(const char * const text,
                             const size_t       size);


            template <typename T> static
            T ToAP(const char * const text,
                   const size_t       size);

            //__________________________________________________________________
            //
            //
            //! convert to [float|double|long double]
            /**
             \param text ascii string text != NULL
             \param size text length, size>0
             \param varName optional var name \param varPart optional var part
             \return parsed floating point value
             */
            //__________________________________________________________________
            template <typename T> static
            T ToFP(const char * const text,
                   const size_t       size);



            //__________________________________________________________________
            //
            //
            //
            //__________________________________________________________________
            template <typename T> static inline
            T To(const char * const text,
                 const size_t       size,
                 const char * const varName,
                 const char * const varPart)
            {
                static const IntToType< CategoryOf<T>::Value > Selected = {};
                try
                {
                    return To<T>(Selected,text,size);
                }
                catch(Exception &excp)
                {
                    throw excp.signedFor(varName,varPart);
                }
                catch(...)
                {
                    throw;
                }

            }

        private:

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

            template <typename T> static inline
            T To(const IntToType<UseIP> &,
                 const char * const text,
                 const size_t       size)
            {
                return ToIntegral<T>(text,size);
            }


            template <typename T> static inline
            T To(const IntToType<UseAP> &,
                 const char * const text,
                 const size_t       size)
            {
                return ToAP<T>(text,size);
            }

            template <typename T> static inline
            T To(const IntToType<UseFP> &,
                 const char * const text,
                 const size_t       size)
            {
                return ToFP<T>(text,size);
            }


            static bool HasHexaPrefix(const char * const text, const size_t size) noexcept;

            template <typename T> static inline
            T ToIntegral(const IntToType<false> &,
                         const char *        text,
                         const size_t        size)
            {
                static const uint64_t MaxValue = IntegerFor<T>::Maximum;
                const uint64_t        value    = ToU64(text,size);
                if(value>MaxValue) throw Specific::Exception(CallSign,"overflow for unsigned integral");
                return (T)value;
            }

            template <typename T> static inline
            T ToIntegral(const IntToType<true> &,
                         const char *        text,
                         const size_t        size)
            {

                static const int64_t MaxValue = IntegerFor<T>::Maximum;
                static const int64_t MinValue = IntegerFor<T>::Minimum;
                const int64_t        value    = ToI64(text,size);
                if(value>MaxValue||value<MinValue)
                    throw Specific::Exception(CallSign,"overflow for signed integeral");
                return (T)value;
            }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
        };

    }

}

#endif // !Y_ASCII_Convert_Included
