#include "y/stream/libc/output.hpp"
#include "y/utest/run.hpp"
using namespace Yttrium;

namespace
{

    class Base : public Identifiable
    {
    public:
        template <typename NAME> inline
        explicit Base(const NAME &name) : label(name)
        {
            std::cerr << "+Base '" << label << "'" << std::endl;
        }

        explicit Base() : Identifiable(), label()
        {
            std::cerr << "+Base!" << std::endl;
        }

        virtual ~Base() noexcept
        {
        }

        virtual const char * callSign() const noexcept { return label.c_str(); }

        const String label;
    private:
        Y_Disable_Copy_And_Assign(Base);
    };


    class Der1 : public virtual Base
    {
    public:
        template <typename NAME> inline
        explicit Der1(const NAME &name) : Base(name)
        {
            std::cerr << "+Der1 '" << label << "'" << std::endl;
        }

    protected:
        explicit Der1() : Base()
        {
            std::cerr << "+Der1!" << std::endl;
        }

    public:
        virtual ~Der1() noexcept
        {
        }

        void run1()
        {
            std::cerr << "In Der1 '" << label << "'" << std::endl;
        }

    private:
        Y_Disable_Copy_And_Assign(Der1);
    };

    class Der2 : public virtual Base
    {
    public:
        template <typename NAME> inline
        explicit Der2(const NAME &name) : Base(name)
        {
            std::cerr << "+Der2 '" << label << "'" << std::endl;
        }

    protected:
        explicit Der2() : Base()
        {
            std::cerr << "+Der2!" << std::endl;
        }

    public:
        virtual ~Der2() noexcept
        {
        }

        void run2()
        {
            std::cerr << "In Der2 '" << label << "'" << std::endl;
        }

    private:
        Y_Disable_Copy_And_Assign(Der2);
    };

    class Both : public Der1, public Der2
    {
    public:
        template <typename NAME> inline
        explicit Both(const NAME &name) :
        Base(name),
        Der1(),
        Der2()
        {
        }

        inline virtual ~Both() noexcept
        {
        }
    private:
        Y_Disable_Copy_And_Assign(Both);
    };


}

Y_UTEST(stream_output_file)
{
    if(false)
    {
        Both both("hello");
        std::cerr << "label=" << both.label << std::endl;
    }

    if(argc>1)
    {
        OutputFile fp(argv[1]);
        size_t     written = 0;
        const int  toto    = -7;
        written += fp.vbr(toto);
        std::cerr << "written=" << written << std::endl;

        const uint32_t x = 0x12345678;
        written += fp.cbr(x);

        fp("%s","aaaaaaa");
        

    }

}
Y_UDONE()

