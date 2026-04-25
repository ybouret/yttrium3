//! \file

#ifndef Y_ASCII_Convert_Included
#define Y_ASCII_Convert_Included 1

#include "y/type/ints.hpp"
#include "y/int-to-type.hpp"
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
                                  const size_t       size,
                                  const char * const varName,
                                  const char * const varPart);

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
                                 const size_t       size,
                                 const char * const varName,
                                 const char * const varPart);

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
                         const size_t       size,
                         const char * const varName,
                         const char * const varPart)
            {
                static const IntToType< IsSignedInt<T>::Value > Choice = {};
                return ToIntegral<T>(Choice,text,size,varName,varPart);
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
                                const size_t       size,
                                const char * const varName,
                                const char * const varPart);

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
                                const size_t       size,
                                const char * const varName,
                                const char * const varPart);

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
                             const size_t       size,
                             const char * const varName,
                             const char * const varPart);

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
                             const size_t       size,
                             const char * const varName,
                             const char * const varPart);


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
                   const size_t       size,
                   const char * const varName,
                   const char * const varPart);


        private:

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            static bool HasHexaPrefix(const char * const text, const size_t size) noexcept;

            template <typename T> static inline
            T ToIntegral(const IntToType<false> &,
                         const char *        text,
                         const size_t        size,
                         const char * const  varName,
                         const char * const  varPart)
            {
                static const uint64_t MaxValue = IntegerFor<T>::Maximium;
                const uint64_t        value    = ToU64(text,size,varName,varPart);
                if(value>MaxValue) {
                    Specific::Exception excp(CallSign,"overflow for unsigned integral");
                    throw excp.signedFor(varName,varPart);
                }
                return (T)value;
            }

            template <typename T> static inline
            T ToIntegral(const IntToType<true> &,
                         const char *        text,
                         const size_t        size,
                         const char * const  varName,
                         const char * const  varPart)
            {

                static const int64_t MaxValue = IntegerFor<T>::Maximium;
                static const int64_t MinValue = IntegerFor<T>::Minimum;
                const int64_t        value    = ToI64(text,size,varName,varPart);
                if(value>MaxValue||value<MinValue) {
                    Specific::Exception excp(CallSign,"overflow for signed integeral");
                    throw excp.signedFor(varName,varPart);
                }
                return (T)value;
            }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
        };

    }

}

#endif // !Y_ASCII_Convert_Included
