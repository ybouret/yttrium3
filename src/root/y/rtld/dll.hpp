//! \file

#ifndef Y_RTLD_DLL_Included
#define Y_RTLD_DLL_Included 1

#include "y/string.hpp"
#include "y/object/counted.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! DLL interface, with internally reference counted handle
    //
    //
    //__________________________________________________________________________
    class DLL : public CountedObject
    {
    public:
        class Code;

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        DLL(const String &);       //!< load module
        DLL(const char * const);   //!< load module
        DLL(const DLL &) noexcept; //!< (shared) copy
        virtual ~DLL()   noexcept; //!< cleanup

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        void * query(const String &) noexcept; //!< \return symbol address
        void * query(const char * const);      //!< \return symbol address

        //! \param symbol data name \return data address
        template <typename T>
        T * queryData(const String &symbol) noexcept {
            return static_cast<T *>( query(symbol) );
        }

        //! \param symbol data name \return data address
        template <typename T>
        T * queryData(const char * const symbol) {
            return static_cast<T *>( query(symbol) );
        }

        //! \param symbol proc name \return proc address
        template <typename PROC>
        PROC queryProc(const String &symbol) noexcept
        {
            union {
                void * addr;
                PROC   proc;
            } alias = { query(symbol) };
            return alias.proc;
        }

        //! \param symbol proc name \return proc address
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
        Y_Disable_Assign(DLL); //!< discarded
        Code * const code;     //!< inner code
    public:
        const String &name;    //!< alias to module path
    };

}

#endif // !Y_RTLD_DLL_Included

