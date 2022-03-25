#pragma once

////////////////////////////////////////////////////////////////
// Module includes.
////////////////////////////////////////////////////////////////

#include "bettertest/mixins/compare_mixin.h"
#include "bettertest/tests/unit_test.h"
#include "common/enum_classes.h"

namespace test
{
    class EnumClassOr : public bt::UnitTest<EnumClassOr, bt::CompareMixin>
    {
    public:
        void operator()() override;
    };

    class EnumClassAnd : public bt::UnitTest<EnumClassAnd, bt::CompareMixin>
    {
    public:
        void operator()() override;
    };

    class EnumClassNot : public bt::UnitTest<EnumClassNot, bt::CompareMixin>
    {
    public:
        void operator()() override;
    };

    class EnumClassToIntegral : public bt::UnitTest<EnumClassToIntegral, bt::CompareMixin>
    {
    public:
        void operator()() override;
    };

    class EnumClassReduction : public bt::UnitTest<EnumClassReduction, bt::CompareMixin>
    {
    public:
        void operator()() override;
    };
}  // namespace app
