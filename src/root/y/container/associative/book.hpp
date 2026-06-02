//! \file

#ifndef Y_Associative_Book_Inluded
#define Y_Associative_Book_Inluded 1

#include "y/container/associative/addr-key.hpp"

namespace Yttrium
{


    template <typename T>
    class BookEntry
    {
    public:
        Y_Args_Expose(T, Type);

        inline explicit BookEntry(ConstType& args) noexcept :
        data(args),
        key_(data)
        {
        }

        inline BookEntry(const BookEntry& other) noexcept :
        data(other.data),
        key_(other.key_)
        {
        }

        inline friend std::ostream& operator<<(std::ostream& os, const BookEntry& self)
        {
            return os << self.data;
        }

        inline ~BookEntry() noexcept {}

        inline const AddrKey& key() const noexcept { return key_; }

    private:
        Y_Disable_Assign(BookEntry);
        ConstType&     data;
        const AddrKey  key_;
    };

    template <typename T, template <typename, typename> class LEXICON >
    class BookOf : public LEXICON<AddrKey, BookEntry<T> >
    {
    public:
        typedef BookEntry<T> Entry;
        Y_Args_Expose(T, Type);

        inline explicit BookOf() {}
        inline virtual ~BookOf() noexcept {}
        inline explicit BookOf(const BookOf& book) : LEXICON<AddrKey, Entry>(book) {}

        inline bool write(ConstType &ref)
        {
            const Entry entry(ref);
            return this->insert(entry);
        }

        inline bool clear(ConstType& ref) noexcept
        {
            const AddrKey key(ref);
            return this->remove(key);
        }

        inline bool query(ConstType& ref) const noexcept
        {
            const AddrKey key(ref);
            return 0 != this->search(key);
        }

    private:
        Y_Disable_Assign(BookOf);
    };

}


#endif // !Y_Associative_Book_Inluded
