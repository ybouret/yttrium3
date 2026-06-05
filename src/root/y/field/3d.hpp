
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


            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

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
            slices(0),
            rows(0),
            data(0)
            {
                allocate();
            }


            //! setup with borrowed memory
            /**
             \param id     field name
             \param layout field layout
             \param slicesAddr memory for slices
             \param rowsAddr   memory for rows
             \param dataAddr   memory for data
             */
            template <typename ID>
            inline explicit In3D(const ID       & id,
                                 const Layout3D & layout,
                                 void * const     slicesAddr,
                                 void * const     rowsAddr,
                                 void * const     dataAddr
                                 ) :
            CoreField(id),
            Layout3D(layout),
            entry(0),
            bytes(0),
            slices( static_cast<Slice *>(slicesAddr)     ),
            rows(   static_cast<Row   *>(rowsAddr)       ),
            data(   static_cast<MutableType *>(dataAddr) )
            {
                build();
            }


            //! cleanup
            inline virtual ~In3D() noexcept
            {
                slices += (**this).lower.z;
                release( (**this).width.z );
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \param z coordinate \return z-th slice
            inline Slice & operator[](const unit_t z) noexcept
            {
                assert(z>=(**this).lower.z);
                assert(z<=(**this).upper.z);
                return slices[z];
            }

            //! \param z coordinate \return z-th const slice
            inline const Slice & operator[](const unit_t z) const noexcept
            {
                assert(z>=(**this).lower.z);
                assert(z<=(**this).upper.z);
                return slices[z];
            }


        private:

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            Y_Disable_Copy_And_Assign(In3D);
            void *        entry;
            size_t        bytes;
            Slice *       slices;
            Row  *        rows;
            MutableType * data;

            inline void allocate() noexcept
            {
                assert(!entry);
                assert(!bytes);
                assert(!rows);
                assert(!slices);
                assert(!data);

                {
                    Memory::Embed em[] = {
                        Memory::Embed(slices,(**this).width.z),
                        Memory::Embed(rows,(**this).width.z*(**this).width.y),
                        Memory::Embed(data,(**this).items)
                    };
                    entry = AcquireMemory( bytes = Y_Memory_Embed_Format(em) );
                    Y_Memory_Embed_Assign(entry,em);
                }
                build();

            }

            inline void build()
            {
                assert(rows);
                assert(slices);
                assert(data);
                const size_t nslices      = (**this).width.z;
                const size_t rowsPerSlice = (**this).width.y;
                const size_t dataPerSlice = (**this).shift.y;
                Row         * r     = rows;
                MutableType * d     = data;
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
                {
                    assert(entry);
                    ReleaseMemory(entry,bytes);
                }
                else
                {
                    assert(!entry);
                }
                slices = 0;
                rows   = 0;
                data   = 0;
            }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
        };

    }

}

#endif // !Y_Field_3D_Included
