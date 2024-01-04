#include "common_test/type_traits.h"

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <memory>

////////////////////////////////////////////////////////////////
// Module includes.
////////////////////////////////////////////////////////////////

#include "common/type_traits.h"

namespace test
{
    void TypeTraits::operator()()
    {
        /*
         * is_unique_ptr
         */

        compareTrue(is_unique_ptr_v<std::unique_ptr<float>>);
        compareTrue(is_unique_ptr_v<const std::unique_ptr<float>>);
        compareTrue(is_unique_ptr_v<std::unique_ptr<const float>>);
        compareTrue(is_unique_ptr_v<const std::unique_ptr<const float>>);
        compareFalse(is_unique_ptr_v<float>);
        compareFalse(is_unique_ptr_v<std::optional<float>>);
        compareFalse(is_unique_ptr_v<std::shared_ptr<float>>);

        /*
         * is_shared_ptr
         */

        compareTrue(is_shared_ptr_v<std::shared_ptr<float>>);
        compareTrue(is_shared_ptr_v<const std::shared_ptr<float>>);
        compareTrue(is_shared_ptr_v<std::shared_ptr<const float>>);
        compareTrue(is_shared_ptr_v<const std::shared_ptr<const float>>);
        compareFalse(is_shared_ptr_v<float>);
        compareFalse(is_shared_ptr_v<std::optional<float>>);
        compareFalse(is_shared_ptr_v<std::unique_ptr<float>>);
    }
}  // namespace test
