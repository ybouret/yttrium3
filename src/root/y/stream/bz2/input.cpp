#include "y/stream/bz2/input.hpp"
#include "y/stream/bz2/error.hpp"
#include "y/type/destroy.hpp"
#include "y/libc/file/input.hpp"
#include "y/ability/lockable.hpp"
#include "y/exception.hpp"
#include "y/stream/io/chars.hpp"

#if defined(_MSC_VER)
#pragma warning ( disable : 4668 )
#endif

#include "y/bzip2/bzlib.h"


namespace Yttrium
{
    namespace BZ2
    {
        namespace
        {
            typedef ArcPtr<Libc::InputFile> SharedInput;
        }

        class Input:: Code : public Object
        {
        public:
            enum Status
            {
                Live,
                Done
            };

            inline virtual ~Code() noexcept
            {
                int bzerror = 0;
                BZ2_bzReadClose(&bzerror,bzf);
                Coerce(bzf) = 0;
            }

            static Code * Create(Libc::InputFile * const inp,
                                 const int               small)
            {
                const SharedInput tmp(inp);
                return new Code(tmp,small);
            }

            inline bool query(char &C)
            {
                if(buf.size)
                {
                    C = buf.pullHead(); return true;
                }
                else
                {
                    switch(st)
                    {
                        case Done: return false;
                        case Live:
                            break;
                    }
                    int       bzerror = 0;
                    const int res     = BZ2_bzRead(&bzerror,bzf, &C, 1);
                    switch(bzerror)
                    {
                        case BZ_STREAM_END: st=Done; break;
                        default:
                            break;
                    }
                    if(res!=1)
                    {
                        if(BZ_STREAM_END==bzerror) {  return false; }
                        throw Specific::Exception("BZ2_bzRead","'%s'", Error::Get(bzerror) );
                    }
                    return true;
                }
            }

        private:
            Y_Disable_Copy_And_Assign(Code);
            SharedInput    ptr;
            BZFILE * const bzf;
        public:
            IO::Chars      buf;
        private:
            Status         st;

            inline Code(const SharedInput &usr,
                        const int          small) :
            Object(),
            ptr(usr),
            bzf(0),
            buf(),
            st(Live)
            {
                Y_Giant_Lock();
                int bzerror = 0;
                Coerce(bzf) = BZ2_bzReadOpen(&bzerror,ptr->handle, 0, small,0,0);
                if(!bzf)
                {
                    throw Specific::Exception("BZ2_bzReadOpen", "'%s'", Error::Get(bzerror));
                }
                else
                {
                    assert(BZ_OK==bzerror);
                }

            }

        };

        Input:: ~Input() noexcept
        {
            assert(code);
            Destroy(code);
        }

        Input:: Input(const String &name, const int small) :
        InputStream(name),
        code( Code::Create( new Libc::InputFile(name), small) )
        {

        }

        Input:: Input(const char * const name, const int small) :
        InputStream(name),
        code( Code::Create( new Libc::InputFile(name), small) )
        {

        }

        Input:: Input(const StdIn_ &_, const int small) :
        InputStream(Y_STDIN),
        code( Code::Create( new Libc::InputFile(_), small) )
        {

        }

        bool Input:: query(char &C)
        {
            assert(code);
            return code->query(C);
        }

        void Input:: store(const char C)
        {
            assert(code);
            code->buf >> C;
        }

        size_t Input:: query(void *const addr, const size_t size)
        {
            assert(!(0==addr&&size>0));

            size_t todo = size;
            char * p    = (char*)addr;
            while(todo>0&&code->buf.size>0)
            {
                *(p++) = code->buf.pullHead();
                --todo;
            }

            while(todo>0&&code->query(*p))
            {
                ++p;
                --todo;
            }

            return size-todo;

        }

    }

}


