
//! file

#ifndef Y_Field_2D_Included
#define Y_Field_2D_Included 1

#include "y/field/layout/2d.hpp"
#include "y/field/1d.hpp"
#include "y/calculus/alignment.hpp"

namespace Yttrium
{
    namespace Field
    {

        //______________________________________________________________________
        //
        //
        //
        //! 2D fields
        //
        //
        //______________________________________________________________________
        template <typename T>
        class In2D :
        public CoreField,
        public Layout2D
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
            inline explicit In2D(const ID       & id,
                                 const Layout2D & layout) :
            CoreField(id),
            Layout2D(layout),
            entry(0),
            bytes(0),
            rows(0),
            data(0)
            {
                allocate();
            }


            //! setup with borrowed memory
            /**
             \param id       field name
             \param layout   field layout
             \param rowsAddr memory for rows
             \param dataAddr memory for data
             */
            template <typename ID>
            inline explicit In2D(const ID       & id,
                                 const Layout2D & layout,
                                 void * const     rowsAddr,
                                 void * const     dataAddr) :
            CoreField(id),
            Layout2D(layout),
            entry(0),
            bytes(0),
            rows( static_cast<Row  *>(rowsAddr) ),
            data( static_cast<MutableType *>(dataAddr) )
            {
                build();
            }



            //! cleanup
            inline virtual ~In2D() noexcept
            {
                rows += (**this).lower.y;
                release( (**this).width.y );
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \param y coordinate \return y-th row
            inline Row & operator[](const unit_t y) noexcept
            {
                assert(y>=(**this).lower.y);
                assert(y<=(**this).upper.y);
                return rows[y];
            }

            //! \param y coordinate \return y-th const row
            inline const Row & operator[](const unit_t y) const noexcept
            {
                assert(y>=(**this).lower.y);
                assert(y<=(**this).upper.y);
                return rows[y];
            }

        private:
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            Y_Disable_Copy_And_Assign(In2D); //!< discarded
            void *        entry;
            size_t        bytes;
            Row *         rows;
            MutableType * data;

            inline void allocate()
            {
                assert(!rows);
                assert(!data);
                assert(!entry);
                const size_t nrow       = (**this).width.y;
                const size_t rowsOffset = 0;
                const size_t rowsLength = nrow * sizeof(Row);
                const size_t dataOffset = Alignment::SystemMemory::Ceil(rowsOffset+rowsLength);
                const size_t dataLength = (**this).items * sizeof(T);
                bytes = dataOffset + dataLength;
                entry = AcquireMemory(bytes);
                {
                    char * p = static_cast<char *>(entry);
                    rows     = Hide::Cast<Row>(p+rowsOffset);
                    data     = Hide::Cast<MutableType>(p+dataOffset);
                }
                build();
            }

            inline void build()
            {
                assert(entry);
                assert(rows);
                assert(data);
                const size_t  nrow = (**this).width.y;
                const size_t  ncol = (**this).width.x;
                size_t        built = 0;
                MutableType * addr = data;
                try
                {
                    unit_t x = (**this).lower.x;
                    while(built<nrow)
                    {
                        const String rid = subFieldId(x++);
                        new (rows+built) Row(rid,sub,addr);
                        ++built;
                        addr += ncol;
                    }
                }
                catch(...) { release(built); throw; }
                rows -= (**this).lower.y;
            }

            inline void release(size_t built) noexcept
            {
                while(built-- > 0)
                    Pulverize( &rows[built] );
                rows=0;
                data=0;
                if(bytes) ReleaseMemory(entry,bytes);
            }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
            
        };


    }
}

#endif // !Y_Field_2D_Included
