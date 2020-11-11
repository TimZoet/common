#include "common_test/enum_classes.h"

#include <limits>

namespace test
{
    enum class Enum : uint32_t
    {
        N = 0,
        A = 1,
        B = 2,
        C = 4,
        D = 8
    };

    enum class EnumInt16 : int16_t
    {
        A = std::numeric_limits<int16_t>::lowest(),
        B = std::numeric_limits<int16_t>::max()
    };

    enum class EnumUint64 : uint64_t
    {
        A = std::numeric_limits<uint64_t>::lowest(),
        B = std::numeric_limits<uint64_t>::max()
    };

    void EnumClassOr::operator()()
    {
        const auto a = Enum::A;
        const auto b = Enum::B;
        const auto c = Enum::C;
        const auto d = Enum::D;

        compareEQ(a | b, static_cast<Enum>(3));
        compareEQ(c | d, static_cast<Enum>(12));
        compareEQ(a | b | c | d, static_cast<Enum>(15));
        compareEQ(a | a, a);
        compareEQ(c | c, c);
        compareEQ(a | b, b | a);

        auto ab   = Enum::A;
        auto cd   = Enum::C;
        auto abcd = Enum::D;
        ab |= Enum::B;
        cd |= Enum::D;
        abcd |= Enum::C;
        abcd |= Enum::B;
        abcd |= Enum::A;

        compareEQ(ab, static_cast<Enum>(3));
        compareEQ(cd, static_cast<Enum>(12));
        compareEQ(abcd, static_cast<Enum>(15));
    }

    void EnumClassAnd::operator()()
    {
        const auto a = Enum::A;
        const auto b = Enum::B;
        const auto c = Enum::C;
        const auto d = Enum::D;

        compareEQ(a & a, a);
        compareEQ(c & c, c);
        compareEQ(a & b, static_cast<Enum>(0));
        compareEQ(a & b & c & d, static_cast<Enum>(0));

        auto       ab   = Enum::A | Enum::B;
        auto       cd   = Enum::C | Enum::D;
        const auto abcd = ab | cd;
        ab &= Enum::A;
        cd &= Enum::B;

        compareEQ(ab, Enum::A);
        compareEQ(cd, static_cast<Enum>(0));
        compareEQ(abcd & ab, ab);
        compareEQ(abcd & cd, cd);
    }

    void EnumClassToIntegral::operator()()
    {
        const auto a16 = EnumInt16::A;
        const auto b16 = EnumInt16::B;
        const auto a64 = EnumUint64::A;
        const auto b64 = EnumUint64::B;

        compareEQ(to_integral(a16), std::numeric_limits<int16_t>::lowest());
        compareEQ(to_integral(b16), std::numeric_limits<int16_t>::max());
        compareEQ(to_integral(a64), std::numeric_limits<uint64_t>::lowest());
        compareEQ(to_integral(b64), std::numeric_limits<uint64_t>::max());
    }

    void EnumClassReduction::operator()()
    {
        compareTrue(any(Enum::A));
        compareFalse(any(Enum::N));
        compareTrue(none(Enum::N));
        compareFalse(any(Enum::N));
    }
}  // namespace test
