//! \file

#ifndef Y_Type_VaList_Included
#define Y_Type_VaList_Included 1

#include "y/core/meta-max.hpp"
#include "y/calculus/alignment.hpp"
#include "y/ostream-proto.hpp"
#include "y/calculus/meta2.hpp"

namespace Yttrium
{

    class VaArgs; // forward declaration

    //! helper to construct empty VaList
#define Y_VaList() wptr(0), data(0), wksp()

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
        static const unsigned MinArgs = 3;  //!< minimum extra arguments
        typedef void (VaList::*Meth)(void); //!< method pointer alias
        typedef void (*Func)(void);         //!< C function alias

        //______________________________________________________________________
        //
        //
        // Metrics
        //
        //______________________________________________________________________
        static const size_t PrologLength  = 2*sizeof(void*);                                   //!< size for inner pointers
        static const size_t MethodLength  = Alignment::To<void*>::CeilOf<sizeof(Meth)>::Value; //!< size for a method pointer
        static const size_t InvokeLength  = sizeof(void*) + MethodLength;                      //!< object pointer+method pointer
        static const size_t SummonLength  = sizeof(Func);            //!< sizeof function
        static const size_t MinArgsBytes  = MinArgs * sizeof(void*); //!< bytes for arguments address
        static const size_t InvokeNeeded  = InvokeLength + MinArgsBytes;
        static const size_t SummonNeeded  = SummonLength + MinArgsBytes;

        static const size_t RequiredTotal = MetaMax<InvokeNeeded,SummonNeeded>::Value ;                     //!< alias
        static const size_t RequiredBytes = (MetaNextPowerOfTwo<RequiredTotal>::Value << 1) - PrologLength; //!< for alignement
        static const size_t RequiredWords = Alignment::WordsGEQ<RequiredBytes>::Count;                      //!< alias
        static const size_t MaxInvokeArgs = (RequiredBytes-InvokeLength)/sizeof(void*);
        static const size_t MaxSummonArgs = (RequiredBytes-SummonLength)/sizeof(void*);
        
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        VaList()  noexcept;      //!< setup empty
        ~VaList() noexcept;      //!< cleanup
        Y_OSTREAM_PROTO(VaList); //!< display

        //! setup \param cfunction initialized with cfunction
        template <typename CFUNCTION> inline
        VaList(CFUNCTION cfunction) noexcept :
        Y_VaList()
        {
            onInit()(cfunction);
        }

        //! setup \param host object \param meth method 
        template <typename OBJECT, typename METHOD> inline
        VaList(OBJECT &host, METHOD meth) noexcept :
        Y_VaList()
        {
            onInit()(host,meth);
        }

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        size_t   usedBytes() const noexcept; //!< \return used bytes
        size_t   freeBytes() const noexcept; //!< \return free bytes



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




    private:
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
        Y_Disable_Copy_And_Assign(VaList);
        friend class VaArgs;
        uint8_t *          wptr;
        uint8_t * const    data;
        void *             wksp[RequiredWords];

        VaList & onInit() noexcept;
        VaList & record(const void * const) noexcept; //!< \return *this with encoded address
        VaList & mwrite(const void * const) noexcept; //!< \return *this with written method
       

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

