//! \file

#ifndef Y_RTLD_DLL_Included
#define Y_RTLD_DLL_Included 1

#include "y/string.hpp"
#include "y/object/counted.hpp"

namespace Yttrium
{

    class DLL : public CountedObject
    {
    public:
        class Code;

        DLL(const String &);
        DLL(const char * const);
        DLL(const DLL &) noexcept;
        virtual ~DLL()   noexcept;

        void * query(const String &symbol) noexcept;
        void * query(const char * const  );

        template <typename T>
        T * queryData(const String &symbol) noexcept {
            return static_cast<T *>( query(symbol) );
        }

        template <typename T>
        T * queryData(const char * const symbol) {
            return static_cast<T *>( query(symbol) );
        }

        template <typename PROC>
        PROC queryProc(const String &symbol) noexcept
        {
            union {
                void * addr;
                PROC   proc;
            } alias = { query(symbol) };
            return alias.proc;
        }

        template <typename PROC>
        PROC queryProc(const char *  const symbol) 
        {
            union {
                void * addr;
                PROC   proc;
            } alias = { query(symbol) };
            return alias.proc;
        }


    private:
        Y_Disable_Assign(DLL);
        Code * const code;
    public:
        const String &name;
    };

}

#endif // !Y_RTLD_DLL_Included

