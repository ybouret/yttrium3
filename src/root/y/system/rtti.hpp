//! \file

#ifndef Y_System_RTTI_Included
#define Y_System_RTTI_Included 1

#include "y/string.hpp"

#include "y/core/pool/cxx.hpp"
#include "y/ability/identifiable.hpp"
#include <typeinfo>

namespace Yttrium
{



    class RTTI : public CountedObject, public Identifiable
    {
    public:
        static const char * const CallSign;
        class Table;

        class Alias : public String
        {
        public:
            explicit Alias(const String &uuid);
            virtual ~Alias() noexcept;

            Alias * next;
        private:
            Y_Disable_Copy_And_Assign(Alias);
        };


        virtual ~RTTI() noexcept;
        Y_OSTREAM_PROTO(RTTI);

        virtual const char * callSign() const noexcept;

        const String &       name()     const noexcept;
        bool   is(const String &) const noexcept;
        RTTI & aka(const String &);
        RTTI & aka(const char * const);

        const CxxPoolOf<Alias> pool;

        static RTTI & Of(const std::type_info &);

        template <typename T> static inline
        RTTI & Of()
        {
            return Of( typeid(T) );
        }

        template <typename T> static inline
        RTTI & Make(const String &uid)
        {
            return Of( typeid(T) ).aka(uid);
        }

        template <typename T> static inline
        RTTI & Make(const char * const uid)
        {
            return Of( typeid(T) ).aka(uid);
        }

        template <typename T> static inline
        const String & Name()
        {
            return Of<T>().name();
        }

        template <typename T> static inline
        const String CXX()
        {
            const String res = Name<T>();
            return '<' + res + '>';
        }




    private:
        explicit RTTI(const String &uuid);
        Y_Disable_Copy_And_Assign(RTTI);
        friend class Table;
    };


}


#endif // !Y_System_RTTI_Included
