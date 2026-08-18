//! \file

#ifndef Y_System_RTTI_Included
#define Y_System_RTTI_Included 1

#include "y/string.hpp"
#include "y/core/pool/cxx.hpp"
#include "y/ability/identifiable.hpp"
#include <typeinfo>

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Run Time Type Information
    //
    //
    //__________________________________________________________________________
    class RTTI : public CountedObject, public Identifiable
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const char * const CallSign; //!< "RTTI"
        class Table;


        //______________________________________________________________________
        //
        //
        //! Alias
        //
        //______________________________________________________________________
        class Alias : public String
        {
        public:
            explicit Alias(const String &uuid); //!< setup \param uuid identifier
            virtual ~Alias() noexcept;          //!< cleanup
            Alias *  next;                      //!< for pool
        private:
            Y_Disable_Copy_And_Assign(Alias); //!< discarded
        };


        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        virtual ~RTTI() noexcept; //!< cleanup
        Y_OSTREAM_PROTO(RTTI);    //!< display

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual const char * callSign() const noexcept;

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        const String & name()     const noexcept; //!< \return top alias
        bool   is(const String &) const noexcept; //!< \return true if id found in alias(es)
        RTTI & aka(const String &);               //!< \return *this with new alias
        RTTI & aka(const char * const);           //!< \return *this with new alias

        //! \return unique RTTI for type
        static RTTI & Of(const std::type_info &);

        //! \return unique RTTI for type
        template <typename T> static inline
        RTTI & Of()
        {
            return Of( typeid(T) );
        }

        //! \param uid user's desired alias \return unique RTTI for type with user alias
        template <typename T> static inline
        RTTI & Make(const String &uid)
        {
            return Of( typeid(T) ).aka(uid);
        }

        //! \param uid user's desired alias \return unique RTTI for type with user alias
        template <typename T> static inline
        RTTI & Make(const char * const uid)
        {
            return Of( typeid(T) ).aka(uid);
        }

        //! \return name of unique RTTI for type
        template <typename T> static inline
        const String & Name()
        {
            return Of<T>().name();
        }

        //! \return "<name>" from unique RTTI for type
        template <typename T> static inline
        const String CXX()
        {
            const String res = Name<T>();
            return '<' + res + '>';
        }

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        const CxxPoolOf<Alias> pool; //!< pool of alias(es)


    private:
        explicit RTTI(const String &uuid); //!< initialize \param uuid from typeid
        Y_Disable_Copy_And_Assign(RTTI);   //!< discarded
        friend class Table;
    };


}


#endif // !Y_System_RTTI_Included
