
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

        //______________________________________________________________________
        //
        //
        //
        //! 1D fields
        //
        //
        //______________________________________________________________________
        template <typename T>
        class In1D :
        public CoreField,
        public Layout1D
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Declare(T,Type); //!< aliases

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
            inline explicit In1D(const ID       & id,
                                 const Layout1D & layout) :
            CoreField(id),
            Layout1D(layout),
            bytes( bytesFor(sizeof(T))  ),
            entry( static_cast<MutableType*>(AcquireMemory(bytes)) )
            {
                assert(bytes>=bytesFor( sizeof(T) ));
                build();
            }

            //! setup with borrowed memory
            /**
             \param id     field name
             \param layout field layout
             \param addr   for entry with enough bytes
             */
            template <typename ID>
            inline explicit In1D(const ID &id, const Layout1D &layout, void * const addr) :
            CoreField(id),
            Layout1D(layout),
            bytes( 0    ),
            entry(  static_cast<MutableType*>(addr) )
            {
                build();
            }


            //! cleanup
            inline virtual ~In1D() noexcept {
                entry += (**this).lower; release( (**this).items );
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \param x coordinate \return data access
            inline Type & operator[](const Coord1D x) noexcept
            {
                assert(x>=(**this).lower);
                assert(x<=(**this).upper);
                return entry[x];
            }

            //! \param x coordinate \return const data access
            inline ConstType & operator[](const Coord1D x) const noexcept
            {
                assert(x>=(**this).lower);
                assert(x<=(**this).upper);
                return entry[x];
            }


        private:
            Y_Disable_Copy_And_Assign(In1D); //!< discarded

            //__________________________________________________________________
            //
            //
            // Members
            //
            //_____________________________________________________ _____________
            size_t         bytes; //!< data bytes, zero if borrowed
            MutableType *  entry; //!< data entry

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            inline void release(size_t built) noexcept
            {
                assert(entry);
                while(built-- > 0 ) Pulverize( &entry[built] );
                if(bytes) ReleaseMemory(entry,bytes);
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
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        };

    }

}

#endif // !Y_Field_1D_Included
