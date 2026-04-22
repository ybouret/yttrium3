//! \file

#ifndef Y_Sequence_Included
#define Y_Sequence_Included 1

#include "y/type/args.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Sequence interface
    //
    //
    //__________________________________________________________________________
    template <typename T, typename WRITABLE>
    class Sequence : public WRITABLE
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Declare(T,Type); //!< aliases

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        inline explicit Sequence() noexcept : WRITABLE() {} //!< setup
        inline virtual ~Sequence() noexcept {}              //!< cleanup

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual void pushTail(ParamType) = 0; //!< push new element at tail
        virtual void pushHead(ParamType) = 0; //!< push new element at head

        virtual void popTail() noexcept = 0; //!< remove element at tail
        virtual void popHead() noexcept = 0; //!< remove element at head


        
    private:
        Y_Disable_Copy_And_Assign(Sequence); //!< discarded

        virtual ConstType & getTail() const noexcept = 0; //!< \return tail element
        virtual ConstType & getHead() const noexcept = 0; //!< \return head element

    public:
        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        inline ConstType & head() const noexcept { assert( this->size() > 0); return         getHead(); } //!< \return head
        inline ConstType & tail() const noexcept { assert( this->size() > 0); return         getTail(); } //!< \return tail
        inline Type &      head()       noexcept { assert( this->size() > 0); return (Type &)getHead(); } //!< \return head
        inline Type &      tail()       noexcept { assert( this->size() > 0); return (Type &)getTail(); } //!< \return tail


        inline Sequence & operator<<(ParamType value) { pushTail(value); return *this; } //!< \param value pushed at tail \return *this
        inline Sequence & operator>>(ParamType value) { pushHead(value); return *this; } //!< \param value pushed at head \return *this

    };
}


#endif // !Y_Sequence_Included

