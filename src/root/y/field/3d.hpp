
//! file

#ifndef Y_Field_3D_Included
#define Y_Field_3D_Included 1

#include "y/field/layout/3d.hpp"
#include "y/field/2d.hpp"

namespace Yttrium
{
    namespace Field
    {

        //______________________________________________________________________
        //
        //
        //
        //! 3D fields
        //
        //
        //______________________________________________________________________
        template <typename T>
        class In3D :
        public CoreField,
        public Layout3D
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Declare(T,Type); //!< aliases
            typedef In1D<T> Row;    //!< alias
            typedef In2D<T> Slice;  //!< alias

            //! setup with own memory
            /**
             \param id     field name
             \param layout field layout
             */
            template <typename ID>
            inline explicit In3D(const ID       & id,
                                 const Layout3D & layout) :
            CoreField(id),
            Layout3D(layout),
            entry(0),
            bytes(0),
            rows(0),
            slices(0),
            data(0)
            {
                allocate();
            }


            inline virtual ~In3D() noexcept
            {
                slices += (**this).lower.z;
                release( (**this).width.z );
            }

            inline Slice & operator[](const unit_t z) noexcept
            {
                assert(z>=(**this).lower.z);
                assert(z<=(**this).upper.z);
                return slices[z];
            }

            inline const Slice & operator[](const unit_t z) const noexcept
            {
                assert(z>=(**this).lower.z);
                assert(z<=(**this).upper.z);
                return slices[z];
            }


        private:
            Y_Disable_Copy_And_Assign(In3D);
            void *        entry;
            size_t        bytes;
            Row  *        rows;
            Slice *       slices;
            MutableType * data;

            inline void allocate() noexcept
            {
                assert(!entry);
                assert(!bytes);
                assert(!rows);
                assert(!slices);
                assert(!data);

                const size_t nslices = (**this).width.z;
                const size_t nrows   = (**this).width.y * nslices;

                const size_t sOffset = 0;
                const size_t sLength = nslices*sizeof(Slice);
                const size_t rOffset = Alignment::SystemMemory::Ceil(sOffset+sLength);
                const size_t rLength = nrows * sizeof(Row);
                const size_t dOffset = Alignment::SystemMemory::Ceil(rOffset+rLength);
                const size_t dLength = (**this).items * sizeof(T);
                bytes = dOffset + dLength;
                entry = AcquireMemory(bytes);
                {
                    char * p = static_cast<char *>(entry);
                    slices   = Hide::Cast<Slice>(p+sOffset);
                    rows     = Hide::Cast<Row>(p+rOffset);
                    data     = Hide::Cast<MutableType>(p+dOffset);
                }
                build();
            }

            inline void build()
            {
                assert(entry);
                assert(rows);
                assert(slices);
                assert(data);
                const size_t nslices      = (**this).width.z;
                const size_t rowsPerSlice = (**this).width.y;
                const size_t dataPerSlice = (**this).shift.y;
                Row         * r = rows;
                MutableType * d = data;
                size_t        built = 0;
                try
                {
                    unit_t z = (**this).lower.z;
                    while(built<nslices)
                    {
                        const String sid = subFieldId(z++);
                        new (slices+built) Slice(sid,sub,r,d);
                        r += rowsPerSlice;
                        d += dataPerSlice;
                        ++built;
                    }
                }
                catch(...) { release(built); throw; }
                slices -= (**this).lower.z;
            }

            inline void release(size_t built) noexcept
            {
                while(built-- > 0 )
                    Pulverize( &slices[built] );
                if(bytes)
                    ReleaseMemory(entry,bytes);
                slices = 0;
                rows   = 0;
                data   = 0;
            }

        };

    }

}

#endif // !Y_Field_3D_Included
