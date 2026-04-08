

//! \file

#ifndef Y_Core_String_Included
#define Y_Core_String_Included 1

#include "y/object/counted.hpp"
#include "y/type/destroy.hpp"
#include <iosfwd>

namespace Yttrium
{

    namespace Core
    {



        template <typename T>
        class String : public CountedObject
        {
        public:
            typedef CountedObject BaseClass;
            class Code;

            String();
            String(const String &);
            String(const T * const);
            String(const T * const, const size_t);
            String(const T);

            String & operator=(const String &);
            String & operator=(const T * const);
            String & operator=(const T) noexcept;

            virtual ~String() noexcept;

            String & xch(String &other) noexcept;

            std::ostream & print(std::ostream &) const;

            inline friend std::ostream & operator<<(std::ostream &os, const String &s) {
                return s.print(os);
            }

            inline friend String operator + (const String &  lhs, const String &  rhs) { return Add(lhs,rhs); }
            inline friend String operator + (const String &  lhs, const T * const rhs) { return Add(lhs,rhs); }
            inline friend String operator + (const T * const lhs, const String &  rhs) { return Add(lhs,rhs); }
            inline friend String operator + (const String &  lhs, const T         rhs) { return Add(lhs,rhs); }
            inline friend String operator + (const T         lhs, const String &  rhs) { return Add(lhs,rhs); }


            //String & operator+=(const String);



        private:
            Code * code;
            String(const T * lhs, const size_t lhsSize,
                   const T * rhs, const size_t rhsSize);
            static String Add(const String  &, const String  &);
            static String Add(const String  &, const T * const);
            static String Add(const T * const, const String  &);
            static String Add(const String  &, const T);
            static String Add(const T, const String  &);

        };
    }

}

#endif // !Y_Core_String_Included

