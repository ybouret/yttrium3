
//! \file

#ifndef Y_Stream_IO_Decode64_Included
#define Y_Stream_IO_Decode64_Included 1

#include "y/stream/io/u64.hpp"
#include "y/ostream-proto.hpp"

namespace Yttrium
{
    namespace IO
    {
        //______________________________________________________________________
        //
        //
        //
        //! Decoding 64 bits from sequential data
        //
        //
        //______________________________________________________________________
        class Decode64 : public U64Bits
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "IO::Decode64"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            /**
             \param b first byte, header+source (exception on invalid header)
             \param varName optional var name
             \param varPart optional var part
             */
            explicit Decode64(const uint8_t b,
                              const char * const varName,
                              const char * const varPart);
            virtual ~Decode64() noexcept; //!< cleanup
            Y_OSTREAM_PROTO(Decode64);    //!< display

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            bool ready() const noexcept; //!< \return expected<=0

            //! still decoding
            /**
             \param b next byte (exception if too many read bits)
             \param varName optional var name
             \param varPart optional var part
             */
            void operator()(const uint8_t b,
                            const char * const varName,
                            const char * const varPart);

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const uint64_t value;    //!< currentl decoded value
            const size_t   numExtra; //!< initial numExtra to read
            const size_t   expected; //!< expected read
            const size_t   dataBits; //!< currently read data bits
        private:
            Y_Disable_Copy_And_Assign(Decode64); //!< discarded
        };
    }

}

#endif // !Y_Stream_IO_Decode64_Included
