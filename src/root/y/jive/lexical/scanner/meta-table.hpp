
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
            typedef ArcPtr<MetaList>                           SharedMetaList;
            typedef Hashing::KeyDumper<uint8_t>                MetaHasher;
            typedef HashMap<uint8_t,SharedMetaList,MetaHasher> MetaMap;

            class MetaTable : public MetaMap
            {
            public:
                explicit MetaTable(const Identifier &);
                virtual ~MetaTable() noexcept;

                MetaList & operator[](const uint8_t);


                // dispatch rule in (all) matching list(s)
                void dispatch(const Rule &);

                const Identifier name;

            private:
                Y_Disable_Copy_And_Assign(MetaTable);
            };


        }

    }

}

#endif // !Y_Jive_Lexical_MetaTable_Included
