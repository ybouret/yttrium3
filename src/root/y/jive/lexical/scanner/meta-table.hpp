
//! \file

#ifndef Y_Jive_Lexical_MetaTable_Included
#define Y_Jive_Lexical_MetaTable_Included 1

#include "y/jive/lexical/scanner/meta-list.hpp"
#include "y/container/associative/hash/map.hpp"
#include "y/pointer/arc.hpp"
#include "y/hashing/key/dumper.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {
            typedef ArcPtr<MetaList>                           SharedMetaList; //!< alias
            typedef Hashing::KeyDumper<uint8_t>                MetaHasher;     //!< alias
            typedef HashMap<uint8_t,SharedMetaList,MetaHasher> MetaMap;        //!< alias

            //__________________________________________________________________
            //
            //
            //
            //! Table of meta-lists
            //
            //
            //__________________________________________________________________
            class MetaTable : public MetaMap
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit MetaTable(const Identifier &); //!< setup
                virtual ~MetaTable() noexcept;          //!< cleanup

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                //! \return on the fly get/create meta list
                MetaList &       operator[](const uint8_t);

                //! \return matching list with look up optimization, 0 otherwise
                const MetaList * query(const uint8_t) noexcept;

                //! dispatch rule reference in (all) matching list(s) \return leading from pattern
                Leading dispatch(const Rule &);

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Identifier name; //!< from scanner

            private:
                Y_Disable_Copy_And_Assign(MetaTable); //!< discarded

                //! remove tail matching rule
                void emergencyRemove(const Rule &) noexcept;
            };


        }

    }

}

#endif // !Y_Jive_Lexical_MetaTable_Included
