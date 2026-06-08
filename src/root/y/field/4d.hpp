
//! file

#ifndef Y_Field_4D_Included
#define Y_Field_4D_Included 1

#include "y/field/layout/4d.hpp"
#include "y/field/3d.hpp"

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
        class In4D :
        public CoreField,
        public Layout4D
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
            typedef In3D<T> Volume; //!< alias

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
            inline explicit In4D(const ID       & id,
                                 const Layout4D & layout) :
            CoreField(id),
            Layout4D(layout),
            volumes(0),
            entry(0),
            bytes(0)
            {
                allocate();
            }


            //! cleanup
            inline virtual ~In4D() noexcept
            {
                volumes += (**this).lower.w;
                release( (**this).width.w );
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \param w coordinate \return w-th volume
            inline Volume & operator[](const unit_t w) noexcept
            {
                assert(w>=(**this).lower.w);
                assert(w<=(**this).upper.w);
                return volumes[w];
            }

            //! \param w coordinate \return w-th const volume
            inline const Volume & operator[](const unit_t w) const noexcept
            {
                assert(w>=(**this).lower.w);
                assert(w<=(**this).upper.w);
                return volumes[w];
            }

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
        private:
            Y_Disable_Copy_And_Assign(In4D);
            Volume *volumes;
            void   *entry;
            size_t  bytes;


            inline void allocate()
            {
                const typename WidthFor<Coord4D>::Type width = (**this).width;
                Slice *       slices      = 0;
                Row   *       rows        = 0;
                MutableType * data        = 0;
                const size_t volumeCount  = width.w;
                const size_t slicesPerVol = width.z;
                const size_t rowsPerVol   = width.z * width.y;
                const size_t dataPerVol   = sub->items;
                {

                    Memory::Embed em[] =
                    {
                        Memory::Embed(volumes,volumeCount),
                        Memory::Embed(slices, volumeCount*slicesPerVol),
                        Memory::Embed(rows,   volumeCount*rowsPerVol),
                        Memory::Embed(data,  (**this).items)
                    };
                    entry = AcquireMemory( bytes = Y_Memory_Embed_Format(em) );
                    Y_Memory_Embed_Assign(entry,em);
                }

                size_t built = 0;
                try
                {
                    unit_t w = (**this).lower.w;
                    while(built<volumeCount)
                    {
                        const String vid = subFieldId(w);
                        new (volumes+built) Volume(vid,sub,slices,rows,data);
                        slices += slicesPerVol;
                        rows   += rowsPerVol;
                        data   += dataPerVol;
                        ++built;
                    }

                }
                catch(...) { release(built); throw; }
                volumes -= (**this).lower.w;
            }

            void release(size_t built) noexcept
            {
                assert(entry);
                assert(bytes);
                while(built-- > 0)
                    Pulverize( &volumes[built] );
                ReleaseMemory(entry,bytes);
                volumes=0;
            }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        };

    }

}

#endif // !Y_Field_4D_Included


