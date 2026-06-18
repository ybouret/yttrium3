
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

        //______________________________________________________________________
        //
        //
        //
        //! book+list of references
        //
        //
        //______________________________________________________________________
        template <typename T> class Roll : public Object
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef BookOf<const T,DefaultHashSet> BookType; //!< alias
            typedef Handy::BasicLightList<const T> ListType; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            inline explicit Roll() : Object(), book(), list() {} //!< setup
            inline virtual ~Roll() noexcept {}                   //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

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

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const BookType book; //!< database
            const ListType list; //!< ordered content

        private:
            Y_Disable_Copy_And_Assign(Roll); //!< discarded
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
            typedef AutoPtr<SpRoll>   SpDB;   //!< alias

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
            const UMatrix  Qm;        //!< conservation matrix
            const size_t & Nc;        //!< Qm.rows
            const size_t   rg;        //!< rank of Qm
            const Laws     laws;      //!< conservation law(s)
            const SpDB     conserved; //!< conserved species
            const SpDB     unbounded; //!< unbounded species

        private:
            Y_Disable_Copy_And_Assign(Canon);              //!< discarded
            void collectSpecies(XML::Log &,const SList &); //!< populate conserved/unbounded
        };

    }

}

#endif // !Y_Chemical_Plexus_Canon_Included

