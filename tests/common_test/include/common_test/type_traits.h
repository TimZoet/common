#pragma once

////////////////////////////////////////////////////////////////
// Module includes.
////////////////////////////////////////////////////////////////

#include "bettertest/mixins/compare_mixin.h"
#include "bettertest/tests/unit_test.h"

namespace test
{
    class TypeTraits : public bt::UnitTest<TypeTraits, bt::CompareMixin>
    {
    public:
        void operator()() override;
    };
}  // namespace test
