//! \file

#ifndef Y_Calculus_SplitWord_Included
#define Y_Calculus_SplitWord_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Calculus
    {

        //______________________________________________________________________
        //
        //
        //
        //! Operations on Words
        //
        //
        //______________________________________________________________________
        struct SplitWord
        {
            template <typename T> struct Make;

            static void Expand(uint8_t  * const target, const uint16_t &source) noexcept; //!< expand \param target small area \param source large word
            static void Expand(uint8_t  * const target, const uint32_t &source) noexcept; //!< expand \param target small area \param source large word
            static void Expand(uint8_t  * const target, const uint64_t &source) noexcept; //!< expand \param target small area \param source large word
            static void Expand(uint16_t * const target, const uint32_t &source) noexcept; //!< expand \param target small area \param source large word
            static void Expand(uint16_t * const target, const uint64_t &source) noexcept; //!< expand \param target small area \param source large word
            static void Expand(uint32_t * const target, const uint64_t &source) noexcept; //!< expand \param target small area \param source large word

            static void Gather(uint16_t & target, const uint8_t  * const source) noexcept; //!< gather \param target large word \param source small area
            static void Gather(uint32_t & target, const uint8_t  * const source) noexcept; //!< gather \param target large word \param source small area
            static void Gather(uint64_t & target, const uint8_t  * const source) noexcept; //!< gather \param target large word \param source small area
            static void Gather(uint32_t & target, const uint16_t * const source) noexcept; //!< gather \param target large word \param source small area
            static void Gather(uint64_t & target, const uint16_t * const source) noexcept; //!< gather \param target large word \param source small area
            static void Gather(uint64_t & target, const uint32_t * const source) noexcept; //!< gather \param target large word \param source small area

        };

        //! split to 8-bits
        template <> struct SplitWord:: Make<uint8_t>
        {
            static uint8_t * From(uint16_t &x, size_t &n) noexcept; //!< \param x input and workspace \param n number of active words \return bytes from x
            static uint8_t * From(uint32_t &x, size_t &n) noexcept; //!< \param x input and workspace \param n number of active words \return bytes from x
            static uint8_t * From(uint64_t &x, size_t &n) noexcept; //!< \param x input and workspace \param n number of active words \return bytes from x
        };

        //! split to 16-bits
        template <> struct SplitWord:: Make<uint16_t>
        {
            static uint16_t * From(uint32_t &x, size_t &n) noexcept; //!< \param x input and workspace \param n number of active words \return words from x
            static uint16_t * From(uint64_t &x, size_t &n) noexcept; //!< \param x input and workspace \param n number of active words \return words from x
        };

        //! split to 32-bits
        template <> struct SplitWord:: Make<uint32_t>
        {
            static uint32_t * From(uint64_t &x, size_t &n) noexcept;//!< \param x input and workspace \param n number of active words \return dwords from x
        };

    }

}

#endif // !Y_Calculus_SplitWord_Included
