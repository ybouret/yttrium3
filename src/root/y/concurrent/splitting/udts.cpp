
#include "y/concurrent/splitting/udts.hpp"
#include "y/object.hpp"
#include "y/memory/allocator/archon.hpp"
#include "y/type/destroy.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        namespace Splitting
        {

            class UpperDiagonalTiles:: Code : public Object
            {
            public:
                typedef Memory::Archon    Manager;

                inline explicit Code(const size_t nc,
                                     Lockable &   lk) :
                Object(),
                cxx(0),
                wlen( nc * sizeof(Tile) ),
                wksp( Manager::Instance().acquire(wlen) )
                {
                    assert(nc>0);
                    Coerce(cxx) = static_cast<Tile *>(wksp) - 1;
                    build(nc,lk,0);
                }

                inline virtual ~Code() noexcept
                {
                    Coerce(cxx)=0;
                    Manager::Location().release(wksp,wlen);
                }

                void build(const size_t mySize,
                           Lockable    &access,
                           const size_t extent) noexcept
                {
                    for(size_t i=1;i<=mySize;++i)
                    {
                        const size_t myRank = i-1;
                        new (cxx+i) Tile(mySize,myRank,access,extent);
                    }
                }


                Tile * const cxx;

            private:
                Y_Disable_Copy_And_Assign(Code);
                size_t wlen;
                void * wksp;

            };

            UpperDiagonalTiles:: ~UpperDiagonalTiles() noexcept
            {
                assert(code);
                Destroy(code);
            }

            UpperDiagonalTiles:: UpperDiagonalTiles(const size_t nc,
                                                    Lockable    &lk) :
            Subdivisions(nc),
            code(new Code(nc,lk) )
            {

            }

            const UpperDiagonalTile & UpperDiagonalTiles:: sub(const size_t i) const noexcept
            {
                return ask(i);
            }

            void UpperDiagonalTiles:: remap(const size_t extent, Lockable &access) noexcept
            {
                assert(code);
                if(extent!=code->cxx[1].n)
                {
                    code->build(ncpu,access,extent);
                    updateCache();
                }
            }

            size_t UpperDiagonalTiles:: size()     const noexcept { return ncpu; }
            size_t UpperDiagonalTiles:: capacity() const noexcept { return ncpu; }

            const UpperDiagonalTile & UpperDiagonalTiles:: ask(const size_t i) const noexcept
            {
                assert(code);
                assert(i>0);
                assert(i<=ncpu);
                return code->cxx[i];
            }


        }

    }

}


