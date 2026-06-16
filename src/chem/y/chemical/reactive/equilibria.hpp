
//! \file

#ifndef Y_Chemical_Equilibria_Included
#define Y_Chemical_Equilibria_Included 1

#include "y/chemical/reactive/equilibrium/format.hpp"
#include "y/container/associative/hash/set.hpp"
#include "y/pointer/keyed.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        typedef Keyed<String, ArcPtr<Equilibrium>> EqPtr; //!< alias
        typedef HashSet<String,EqPtr>              EqSet; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! Database of equilibria
        //
        //
        //______________________________________________________________________
        class Equilibria :
        public Proxy<const EqSet>,
        public EqFormat
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const    CallSign;      //!< "Equilibria"
            typedef EqSet::ConstIterator ConstIterator; //!< alias
            typedef EqSet::Iterator      Iterator;      //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Equilibria();          //!< setup
            virtual ~Equilibria() noexcept; //!< cleanup
            Equilibria(const Equilibria &); //!< duplicate
            Y_OSTREAM_PROTO(Equilibria);    //!< display with constants


            Iterator       begin()                        noexcept; //!< \return begin
            Iterator       end()                          noexcept; //!< \return end
            void           add(const EqPtr &);                      //!< add a precompiled equilibria
            std::ostream & print(std::ostream &, const bool) const; //!< print with optional constants \return output stream


        private:
            Y_Disable_Assign(Equilibria); //!< discarded
            Y_Proxy_Decl();               //!< helper
            EqSet db;                     //!< inner database

        public:
            xreal_t t_print; //!< time to print constants
        };
    }

}

#endif // !Y_Chemical_Equilibria_Included
