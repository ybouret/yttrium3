
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
            template <typename ID>
            inline explicit In4D(const ID &id, const Layout4D &layout) :
            CoreField(id),
            Layout4D(layout),
            volumes(0),
            entry(0),
            bytes(0)
            {
                allocate();
            }


            inline virtual ~In4D() noexcept
            {
            }


        private:
            Y_Disable_Copy_And_Assign(In4D);
            Volume *volumes;
            void   *entry;
            size_t  bytes;


            inline void allocate()
            {
                {
                    Memory::Embed embed[] =
                    {
                        
                    };
                    entry = AcquireMemory( bytes = Y_Memory_Embed_Format(em) );
                    Y_Memory_Embed_Assign(entry,em);
                }
            }
        };

    }

}

#endif // !Y_Field_4D_Included


