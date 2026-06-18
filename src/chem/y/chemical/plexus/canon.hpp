
#ifndef Y_Chemical_Plexus_Canon_Included
#define Y_Chemical_Plexus_Canon_Included 1

#include "y/chemical/plexus/topology.hpp"
#include "y/chemical/plexus/conservation/law.hpp"

#include "y/container/associative/book.hpp"
#include "y/container/associative/hash/default-set.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        template <typename T> class Roll : public Object
        {
        public:
            typedef BookOf<const T,DefaultHashSet> BookType;
            typedef Handy::BasicLightList<const T> ListType;

            inline explicit Roll() : Object(), book(), list()
            {
            }

            inline virtual ~Roll() noexcept
            {
            }

            //! inscribe species and kept list ordered \param sp species to inscribe
            inline void inscribe(const Species &sp)
            {
                if( Coerce(book).write(sp) ) {
                    try { Indexed::TopHSort( (Coerce(list) << sp) ); }
                    catch(...) { Coerce(book).clear(sp); throw; }
                } else {
                    assert(list.found(sp));
                }
            }


            const BookType book;
            const ListType list;

        private:
            Y_Disable_Copy_And_Assign(Roll);
        };

        typedef Matrix<unsigned> UMatrix; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! Canon of conservation laws
        //
        //
        //______________________________________________________________________
        class Canon
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            typedef Conservation::Law Law;    //!< alias
            typedef Law::List         Laws;   //!< alias
            typedef Roll<Species>     SpRoll; //!< alias
            typedef AutoPtr<SpRoll>   SpDB;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Canon(XML::Log &, const Topology &); //!< setup
            virtual ~Canon() noexcept;                    //!< cleanup

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const UMatrix  Qm;   //!< conservation matrix
            const size_t & Nc;   //!< Qm.rows
            const size_t   rg;   //!< rank of Qm
            const Laws     laws; //!< conservation law(s)
            const SpDB     conserved;
            const SpDB     unbounded;
        private:
            Y_Disable_Copy_And_Assign(Canon); //!< discarded
            void collectSpecies(XML::Log &,const SList &);
        };

    }

}

#endif // !Y_Chemical_Plexus_Canon_Included

