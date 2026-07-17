
//! \file

#ifndef Y_Memory_Embedded_Included
#define Y_Memory_Embedded_Included 1


#include "y/config/setup.hpp"
#include "y/ostream-proto.hpp"

namespace Yttrium
{
    namespace Memory
    {

        //______________________________________________________________________
        //
        //
        //
        //! helper to embed different objects into memory
        //
        //
        //______________________________________________________________________
        class Embed
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            /**
             \param entry address of objects
             \param count number of objects
             */
            template <typename T> inline explicit
            Embed(T * & entry, const size_t count) noexcept :
            pblock( (void**) &entry ),
            length( count * sizeof(T) ),
            offset(0)
            {

            }

            Embed(void * &     entry,
                  const size_t numBlocks,
                  const size_t blockSize) noexcept;




            Embed(const Embed &) noexcept; //!< duplicate
            ~Embed() noexcept;             //!< cleanup
            Y_OSTREAM_PROTO(Embed);        //!< display

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            static size_t Format(Embed [], const size_t)              noexcept; //!< format offsets \return bytes to hold embedded objects
            static void   Assign(void * const, Embed[], const size_t) noexcept; //!< assign blocks to their offset
            size_t        nextOffset()                          const noexcept; //!< \return next aligned offset
            void          assignFrom(void * const)                    noexcept; //!< set pblock to entry+offset

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            void **      pblock; //!< block pointer
            const size_t length; //!< required bytes
            size_t       offset; //!< current offset

        private:
            Y_Disable_Assign(Embed); //!< discarded
        };

        //! helper to compute bytes for objects
#define Y_Memory_Embed_Format(EM)       (Yttrium::Memory::Embed::Format(EM,sizeof(EM)/sizeof(EM[0])))

        //! helper to assign objects from memory
#define Y_Memory_Embed_Assign(ENTRY,EM)  Yttrium::Memory::Embed::Assign(ENTRY,EM,sizeof(EM)/sizeof(EM[0]))

        

    }

}

#endif // !Y_Memory_Embedded_Included
