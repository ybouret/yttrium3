//! \file

#ifndef Y_Concurrent_Splitting_Tile1D_Included
#define Y_Concurrent_Splitting_Tile1D_Included 1

#include "y/concurrent/member.hpp"
#include <iostream>

namespace Yttrium
{
    namespace Concurrent
    {

        namespace Splitting
        {

            template <typename T>
            class Tile1D : public Member
            {
            public:
                static const T _1 = 1;

                inline explicit Tile1D(const size_t sz,
                                       const size_t rk,
                                       const T      dataOffset,
                                       const T      dataLength) :
                Member(sz,rk),
                offset(dataOffset),
                length( part<T>(dataLength, Coerce(offset) ) ),
                utmost(offset+length-_1)
                {

                }

                inline virtual ~Tile1D() noexcept
                {
                }

                inline friend std::ostream & operator<<(std::ostream &os, const Tile1D &self)
                {
                    if(self.length<=0)
                        return os << Empty;
                    else
                        return os << '|' << self.offset << ':' << self.utmost << '|' << '=' << self.length;
                }


                const T offset;
                const T length;
                const T utmost;

            private:
                Y_Disable_Copy_And_Assign(Tile1D);
            };

        }

    }
}

#endif // !Y_Concurrent_Splitting_Tile1D_Included

