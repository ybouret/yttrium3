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


        explicit RTTI(const String &uuid);
        virtual ~RTTI() noexcept;
        Y_OSTREAM_PROTO(RTTI);

        virtual const char * callSign() const noexcept;
        const String &       name()     const noexcept;

        bool   is(const String &) const noexcept;
        //RTTI & aka(const char * const);

        const CxxPoolOf<Alias> pool;



    private:
        Y_Disable_Copy_And_Assign(RTTI);

    };


}


#endif // !Y_System_RTTI_Included
