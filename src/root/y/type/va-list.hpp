//! \file

#ifndef Y_Type_VaList_Included
#define Y_Type_VaList_Included 1

#include "y/core/meta-max.hpp"
#include "y/calculus/alignment.hpp"
#include "y/ostream-proto.hpp"

namespace Yttrium
{


    //__________________________________________________________________________
    //
    //
    //
    //! Variable List of addresses
    //
    //
    //__________________________________________________________________________
    class VaList
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const unsigned MaxArgs = 2;  //!< maximum of extra arguments
        typedef void (VaList::*Meth)(void); //!< method pointer alias
        typedef void (*Func)(void);         //!< C function alias

        //______________________________________________________________________
        //
        //
        // Metrics
        //
        //______________________________________________________________________
        static const size_t BytesForArgs  = MaxArgs * sizeof(void*);                           //!< alias
        static const size_t BytesForFunc  = BytesForArgs + sizeof(Func);                       //!< alias
        static const size_t MethodLength  = Alignment::To<void*>::CeilOf<sizeof(Meth)>::Value; //!< alias
        static const size_t BytesForMeth  = BytesForArgs + sizeof(void *) + MethodLength;      //!< alias
        static const size_t RequiredBytes = MetaMax<BytesForFunc,BytesForMeth>::Value;         //!< alias
        static const size_t RequiredWords = Alignment::WordsGEQ<RequiredBytes>::Count;         //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        VaList()  noexcept;      //!< setup empty
        ~VaList() noexcept;      //!< cleanup
        Y_OSTREAM_PROTO(VaList); //!< display

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        size_t   usedBytes() const noexcept; //!< \return used bytes
        size_t   freeBytes() const noexcept; //!< \return free bytes
        size_t   codeBytes() const noexcept; //!< \return bytes still containing code



        //! pack an argument address \param args argument to pack
        template <typename T> inline
        VaList & operator<<(T &args) {
            return record(&args);
        }


        //! pack a C-style function address \param cfunction function address
        template <typename CFUNCTION>
        VaList & operator()(CFUNCTION cfunction)
        {
            assert(0!=cfunction);
            union {
                CFUNCTION func;
                void *    addr;
            } alias =  { cfunction };
            assert(0!=alias.addr);
            return record(alias.addr);
        }

        //! pack host+meth \param host object \param meth method
        template <typename OBJECT, typename METHOD> inline
        VaList & operator()(OBJECT &host, METHOD meth)
        {
            return record(&host).save(meth);
        }

        //! unpack data \return cast a previously stored args
        template <typename T> inline
        T & as() noexcept
        {
            return *static_cast<T*>( unpack() );
        }

        //! unpack a C-style function \return cast of previously stored function address
        template <typename CFUNCTION> inline
        CFUNCTION func()
        {
            union {
                void *    addr;
                CFUNCTION func;
            } alias = { unpack() }; assert(0!=alias.func);
            return alias.func;
        }


        //! unpack a memthod pointer \return cat of previously stored method pointer
        template <typename METHOD> inline
        METHOD meth() noexcept
        {
            assert(sizeof(METHOD)==sizeof(Meth));
            union { METHOD user; } alias = { 0 };
            mquery(&alias);
            return alias.user;
        }

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
    private:
        Y_Disable_Copy_And_Assign(VaList);
        uint8_t *          wptr;
        uint8_t *          rptr;
        uint8_t * const    data;
        void *             wksp[RequiredWords];
        
        void   * unpack()                   noexcept; //!< \return decoded address
        VaList & record(const void * const) noexcept; //!< \return *this with encoded address
        VaList & mwrite(const void * const) noexcept; //!< \return *this with written method
        void     mquery(void * const)       noexcept; //!< decode method at given address


        template <typename METHOD> inline
        VaList & save(METHOD method) noexcept
        {
            assert(method); assert(sizeof(METHOD)==sizeof(Meth));
            union { METHOD meth; } alias =  { method };
            return mwrite(&alias);
        }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)



    };





}



#endif // !Y_Type_VaList_Included

