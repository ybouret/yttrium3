#include "y/utest/driver.hpp"
#include "y/libc/block/zero.h"
#include "y/libc/block/zeroed.h"
#include "y/core/max.hpp"
#include "y/libc/sort.h"
#include "y/ascii/plural.hpp"

#include <iostream>
#include <cassert>
#include <cstring>

namespace Yttrium
{
    namespace UTest
    {
        Driver:: ~Driver() noexcept
        {
            Yttrium_BZero(proc,capacity*sizeof(Proc));
        }

        Driver:: Driver(Proc * const procEntry, const size_t procCount) noexcept :
        proc(procEntry),
        size(0),
        capacity(procCount),
        width(0)
        {
            assert( Yttrium_Zeroed(proc,capacity*sizeof(Proc)) );
        }

        Proc * Driver:: search(const char * const name) noexcept
        {
            assert(0!=name);
            for(size_t i=0;i<size;++i) {
                Proc * const p = proc+i;
                if( 0 == strcmp(name,p->name) )
                    return p;
            }
            return 0;
        }


        static inline int CompareProcs(const void *const lhs,
                                       const void *const rhs,
                                       void * const) noexcept
        {
            return strcmp(static_cast<const Proc *>(lhs)->name,
                          static_cast<const Proc *>(rhs)->name);
        }

        void Driver:: operator()(CFunction const func, const char * const name) noexcept
        {
            assert(0!=name);
            assert(0!=func);

            if(size>=capacity)
            {
                std::cerr << "Exceeded " << capacity << " tests!" << std::endl;
                exit(1);
            }

            if(search(name))
            {
                std::cerr << "Multiple '" << name << "'" << std::endl;
                exit(2);
            }

            Proc &p = proc[size++];
            p.func = func;
            p.name = name;
            InSituMax(width,strlen(name));
            Proc tmp = { 0, 0};
            Yttrium_Sort(proc,size,sizeof(Proc),CompareProcs,0,&tmp);
        }

        void Driver:: display() const
        {
            for(size_t i=0;i<size;++i)
            {
                const Proc & p = proc[i];
                const size_t n = strlen(p.name);
                std::cerr << '\t' << '[' << p.name << ']';
                for(size_t k=n;k<=width;++k) std::cerr << ' ';
                std::cerr << " #" << (i+1) << std::endl;
            }
        }

        size_t Driver:: countContaining(const char * const name) const noexcept
        {
            assert(0!=name);
            size_t        count = 0;
            const size_t  nameLength = strlen(name);
            for(size_t i=0;i<size;++i)
            {
                const char * const big = proc[i].name;
                if(strlen(big)>=nameLength && strstr(big,name))
                    ++count;
            }
            return count;
        }

        void Driver:: printContaining(const char *const name) const
        {
            assert(0!=name);
            const size_t  nameLength = strlen(name);
            for(size_t i=0;i<size;++i)
            {
                const Proc       & p   = proc[i];
                const char * const big = p.name;
                if(strlen(big)>=nameLength && strstr(big,name))
                {
                    std::cerr << '\t' << p.name << std::endl;
                }
            }
        }


        int  Driver:: operator()(int argc,char **argv)
        {
            assert(argc>0);
            assert(argv!=0);

            if(argc<=1)
            {
                std::cerr << '#' << argv[0] << " = " << size << std::endl;
                display();
                return 0;
            }
            else
            {
                const char * const name = argv[1];
                Proc * const       proc = search(name);
                if(proc)
                    return proc->func(--argc,++argv);
                else
                {
                    std::cerr << "no [" << name << "] in" << argv[0] << std::endl;
                    const size_t n = countContaining(name);
                    if(n>0)
                    {
                        std::cerr << "maybe you meant (" << n << " matching test" << ASCII::Plural::s(n) << ") :" << std::endl;
                        printContaining(name);
                    }
                    return 0;
                }
            }
        }


    }

}
