

#ifndef Y_Chemical_Plexus_Warden_Included
#define Y_Chemical_Plexus_Warden_Included 1

#include "y/chemical/plexus/conservations.hpp"
#include "y/container/cxx/array.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        

        template <typename T>
        class CountedMatrix : public CountedObject, public Matrix<T>
        {
        public:
            typedef ArcPtr<CountedMatrix> Pointer;
            
            inline explicit CountedMatrix(const Matrix<T> &mm,
                                          const T         &dd) :
            CountedObject(),
            Matrix<T>(mm),
            denom(dd)
            {
            }

            inline explicit CountedMatrix(const size_t nr,
                                          const size_t nc,
                                          const T     &dd) :
            CountedObject(),
            Matrix<T>(nr,nc),
            denom(dd)
            {
            }


            inline virtual ~CountedMatrix() noexcept
            {
            }

            const T denom;

        private:
            Y_Disable_Copy_And_Assign(CountedMatrix);
        };

        class Warden
        {
        public:

            explicit Warden(XML::Log &, const Conservations &);
            virtual ~Warden() noexcept;

            
        private:
            Y_Disable_Copy_And_Assign(Warden);
        };

    }

}

#endif // !Y_Chemical_Plexus_Warden_Included

