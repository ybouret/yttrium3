
//! \file

#ifndef Y_Random_Fill_Included
#define Y_Random_Fill_Included 1

#include "y/hide.hpp"
#include "y/config/compiler.h"
#include <cassert>

namespace Yttrium
{
    namespace Random
    {
        //______________________________________________________________________
        //
        //! Fill a block with random data
        /**
         \param ran  posseses a in<uint8_t>(umin,umax) method
         \param addr data address
         \param size data size
         \param umin minimum byte value
         \param umax maximum byte value
         */
        //______________________________________________________________________
        template <typename RAND> inline
        void * FillWith(RAND &        ran,
                        void * const  addr,
                        const size_t  size,
                        const uint8_t umin = 0,
                      const uint8_t umax = 255) noexcept
        {
            assert(!(0==addr&&size>0));
            uint8_t * const p = static_cast<uint8_t *>(addr);
            for(size_t i=0;i<size;++i)
            {
                p[i] = ran.template in<uint8_t>(umin,umax);
            }
            return addr;
        }

        //______________________________________________________________________
        //
        //! Fill a word with random data
        /**
         \param ran  posseses a in<uint8_t>(umin,umax) method
         \param word data reference
         \param umin minimum byte value
         \param umax maximum byte value
         */
        //______________________________________________________________________
        template <typename RAND, typename T> inline
        void FillWord(RAND &ran, T &word, const uint8_t umin = 0, const uint8_t umax=255) noexcept
        {
            uint8_t * const p = static_cast<uint8_t *>( Hide::Address(&word) );
            for(unsigned i=0;i<sizeof(T);++i)
            {
                p[i] = ran.template in<uint8_t>(umin,umax);
            }
        }


        //______________________________________________________________________
        //
        //! Fill a range with random data
        /**
         \param ran  posseses a in<uint8_t>(umin,umax) method
         \param a    first iterator
         \param n    number of elements
         \param umin minimum byte value
         \param umax maximum byte value
         */
        //______________________________________________________________________
        template <typename RAND, typename ITER> inline
        void Fill(RAND &ran, ITER a, size_t n, const uint8_t umin = 0, const uint8_t umax=255) noexcept
        {
            while(n-- > 0) FillWord(ran,*(a++),umin,umax);
        }


    }
}

#endif // !Y_Random_Fill_Included

