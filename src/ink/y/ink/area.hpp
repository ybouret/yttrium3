//! \file

#ifndef Y_Ink_Area_Included
#define Y_Ink_Area_Included 1

#include "y/concurrent/splitting/leap2d.hpp"

namespace Yttrium
{
    namespace Ink
    {

        typedef Concurrent::Splitting::Leap2D<unit_t> Leap;
        typedef Leap::vertex_t                        Vertex;

        
        class Area : public Leap
        {
        public:
            explicit Area(const unit_t W, const unit_t H) noexcept;
            virtual ~Area() noexcept;
            Area(const Area &) noexcept;



        private:
            Y_Disable_Assign(Area);
        };

    }
}

#endif // !Y_Ink_Area_Included

