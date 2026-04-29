//! file

#ifndef Y_OutputStream_Included
#define Y_OutputStream_Included 1


#include "y/stream/stream.hpp"
#include "y/type/ints.hpp"
#include "y/check/printf.h"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Base class for Output Stream
    //
    //
    //__________________________________________________________________________
    class OutputStream : public Stream
    {

    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup \param name for title
        template <typename NAME> inline
        explicit OutputStream(const NAME &name) : Stream(name)
        {
        }

        virtual ~OutputStream() noexcept; //!< cleanup

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual void write(const char)                       = 0; //!< write single char
        virtual void write(const void * const, const size_t) = 0; //!< write block of bytes
        virtual void flush()                                 = 0; //!< flush state


        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        size_t vbr64(const uint64_t); //!< write variable byte rate 64 bits \return written bytes

        //! variable byte rate output \param x integral value \return written bytes
        template <typename T> inline
        size_t vbr(const T &x)
        {
            typedef typename UnsignedFor<sizeof(T)>::Alias::Type UType;
            const union {
                T     t;
                UType u;
            } alias = { x };
            return vbr64(alias.u);
        }

        //! constrant byte rate output \param x integral value \return written bytes
        template <typename T> inline
        size_t cbr(const T &x)
        {
            typedef typename UnsignedFor<sizeof(T)>::Alias::Type UType;
            const union {
                T     t;
                UType u;
            } alias = { x };
            return emit(alias.u);
        }

        size_t emit(const uint8_t  &); //!< emit one byte    \return 1
        size_t emit(const uint16_t &); //!< emit two bytes   \return 2
        size_t emit(const uint32_t &); //!< emit four bytes  \return 4
        size_t emit(const uint64_t &); //!< emit eight bytes \return 8

        //! formatted output
        /**
         \param fmt C-style format
         \return *this
         */
        OutputStream & operator()(const char * const fmt,...) Y_Printf_Check(2,3);

    protected:
        //explicit OutputStream(); //!< setup for virtual constructor

    private:
        Y_Disable_Copy_And_Assign(OutputStream); //!< discarded
    };

}


#endif // !Y_OutputStream_Included
