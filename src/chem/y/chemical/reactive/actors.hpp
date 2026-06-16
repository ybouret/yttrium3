

//! \file

#ifndef Y_Chemical_Actors_Included
#define Y_Chemical_Actors_Included 1

#include "y/chemical/reactive/actor.hpp"
#include "y/type/proxy.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        //______________________________________________________________________
        //
        //
        //
        //! List of univocal actors
        //
        //
        //______________________________________________________________________
        class Actors : public Proxy<const Actor::List>, public Entity
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "Actors"

            //__________________________________________________________________
            //
            //
            // C+++
            //
            //__________________________________________________________________
            explicit Actors(const Acting); //!< setup
            virtual ~Actors() noexcept;    //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void hire(const unsigned, const Species &); //!< hire new actor
            bool hired(const Species &) const noexcept; //!< \return true iff species was hired
            apz  charge()                        const; //!< \return partial reaction charge

            void massAction(XMul &, const XReadable &, const Level) const; //!< update mass action
            void massAction(XMul &, const XReadable &, const Level, const xreal_t) const; //!< updated shifted mass action



            xreal_t extent(const XReadable &, const Level)            const noexcept; //!< \return limiting extent
            bool    active(const XReadable &, const Level)            const noexcept; //!< \return false if one concentration is <= 0
            void    safeMove(XWritable &, const Level, const xreal_t) const noexcept; //!< move all concentrations using extent

        private:
            Y_Disable_Copy_And_Assign(Actors); //!< discarded
            Y_Proxy_Decl();                    //!< helper
            Actor::List  list;                 //!< innner actors
            const Acting acting;               //!< usage
        };

    }
}

#endif // !Y_Chemical_Actors_Included

