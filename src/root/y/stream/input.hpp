//! file

#ifndef Y_InputStream_Included
#define Y_InputStream_Included


#include "y/stream/stream.hpp"
#include "y/type/ints.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Base class for input stream
    //
    //
    //__________________________________________________________________________
    class InputStream : public Stream
    {

    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const char CR =  '\r'; //!< alias
        static const char LF =  '\n'; //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup \param name for title
        template <typename NAME> inline
        explicit InputStream(const NAME &name) : Stream(name)
        {
        }
        
        virtual ~InputStream() noexcept; //!< cleanup

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual bool   query(char &)                      = 0; //!< \return true if new char is available
        virtual size_t query(void * const, const size_t ) = 0; //!< \return read in block
        virtual void   store(const char)                  = 0; //!< store single back back into the stream

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        bool peek(char &);    //!< \return true iff available char
        bool gets(String &);  //!< \return ture iff a new (maybe empty) string was read

        //! try to load exact block size
        /**
         \param blockAddr memory region
         \param blockSize mandatory block size > 0
         \param varName   optional variable name
         \param varPart   optional variable part
         */
        void load(void * const       blockAddr,
                  const size_t       blockSize,
                  const char * const varName,
                  const char * const varPart);


        //! \return load for uint[8|16|32|64]_t
        template <typename T>
        T load(const char * const, const char * const);

        //! load constant byte rate integral
        /**
         \param varName   optional variable name
         \param varPart   optional variable part
         \return read integral type
         */
        template <typename T> inline
        T cbr(const char * const varName,
              const char * const varPart)
        {
            typedef typename UnsignedFor<sizeof(T)>::Alias::Type UType;
            union {
                UType u;
                T     t;
            } alias = { load<UType>(varName,varPart) };
            return alias.t;
        }

        //! decode variable byte rate 64 bits
        /**
         \param varName   optional variable name
         \param varPart   optional variable part
         \return decoded 64 bits from [0:9] bytes
         */
        uint64_t vbr64(const char * const varName,
                       const char * const varPart);

        template <typename T> inline
        T vbr(const char * const varName,
              const char * const varPart)
        {
            // load compact 64 bits
            const uint64_t qw = vbr64(varName,varPart);
            return 0;
        }

    protected:
        explicit InputStream(); //!< for virtual constructor

    private:
        Y_Disable_Copy_And_Assign(InputStream); //!< discarded

    };

}


#endif // !Y_InputStream_Included
