//! \file

#ifndef Y_Coven_Survey_Included
#define Y_Coven_Survey_Included 1

#include "y/coven/vector.hpp"
#include "y/type/proxy.hpp"

namespace Yttrium
{

    namespace Coven
    {

        //______________________________________________________________________
        //
        //
        //
        //! Survey to collect tribes construction result
        //
        //
        //______________________________________________________________________
        class Survey : public Proxy< const Vectors >, public Releasable
        {
        public:
            
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Survey(const size_t nmin) noexcept; //!< setup \param nmin for min_ncof
            virtual ~Survey() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            bool        got(const Vector &) const noexcept;         //!< \return true iff vector is not recorded
            Survey &    operator<< (const Vector &);                //!< insert not null, taken vector \return *this
            friend bool operator==(const Survey &, const Survey &); //!< \return vector-wise comparison
            void        print(std::ostream &) const;                //!< pretty print content
            static void Callback(const Vector &, void * const);     //!< helper for Tribes
            void        fusion(Survey &) noexcept;                  //!< fusion source (new) content, source is emptied
            bool        insert(const Vector &);                     //!< try to insert new vector \return true iff new, taken vector

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void release() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Survey); //!< discards
            void            place(Vector * const)       noexcept;     //!< push tail and move new vector at its palce
            virtual bool    takes(const Vector &) const noexcept = 0; //!< \return true iff criterion is matched
            const Vectors & locus()               const noexcept;

            
            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            Vectors      list;     //!< list of univocal, ordered vectors
        public:
            const size_t sampling; //!< number of trials
            const size_t min_ncof; //!< minimal number of coefficients
        };

    }

}

#endif // !Y_Coven_Survey_Included

