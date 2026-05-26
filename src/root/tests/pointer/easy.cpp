
#include "y/pointer/easy.hpp"
#include "y/utest/run.hpp"
#include "y/object/counted.hpp"

using namespace Yttrium;

namespace
{

    class Dummy : public CountedObject
    {
    public:
        explicit Dummy(const int x) : value(x) { std::cerr << "[+] Dummy@" << value; }
        virtual ~Dummy() noexcept
        {
            std::cerr << "[~] Dummy@" << value;
        }

        inline friend std::ostream & operator<<(std::ostream &os, const Dummy &self)
        {
            return os << "Dummy@" << self.value;
        }

        const int value;

    private:
        Y_Disable_Copy_And_Assign(Dummy);
    };
}

Y_UTEST(pointer_easy)
{
    EasyPtr<Dummy> a; std::cerr << a << std::endl;
    a = new Dummy(8);
    
}
Y_UDONE()
