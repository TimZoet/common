#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <type_traits>

template<typename Enum>
requires std::is_enum_v<Enum> constexpr Enum operator|(const Enum lhs, const Enum rhs)
{
    using t = typename std::underlying_type<Enum>::type;
    return static_cast<Enum>(static_cast<t>(lhs) | static_cast<t>(rhs));
}

template<typename Enum>
requires std::is_enum_v<Enum> constexpr Enum& operator|=(Enum& lhs, const Enum rhs)
{
    using t = typename std::underlying_type<Enum>::type;
    lhs     = lhs | rhs;
    return lhs;
}

template<typename Enum>
requires std::is_enum_v<Enum> constexpr Enum operator&(const Enum lhs, const Enum rhs)
{
    using t = typename std::underlying_type<Enum>::type;
    return static_cast<Enum>(static_cast<t>(lhs) & static_cast<t>(rhs));
}

template<typename Enum>
requires std::is_enum_v<Enum> constexpr Enum& operator&=(Enum& lhs, const Enum rhs)
{
    using t = typename std::underlying_type<Enum>::type;
    lhs     = lhs & rhs;
    return lhs;
}

template<typename Enum>
requires std::is_enum_v<Enum>
constexpr Enum operator~(const Enum lhs)
{
    using t = std::underlying_type_t<Enum>;
    return static_cast<Enum>(~static_cast<t>(lhs));
}


template<typename Enum>
requires std::is_enum_v<Enum> constexpr auto to_integral(const Enum lhs) -> typename std::underlying_type<Enum>::type
{
    using t = typename std::underlying_type<Enum>::type;
    return static_cast<t>(lhs);
}

template<typename Enum>
requires std::is_enum_v<Enum> constexpr bool any(const Enum lhs)
{
    return static_cast<bool>(lhs);
}

template<typename Enum>
requires std::is_enum_v<Enum> constexpr bool none(const Enum lhs)
{
    return !any(lhs);
}
