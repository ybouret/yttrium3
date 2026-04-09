
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
        //__________________________________________________________________________
        //
        //
        //! common functions for Stride
        //
        //__________________________________________________________________________
        struct StrideIO
        {
            static Memory::Allocator & AllocatorInstance();          //!< \return pooled allocator
            static Memory::Allocator & AllocatorLocation() noexcept; //!< \return pooled allocator
        };


        //! helper to setup Stride memory
#define Y_Stride_Acquire()  \
/**/    count(capacity+1),  \
/**/    bytes(0),           \
/**/    entry( StrideIO::AllocatorInstance().acquireAs<T>(Coerce(count),Coerce(bytes)) ), \
/**/    cxx(entry-1)

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


            //! setup with buffer \param buffer user data \param buflen data size
            explicit Stride(const T * const buffer,
                            const size_t    buflen) :
            capacity( buflen ),
            size( capacity ),
            Y_Stride_Acquire()
            {
                Y_Stride_Upgrade();
                assert(!(0==buffer&&buflen>0));
                memcpy(entry,buffer,size*sizeof(T));
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
                static Memory::Allocator &mgr = StrideIO::AllocatorLocation();
                clear(); assert(0==size);
                Coerce(capacity) = 0;
                mgr.releaseAs(Coerce(entry),Coerce(count),Coerce(bytes));
            }


            //! display, mostly for Debug
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

            //! catenate \param text data \param tlen data size
            inline void cat(const T * const text, const size_t tlen) noexcept
            {
                assert(sanity());
                assert(tlen == StringLength(text));
                assert(size+tlen<=capacity);
                memmove(entry+size,text,tlen*sizeof(T));
                Coerce(size) += tlen;
                assert(sanity());
            }

            inline void pre(const T * const text, const size_t tlen) noexcept
            {
                assert(sanity());
                assert(tlen == StringLength(text));
                assert(size+tlen<=capacity);

                assert(sanity());
            }

            //! clear content
            inline void clear() noexcept
            {
                assert( sanity() );
                memset(entry,0,size*sizeof(T));
                Coerce(size) = 0;
                assert(sanity());
            }

            //! trim chars \param n chars to trim
            inline void trim(size_t n) noexcept
            {
                assert( sanity() );
                if(n>=size) return clear();
                while(n-- > 0)
                {
                    assert(size>0);
                    entry[--Coerce(size)] = 0;
                    assert(sanity());
                }
            }

            //! skip chars \param n chars to skip
            inline void skip(const size_t n) noexcept
            {
                assert( sanity() );
                if(n>=size) return clear();
                memmove(entry,entry+n,(Coerce(size) -= n)*sizeof(T));
                memset(entry+size,0,n*sizeof(T));
                assert( sanity() );
            }

            //! copy content \param other other.size<=capacity
            inline void copy(const Stride &other) noexcept
            {
                assert(this != &other);
                assert( sanity() );
                assert( other.sanity() );
                assert(capacity>=other.size);

                memmove(entry,other.entry,(Coerce(size)=other.size)*sizeof(T));
                memset(entry+size,0,(count-size)*sizeof(T));

                assert( sanity() );
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
            T *   const  cxx;      //!< entry-1

        private:
            Y_Disable_Assign(Stride); //!< discarded

        };

    }

}

#endif // !Y_String_Stride_Included

