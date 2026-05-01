#include "y/jive/pattern/leading.hpp"
#include "y/calculus/non-zero-bits.hpp"
#include "y/ascii/printable.hpp"
#include <cstring>
#include <iostream>
#include <cassert>

namespace Yttrium
{
    namespace Jive
    {

        Leading & Leading:: ldz() noexcept
        {
            memset(data,0,sizeof(data));
            return *this;
        }

        Leading:: ~Leading() noexcept
        {
            ldz();
        }

        Leading:: Leading() noexcept : data()
        {
            ldz();
        }

        Leading:: Leading(const Leading &other) noexcept :
        data()
        {
            memcpy(data,other.data,sizeof(data));
        }

        Leading & Leading::operator=(const Leading &other) noexcept
        {
            memmove(data,other.data,sizeof(data));
            return *this;
        }

        size_t Leading:: size() const noexcept
        {
            size_t res = 0;
            for(size_t i=0;i<32;++i)
            {
                res += Calculus::NonZeroBits::For(data[i]);
            }
            return res;
        }

        const uint8_t Leading:: Bit[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
        const uint8_t Leading:: Msk[8] = { 255-1, 255-2, 255-4, 255-8, 255-16, 255-32, 255-64, 255-128 };

        Leading & Leading:: operator << (const uint8_t b) noexcept
        {
            return set(b);
        }

        Leading & Leading:: operator-=(const uint8_t b) noexcept
        {
            return clr(b);
        }

        Leading & Leading:: operator-=(const Leading &other)   noexcept
        {
            for(unsigned i=0;i<256;++i)
            {
                const uint8_t b = (uint8_t)i;
                if(other.get(b)) clr(b);
            }
            return *this;
        }


        Leading & Leading:: operator << (const Leading &other) noexcept
        {
            for(unsigned i=0;i<32;++i)
            {
                data[i] |= other.data[i];
            }
            return *this;
        }


        bool Leading:: get(const uint8_t b) const noexcept
        {
            return 0 != ( data[b>>3] & Bit[b&7] );
        }

        Leading & Leading:: set(const uint8_t b) noexcept
        {
            data[b>>3] |= Bit[b&7];
            return *this;
        }

        Leading & Leading:: clr(const uint8_t b) noexcept
        {
            data[b>>3] &= Msk[b&7];
            return *this;
        }


        static inline void display(const Within &w, void * const args)
        {
            assert(args);
            std::ostream & os = * static_cast<std::ostream *>(args);
            os << w;
        }
        std::ostream & operator<<(std::ostream &os, const Leading &self)
        {
            os << '#' << '{';
            self.forEach(display,&os);
            os << '}' << '=' << self.size();
            return os;
        }


        Leading & Leading:: set(const Within w) noexcept
        {
            unsigned lower = w.lower;
            unsigned upper = w.upper;
            for(unsigned i=lower;i<=upper;++i) set( (uint8_t)i );
            return *this;
        }

        Leading & Leading:: all() noexcept
        {
            memset(data,0xff,sizeof(data));
            return *this;
        }




        void Leading:: forEach( void (*proc)(const Within &, void * const), void * const args ) const
        {
            assert(proc);
            unsigned curr = 0;
            while(curr<256)
            {
                if( ! get( (uint8_t) curr) )
                {
                    ++curr;
                    continue;
                }
                const uint8_t lower = (uint8_t) curr;
                while(curr<256 && get( (uint8_t) curr) )
                {
                    ++curr;
                }
                const uint8_t upper = (uint8_t)(curr-1);
                const Within  w(lower,upper);
                proc(w,args);
            }


        }

    }

}
