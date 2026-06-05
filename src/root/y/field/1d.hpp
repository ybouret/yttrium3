
//! file

#ifndef Y_Field_1D_Included
#define Y_Field_1D_Included 1

#include "y/field/layout/1d.hpp"
#include "y/field/field.hpp"
#include "y/type/pulverize.hpp"

namespace Yttrium
{
    namespace Field
    {

        template <typename T>
        class In1D :
        public Field,
        public Layout1D
        {
        public:
            Y_Args_Declare(T,Type);
            
            template <typename ID>
            inline explicit In1D(const ID &id, const Layout1D &layout) :
            Field(id),
            Layout1D(layout),
            bytes( bytesFor(sizeof(T))  ),
            entry( static_cast<MutableType*>(AcquireMemory(bytes)) )
            {
                assert(bytes>=bytesFor( sizeof(T) ));
                build();
            }


            inline virtual ~In1D() noexcept {
                entry += (**this).lower; release( (**this).items );
            }

            inline Type & operator[](const Coord1D x) noexcept
            {
                assert(x>=(**this).lower);
                assert(x<=(**this).upper);
                return entry[x];
            }

            inline ConstType & operator[](const Coord1D x) const noexcept
            {
                assert(x>=(**this).lower);
                assert(x<=(**this).upper);
                return entry[x];
            }


        private:
            Y_Disable_Copy_And_Assign(In1D);
            size_t         bytes;
            MutableType *  entry;

            inline void release(size_t built) noexcept
            {
                assert(entry);
                while(built-- > 0 ) Pulverize( &entry[built] );
                if(bytes) ReleaseMemory(*(void**)&entry,bytes);
            }

            inline void build()
            {
                const size_t count = (**this).items;
                size_t       built = 0;
                try {
                    while(built<count) {
                        new (entry+built) MutableType();
                        ++built;
                    }
                }
                catch(...) { release(built); throw; }
                entry -= (**this).lower;
            }

        };

    }

}

#endif // !Y_Field_1D_Included
