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

            //__________________________________________________________________
            //
            //
            //
            //! 1D Tile
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Tile1D : public Member
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const T _1 = 1; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param sz size
                 \param rk rank
                 \param dataOffset data offset
                 \param dataLength data length
                 */
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

                //! cleanup
                inline virtual ~Tile1D() noexcept {}

                //! display
                inline friend std::ostream & operator<<(std::ostream &os, const Tile1D &self)
                {
                    if(self.length<=0)
                        return os << Empty;
                    else
                        return os << '|' << self.offset << ':' << self.utmost << '|' << '=' << self.length;
                }

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const T offset; //!< offset
                const T length; //!< length (0 means empty!)
                const T utmost; //!< meaningful iff length>0

            private:
                Y_Disable_Copy_And_Assign(Tile1D); //!< discarded
            };

        }

    }
}

#endif // !Y_Concurrent_Splitting_Tile1D_Included

