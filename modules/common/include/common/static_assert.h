#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

template<bool flag = false>
constexpr void constexpr_static_assert()
{
    static_assert(flag, "No match");
}