
#include "y/ink/bitmap.hpp"
#include "y/object/counted.hpp"
#include "y/type/destroy.hpp"
#include "y/exception.hpp"
#include "y/object/factory.hpp"

namespace Yttrium
{
    namespace Ink
    {

        namespace
        {
            typedef Object::Factory BmpAllocator;

            static inline
            Memory::Allocator & BmpMgr()
            {
                static Memory::Allocator &mgr = BmpAllocator::Instance();
                return mgr;
            }

        }

        class Bitmap :: Code : public CountedObject
        {
        public:

            inline explicit Code(const Bitmap &bmp,
                                 Proc const    ctor,
                                 Proc const    dtor) :
            blockSize( bmp.d ),
            allocated( bmp.n * blockSize),
            workspace(BmpMgr().acquire(allocated)),
            destruct1(dtor),
            built(0)
            {
                assert(ctor);
                assert(dtor);
                try {
                    char * p = entry();
                    while(built<bmp.n)
                    {
                        ctor(p);
                        ++built;
                        p += blockSize;
                    }
                }
                catch(...)
                {
                    release(); throw;
                }
            }

            inline virtual ~Code() noexcept
            {
                release();
            }

            inline char * entry() noexcept
            {
                return static_cast<char *>(workspace);
            }

        private:
            Y_Disable_Copy_And_Assign(Code);
            void release() noexcept
            {
                static Memory::Allocator &mgr = BmpAllocator::Location();
                assert(workspace);
                assert(allocated);
                {
                    char * p = entry() + blockSize * built;
                    while(built>0)
                    {
                        destruct1( p -= blockSize );
                        --built;
                    }
                }
                mgr.release(workspace,allocated);
            }

            const size_t blockSize;
            size_t       allocated;
            void *       workspace;
            void       (*destruct1)(void *);
            size_t       built;
        };

        void Bitmap:: releaseCode() noexcept
        {
            assert(code);
            if(code->liberate())
                Destroy(code);
            else
                Coerce(code) = 0;
        }

        

        Bitmap:: ~Bitmap() noexcept
        {
            releaseRows();
            releaseCode();
        }

        namespace
        {
            static unsigned CheckD(const unsigned D)
            {
                if(D<=0) throw Specific::Exception("Ink::Bitmap", "negative depth");
                return D;
            }
        }

        Bitmap:: Bitmap(const unit_t   W,
                        const unit_t   H,
                        const unsigned D,
                        Proc const     ctor,
                        Proc const     dtor) :
        Area(W,H),
        d( CheckD(D) ),
        s( w*d ),
        code( new Code(*this,ctor,dtor) ),
        rlen(0),
        row_(0)
        {
            code->withhold();
            acquireRows();
        }

        Bitmap:: Bitmap(const Bitmap &bmp) :
        Area(bmp),
        d(bmp.d),
        s(bmp.s),
        code(bmp.code),
        rlen(0),
        row_(0)
        {
            code->withhold();
            acquireRows();
        }

        Bitrow:: Bitrow(void * const P, const unit_t W) noexcept :
        p(P),
        w(W)
        {
            assert(p); assert(w);
        }

        void Bitmap:: releaseRows() noexcept
        {
            static Memory::Allocator &mgr = BmpAllocator::Location();
            void * addr = row_; mgr.release(addr,Coerce(rlen));
            Coerce(row_) = 0;
        }


        void Bitmap:: acquireRows()
        {
            try
            {
                assert(code);
                assert(!row_);
                Coerce(row_)  = static_cast<Bitrow *>( BmpMgr().acquire(Coerce(rlen)  = h * sizeof(Bitrow)) );
                char * p = code->entry();
                for(unit_t j=0;j<h;++j,p+=s)
                    new (row_+j) Bitrow(p,w);
            }
            catch(...)
            {
                releaseCode(); throw;
            }
        }


    }

}


