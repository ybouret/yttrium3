
//! \file

#ifndef Y_String_Stride_Included
#define Y_String_Stride_Included 1

#include "y/memory/allocator.hpp"
#include "y/string/length.hpp"
#include "y/core/display.hpp"
#include "y/libc/block/zeroed.h"
#include <cstring>

namespace Yttrium
{

    namespace Core
    {
        //! common functions for Stride
        struct Stride
        {
            static Memory::Allocator & AllocatorInstance();          //!< \return pooled allocator
            static Memory::Allocator & AllocatorLocation() noexcept; //!< \return pooled allocator
        };
    }

    //! helper to setup Stride memory
#define Y_Stride_Acquire()  \
/**/    count(capacity+1),  \
/**/    bytes(0),           \
/**/    entry( Core::Stride::AllocatorInstance().acquireAs<T>(Coerce(count),Coerce(bytes)) )

    //! post constructor upgrade
#define Y_Stride_Upgrade() Coerce(capacity) = count-1

    //__________________________________________________________________________
    //
    //
    //
    //! Content of strings
    //
    //
    //__________________________________________________________________________
    template <typename T>
    class Stride
    {
    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup with memory \param n minimal count
        inline explicit Stride(const size_t n) :
        capacity(n),
        size(0),
        Y_Stride_Acquire()
        {
            Y_Stride_Upgrade();
        }

        //! setup with buffer \param text user data
        explicit Stride(const T * const text) :
        capacity( StringLength(text) ),
        size( capacity ),
        Y_Stride_Acquire()
        {
            Y_Stride_Upgrade();
            memcpy(entry,text,size*sizeof(T));
            assert(sanity());
        }

        //! duplicate \param s another stride
        explicit Stride(const Stride &s) :
        capacity(s.size),
        size(s.size),
        Y_Stride_Acquire()
        {
            Y_Stride_Upgrade();
            memcpy(entry,s.entry,size*sizeof(T));
            assert(sanity());
        }

        //! cleanup
        inline virtual ~Stride() noexcept
        {
            static Memory::Allocator &mgr = Core::Stride::AllocatorLocation();
            mgr.releaseAs(Coerce(entry),Coerce(count),Coerce(bytes));
            Coerce(capacity) = 0;
            Coerce(size)     = 0;
        }


        //! display
        inline friend std::ostream & operator<<(std::ostream &os, const Stride &self)
        {
            return Core::Display(os,self.entry,self.size) <<  '#' << self.size << '/' << self.capacity;
        }

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! check sanity \return true if excess memory is zeroed
        inline bool sanity() const noexcept
        {
            assert(size<=capacity);
            assert(capacity==count-1);
            return Y_TRUE == Yttrium_Zeroed(entry+size,(count-size)*sizeof(T));
        }

        //! catenate \param text data \param tlen data size \return *this
        inline Stride & cat(const T * const text, const size_t tlen) noexcept
        {
            assert(sanity());
            assert(tlen == StringLength(text));
            assert(size+tlen<=capacity);
            memcpy(entry+size,text,tlen*sizeof(T));
            Coerce(size) += tlen;
            assert(sanity());
            return *this;
        }

        //! clear content \return *this
        inline Stride & clear() noexcept
        {
            assert( sanity() );
            memset(entry,0,size*sizeof(T));
            Coerce(size) = 0;
            assert(sanity());
            return *this;
        }

        //! trim chars \param n chars to trim \return *this
        inline Stride & trim(size_t n) noexcept
        {
            assert( sanity() );
            if(n>=size) return clear();
            while(n-- > 0)
            {
                assert(size>0);
                entry[--Coerce(size)] = 0;
                assert(sanity());
            }
            return *this;
        }

        //! skip chars \param n chars to skip \return *this
        inline Stride & skip(const size_t n) noexcept
        {
            assert( sanity() );
            if(n>=size) return clear();
            memmove(entry,entry+n,(Coerce(size) -= n)*sizeof(T));
            memset(entry+size,0,n*sizeof(T));
            assert( sanity() );
            return *this;
        }

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        const size_t capacity; //!< maximum number of chars
        const size_t size;     //!< current number of chars
        const size_t count;    //!< capacity+1
        const size_t bytes;    //!< count * sizeof(chars)
        T *   const  entry;    //!< chars

    private:
        Y_Disable_Assign(Stride); //!< discarded

    };

}

#endif // !Y_String_Stride_Included

