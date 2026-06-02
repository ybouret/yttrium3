//! \file

#ifndef Y_Associative_Book_Inluded
#define Y_Associative_Book_Inluded 1

#include "y/container/associative/addr-key.hpp"

namespace Yttrium
{


    //__________________________________________________________________________
    //
    //
    //
    //! holds reference + key
    //
    //
    //__________________________________________________________________________
    template <typename T>
    class BookEntry
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Expose(T,Type); //!< aliases

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup \param args use its address
        inline explicit BookEntry(ConstType& args) noexcept :
        data(args),
        key_(data)
        {
        }

        //! duplicate \param other another entry
        inline BookEntry(const BookEntry& other) noexcept :
        data(other.data),
        key_(other.key_)
        {
        }

        //! display
        inline friend std::ostream& operator<<(std::ostream& os, const BookEntry& self)
        {
            return os << self.data;
        }

        //! cleanup
        inline ~BookEntry() noexcept {}

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        inline const AddrKey & key() const noexcept { return key_; } //!< \return  key_

    private:
        Y_Disable_Assign(BookEntry); //!< discard
        ConstType&     data; //!< inner reference
        const AddrKey  key_; //!< inner key
    };

    //__________________________________________________________________________
    //
    //
    //
    //! Book of named addresses
    //
    //
    //__________________________________________________________________________
    template <typename T, template <typename, typename> class LEXICON >
    class BookOf : public LEXICON<AddrKey, BookEntry<T> >
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef BookEntry<T> Entry; //!< alias
        Y_Args_Expose(T,Type);      //!< aliases

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup
        inline explicit BookOf() {}

        //! cleanup
        inline virtual ~BookOf() noexcept {}

        //! duplicate \param book another book
        inline explicit BookOf(const BookOf& book) : LEXICON<AddrKey, Entry>(book) {}

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! write address \param ref object reference \return true iff address was kept
        inline bool write(ConstType &ref)
        {
            const Entry entry(ref);
            return this->insert(entry);
        }

        //! clear address \param ref object reference \return true iff address was removed
        inline bool clear(ConstType& ref) noexcept
        {
            const AddrKey key(ref);
            return this->remove(key);
        }

        //! query address \param ref object reference \return true iff address was previously written
        inline bool query(ConstType& ref) const noexcept
        {
            const AddrKey key(ref);
            return 0 != this->search(key);
        }

    private:
        Y_Disable_Assign(BookOf); //!< discarded
    };

}


#endif // !Y_Associative_Book_Inluded
