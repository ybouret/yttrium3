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
            explicit Survey() noexcept;
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

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void release() noexcept;

        private:
            const Vectors & locus() const noexcept;
            virtual bool    takes(const Vector &) const noexcept = 0; //!< \return true iff criterion is matched
            Y_Disable_Copy_And_Assign(Survey); //!< discards

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            Vectors      list;     //!< list of univocal, ordered vectors
        public:
            const size_t sampling; //!< number of trials
        };

    }

}

#endif // !Y_Coven_Survey_Included

