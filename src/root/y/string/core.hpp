

//! \file

#ifndef Y_Core_String_Included
#define Y_Core_String_Included 1

#include "y/object/counted.hpp"
#include "y/type/destroy.hpp"
#include "y/type/with-at-least.hpp"
#include "y/container/writable.hpp"
#include "y/type/sign.hpp"
#include <iosfwd>

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //! how to initialize zeroed strings when required
    //
    //__________________________________________________________________________
    enum StringInit
    {
        InitEmptyString, //!< size = 0
        InitBlankString  //!< size = requested
    };

    namespace Core
    {

        //______________________________________________________________________
        //
        //
        //
        //! String of given type
        //
        //
        //______________________________________________________________________
        template <typename T>
        class String : public CountedObject, public Writable<T>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef CountedObject BaseClass; //!< alias
            Y_Args_Declare(T,Type);          //!< aliases
            class Code;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            String();                              //!< setup empty with minimal content
            String(const String &);                //!< duplicate
            String(const T * const);               //!< duplicate
            String(const T * const, const size_t); //!< duplicate
            String(const T);                       //!< duplicate
            String(const WithAtLeast_ &, const size_t, const StringInit); //!< setup (with zeros)

            String & operator=(const String &);   //!< assign \return *this
            String & operator=(const T * const);  //!< assign \return *this
            String & operator=(const T) noexcept; //!< assign \return *this

            virtual ~String() noexcept; //!< cleanup


            //! display
            inline friend std::ostream & operator<<(std::ostream &os, const String &s) {
                return s.print(os);
            }

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual size_t size()     const noexcept;
            virtual size_t capacity() const noexcept;
            virtual void   popTail() noexcept;
            virtual void   popHead() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            String &       xch(String &)      noexcept; //!< no-throw exchange \return *this
            std::ostream & print(std::ostream &) const; //!< print \return output stream
            String &       reverse()          noexcept; //!< reverse content \return *this, reversed

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            inline friend String operator + (const String &  lhs, const String &  rhs) { return Add(lhs,rhs); }
            inline friend String operator + (const String &  lhs, const T * const rhs) { return Add(lhs,rhs); }
            inline friend String operator + (const T * const lhs, const String &  rhs) { return Add(lhs,rhs); }
            inline friend String operator + (const String &  lhs, const T         rhs) { return Add(lhs,rhs); }
            inline friend String operator + (const T         lhs, const String &  rhs) { return Add(lhs,rhs); }


            String & operator+=(const String &);
            String & operator+=(const T * const);
            String & operator+=(const T);
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
#define Y_String_Cmp(OP,EXPR) \
inline friend bool operator OP (const String  & lhs, const String  & rhs) noexcept { return Cmp(lhs,rhs) EXPR; } \
inline friend bool operator OP (const String  & lhs, const T * const rhs) noexcept { return Cmp(lhs,rhs) EXPR; } \
inline friend bool operator OP (const T * const lhs, const String  & rhs) noexcept { return Cmp(lhs,rhs) EXPR; } \
inline friend bool operator OP (const String  & lhs, const T         rhs) noexcept { return Cmp(lhs,rhs) EXPR; } \
inline friend bool operator OP (const T         lhs, const String  & rhs) noexcept { return Cmp(lhs,rhs) EXPR; }


            Y_String_Cmp(==,  == __Zero__ )
            Y_String_Cmp(!=,  != __Zero__ )
            Y_String_Cmp(<,   ==  Negative)
            Y_String_Cmp(>,   ==  Positive)
            Y_String_Cmp(<=,  !=  Positive)
            Y_String_Cmp(>=,  !=  Negative)


#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)



        private:
            Code * code; //!< inner code
            
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            Y_Readable_Decl();

            // for additions
            String(const T * const lhs, const size_t lhsSize,
                   const T * const rhs, const size_t rhsSize);
            static String Add(const String  &, const String  &);
            static String Add(const String  &, const T * const);
            static String Add(const T * const, const String  &);
            static String Add(const String  &, const T);
            static String Add(const T, const String  &);

            // for comparisons
            static SignType Cmp(const T * lhs, const size_t lhsSize,
                                const T * rhs, const size_t rhsSize) noexcept;

            static SignType Cmp(const String  &, const String  &) noexcept;
            static SignType Cmp(const String  &, const T * const) noexcept;
            static SignType Cmp(const T * const, const String  &) noexcept;
            static SignType Cmp(const String  &, const T        ) noexcept;
            static SignType Cmp(const T,         const String  &) noexcept;


#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        };
    }

}

#endif // !Y_Core_String_Included

