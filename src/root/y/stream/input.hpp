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
        static const char CR =  '\r';
        static const char LF =  '\n';
        
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

        void load(void * const       blockAddr,
                  const size_t       blockSize,
                  const char * const varName,
                  const char * const varPart);


        template <typename T>
        T load(const char * const, const char * const);

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

        uint64_t vbr64(const char * const varName,
                       const char * const varPart);

    protected:
        explicit InputStream(); //!< for virtual constructor

    private:
        Y_Disable_Copy_And_Assign(InputStream); //!< discarded
    };

}


#endif // !Y_InputStream_Included
