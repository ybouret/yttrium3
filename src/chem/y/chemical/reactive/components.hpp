
//! \file

#ifndef Y_Chemical_Components_Included
#define Y_Chemical_Components_Included 1

#include "y/chemical/reactive/actors.hpp"
#include "y/chemical/type/assembly.hpp"
#include "y/ability/freezable.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        //______________________________________________________________________
        //
        //
        //! Components classification
        //
        //______________________________________________________________________
        enum EqKind
        {
            Outlawed, //!< forbidden
            ProdOnly, //!< only product(s)
            ReacOnly, //!< only reactant(s)
            BothWays  //!< reactant(s) and product(s)
        };

        //______________________________________________________________________
        //
        //
        //
        //! Components (without constant)
        //
        //
        //______________________________________________________________________
        class Components : public Indexed, public Freezable, public Vizible
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Components(const String &, const size_t); //!< setup
            virtual ~Components() noexcept;                    //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void  addReac(const unsigned, const Species &); //!< add new reactant
            void  addProd(const unsigned, const Species &); //!< add new product
            bool  electroneutral() const; //!< \return true iff electroneutral
            bool  atLeastOneItem() const; //!< \return true iff at least one item

            xreal_t massAction(const xreal_t, XMul &, const XReadable &, const Level)                const; //!< \return mass action
            xreal_t massAction(const xreal_t, XMul &, const XReadable &, const Level, const xreal_t) const; //!< \return shifted mass action
            void    saveMove(XWritable &, const Level, const xreal_t)                       const noexcept; //!< safely move concentration using extent

            //! compute extent from a transformation
            /**
             \param Cold old C
             \param Cnew new C
             \param L    computation level
             \param xadd helper
             \return average extent
            */
            xreal_t extent(const XReadable &Cold, const XReadable &Cnew, const Level L, XAdd &xadd)    const;

            bool    hired(const Species &)       const noexcept; //!< \return true iff species in reac or prod
            bool    linkedTo(const Components &) const noexcept; //!< \return true iff common species

            //! emit graphViz code
            /**
             \param fp output stream
             \param color optional color
             \param style optional style
             \return fp
             */
            OutputStream & vizSelf(OutputStream &     fp,
                                   const char * const color,
                                   const char * const style) const;

            //! emit topology code
            /**
             \param fp output stream
             \param color optional color
             \return fp
             */
            OutputStream & vizLink(OutputStream &     fp,
                                   const char * const color) const;


            template <typename ARRAY> inline
            void topology(ARRAY &array, const Level L) const
            {
                for(const Actor *ac=prod->head;ac;ac=ac->next)
                    ac->sp(array,L) = (int)(ac->nu);

                for(const Actor *ac=reac->head;ac;ac=ac->next)
                    ac->sp(array,L) = -(int)(ac->nu);
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const EqKind   kind; //!< updated
            const size_t   size; //!< count of actors
            const Actors   reac; //!< reactant(s)
            const Actors   prod; //!< product(s)
            const xreal_t  one;  //!< numeric 1

        private:
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            Y_Disable_Copy_And_Assign(Components);
            void   checkUnused(const char * const, const Species &) const;
            EqKind computeKind() const noexcept;
#endif
        };

    }
}

#endif // !Y_Chemical_Components_Included

