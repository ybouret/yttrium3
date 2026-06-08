
//! file

#ifndef Y_Field_Included
#define Y_Field_Included 1

#include "y/string.hpp"
#include "y/hide.hpp"

namespace Yttrium
{
    namespace Field
    {
        //______________________________________________________________________
        //
        //
        //
        //! Base class for Fields
        //
        //
        //______________________________________________________________________
        class CoreField : public CountedObject
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param id field name
            template <typename ID> inline
            explicit CoreField(const ID &id) : CountedObject(), name(id)
            {
            }

            //! cleanup
            virtual ~CoreField() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            static void *  AcquireMemory(size_t & );                     //!< \return memory for required bytes
            static void    ReleaseMemory_(void * &, size_t & ) noexcept; //!< release acquired memory
            String         subFieldId(const unit_t)               const; //!< \return sub field name for given coordinate
            const String & key()                         const noexcept; //!< \return name

            template <typename T> static inline
            void ReleaseMemory(T * &entry, size_t &bytes) noexcept
            {
                void * addr = Hide::Address(entry);
                ReleaseMemory_(addr,bytes);
                entry = 0;
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const String name; //!< name
            
        private:
            Y_Disable_Copy_And_Assign(CoreField); //!< discarded
        };
    }

}

#endif // !Y_Field_Included

