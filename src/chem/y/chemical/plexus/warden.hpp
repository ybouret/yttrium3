

#ifndef Y_Chemical_Plexus_Warden_Included
#define Y_Chemical_Plexus_Warden_Included 1

#include "y/chemical/plexus/canon.hpp"
#include "y/container/cxx/array.hpp"

namespace Yttrium
{
    namespace Chemical
    {


        class Warden
        {
        public:
            class Cell : public Object
            {
            public:
                typedef CxxListOf<Cell> List;
                explicit Cell(const Readable<size_t> &,
                              const Matrix<apz>      &);
                virtual ~Cell() noexcept;

                CxxArray<size_t> key;

                Cell * next;
                Cell * prev;

            private:
                Y_Disable_Copy_And_Assign(Cell);
            };

            explicit Warden(XML::Log &,const Canon &);
            virtual ~Warden() noexcept;

            CxxArray<Cell::List> cells;

        private:
            Y_Disable_Copy_And_Assign(Warden);
        };

    }

}

#endif // !Y_Chemical_Plexus_Warden_Included

