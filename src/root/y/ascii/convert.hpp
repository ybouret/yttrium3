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

        struct Convert
        {
            static const char * const CallSign;

            static uint64_t ToU64(const char *       text,
                                  const size_t       size,
                                  const char * const varName,
                                  const char * const varPart);

            static uint64_t ToI64(const char *       text,
                                  const size_t       size,
                                  const char * const varName,
                                  const char * const varPart);


            template <typename T> static inline
            T ToIntegral(const char *       text,
                         const size_t       size,
                         const char * const varName,
                         const char * const varPart)
            {
                static const IntToType< IsSignedInt<T>::Value > Choice = {};
                return ToIntegral<T>(Choice,text,size,varName,varPart);
            }

            static apn ToDecAPN(const char *       text,
                                const size_t       size,
                                const char * const varName,
                                const char * const varPart);

            static apn ToHexAPN(const char *       text,
                                const size_t       size,
                                const char * const varName,
                                const char * const varPart);

            static apn ToAPN(const char * const text,
                             const size_t       size,
                             const char * const varName,
                             const char * const varPart);

        private:
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
        };

    }

}

#endif // !Y_ASCII_Convert_Included
