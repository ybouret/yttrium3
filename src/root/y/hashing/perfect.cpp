
#include "y/hashing/perfect.hpp"
#include "y/core/tree.hpp"
#include "y/type/destroy.hpp"
#include "y/check/static.hpp"
#include "y/exception.hpp"
#include "y/string.hpp"
#include "y/string/length.hpp"


namespace Yttrium
{
    namespace Hashing
    {

        class Perfect:: Code : public Object, public Core::Tree
        {
        public:

            inline explicit Code()
            {
            }

            inline virtual ~Code() noexcept
            {
                //release();
            }

        private:
            Y_Disable_Copy_And_Assign(Code);
        };


        const char * const Perfect:: CallSign = "Hashing::Perfect";

        Perfect:: Perfect() : code( new Code() )
        {
        }

        Perfect:: ~Perfect() noexcept
        {
            assert(code);
            Destroy(code);
        }


        void Perfect:: at(const void * const path, const size_t size, const int key)
        {
            Y_STATIC_CHECK(sizeof(void*)>=sizeof(int),BadSystem);
            assert(0!=code);
            assert(!(path==0&&size>0));
            assert(key>0);

            const uint8_t * const iter = static_cast<const uint8_t *>(path);

            union {
                uint64_t q;
                void *   p;
                int     k;
            } alias = { 0 };

            alias.k = key; assert(0!=alias.p);

            if( ! code->insert(iter,size,alias.p) )
            {
                throw Specific::Exception(CallSign,"invalid key %d or multiple path",key);
            }
        }


        void Perfect:: at(const char * const text, const int key)
        {
            at(text, StringLength(text), key);
        }

        void Perfect::at(const Memory::ReadOnlyBuffer &buf, const int key)
        {
            at(buf.ro(), buf.length(), key);
        }


        static inline int NodeToKey(const Core::TreeNode * const node) noexcept
        {
            if(!node) return 0;
            union {
                uint64_t q;
                void *   p;
                int      k;
            } alias = { 0 };
            alias.p = node->data;
            assert(alias.k>0);
            return alias.k;
        }

        int Perfect:: operator()(const void * const path, const size_t size) noexcept
        {
            assert(0!=code);
            assert(!(path==0&&size>0));
            return NodeToKey(code->search(static_cast<const uint8_t *>(path),size));
        }

        int Perfect:: operator()(const char * const text) noexcept
        {
            return (*this)(text, StringLength(text));
        }

        int Perfect:: operator()(const Memory::ReadOnlyBuffer &buf) noexcept
        {
            return (*this)(buf.ro(), buf.length());
        }


        int Perfect:: operator()(const void * const path, const size_t size) const noexcept
        {
            assert(0!=code);
            assert(!(path==0&&size>0));
            return NodeToKey(code->search(static_cast<const uint8_t *>(path),size));
        }

        int Perfect:: operator()(const char * const text) const noexcept
        {
            return (*this)(text, StringLength(text));
        }

        int Perfect:: operator()(const Memory::ReadOnlyBuffer &buf) const noexcept
        {
            return (*this)(buf.ro(), buf.length());
        }



        OutputStream & Perfect:: viz(OutputStream &fp) const
        {
            return code->viz(fp);
        }

    }

}
