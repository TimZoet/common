#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <memory>
#include <optional>
#include <tuple>
#include <vector>

////////////////////////////////////////////////////////////////
// Pointer to member.
////////////////////////////////////////////////////////////////

template<typename T>
struct member_pointer_value;

template<typename T, typename M>
struct member_pointer_value<M T::*>
{
    using type = M;
};

/**
 * \brief Get value type from a pointer to member type.
 */
template<typename T>
using member_pointer_value_t = typename member_pointer_value<T>::type;

template<typename T>
struct member_pointer_class;

template<typename T, typename M>
struct member_pointer_class<M T::*>
{
    using type = T;
};

/**
 * \brief Get class type from a pointer to member type.
 */
template<typename T>
using member_pointer_class_t = typename member_pointer_class<T>::type;

template<typename...>
struct is_same_class_member_pointer : std::false_type
{
};

template<typename T, typename... Ms>
struct is_same_class_member_pointer<Ms T::*...> : std::true_type
{
};

/**
 * \brief If all pointers to members point to a member of the same class this value will be true.
 */
template<auto... Ms>
inline constexpr bool is_same_class_member_pointer_v = is_same_class_member_pointer<decltype(Ms)...>::value;

////////////////////////////////////////////////////////////////
// std::tuple
////////////////////////////////////////////////////////////////

template<typename... Ts>
struct _is_tuple : std::false_type
{
};

template<typename... Ts>
struct _is_tuple<std::tuple<Ts...>> : std::true_type
{
};

template<typename Tuple>
concept is_tuple = _is_tuple<Tuple>::value;

/**
 * \brief Concatenate a new element type to a tuple type.
 * \tparam Tuple Tuple type.
 * \tparam T New element type.
 */
template<is_tuple Tuple, typename T>
using tuple_cat_t = decltype(std::tuple_cat(std::declval<Tuple>(), std::declval<std::tuple<T>>()));

template<typename Tuple0, typename Tuple1>
struct tuple_merge
{
    using type = Tuple0;
};

template<is_tuple Tuple0>
struct tuple_merge<Tuple0, std::tuple<>>
{
    using type = Tuple0;
};

template<is_tuple Tuple0, typename T, typename... Ts>
struct tuple_merge<Tuple0, std::tuple<T, Ts...>> : tuple_merge<tuple_cat_t<Tuple0, T>, std::tuple<Ts...>>
{
};

/**
 * \brief Merge the element types of two tuples into one tuple type.
 * \tparam Tuple0 First tuple.
 * \tparam Tuple1 Second tuple.
 */
template<is_tuple Tuple0, is_tuple Tuple1>
using tuple_merge_t = typename tuple_merge<Tuple0, Tuple1>::type;

template<typename T, typename Tuple>
struct tuple_has_type;

template<typename T>
struct tuple_has_type<T, std::tuple<>> : std::false_type
{
};

template<typename T, typename U, typename... Ts>
struct tuple_has_type<T, std::tuple<U, Ts...>> : tuple_has_type<T, std::tuple<Ts...>>
{
};

template<typename T, typename... Ts>
struct tuple_has_type<T, std::tuple<T, Ts...>> : std::true_type
{
};

/**
 * \brief Check if tuple contains the element type.
 * \tparam T Element type.
 * \tparam Tuple Second tuple.
 */
template<typename T, typename Tuple>
concept tuple_contains_type = is_tuple<Tuple> && tuple_has_type<T, Tuple>::value;

template<typename Tuple, typename... Ts>
struct tuple_unique
{
    using type = Tuple;
};

template<typename Tuple, typename T, typename... Ts>
struct tuple_unique<Tuple, std::tuple<T, Ts...>> : tuple_unique<Tuple, std::tuple<Ts...>>
{
};

template<typename Tuple, typename T, typename... Ts>
    requires(!tuple_contains_type<T, Tuple>)
struct tuple_unique<Tuple, std::tuple<T, Ts...>> : tuple_unique<tuple_cat_t<Tuple, T>, std::tuple<Ts...>>
{
};

template<typename Tuple>
struct tuple_unique<Tuple, std::tuple<>> : tuple_unique<Tuple>
{
};

/**
 * \brief Discard all duplicate element types in a tuple. The first occurrence of each element type is maintained, subsequent same types are thrown away.
 * \tparam Tuple Tuple type.
 */
template<is_tuple Tuple>
using tuple_unique_t = typename tuple_unique<std::tuple<>, Tuple>::type;

template<is_tuple Tuple>
constexpr bool is_unique_tuple = std::same_as<Tuple, tuple_unique_t<Tuple>>;

template<typename Superset, typename... Ts>
struct tuple_subset : std::false_type
{
};

template<>
struct tuple_subset<std::tuple<>, std::tuple<>> : std::true_type
{
};

template<typename Superset, typename T, typename... Ts>
struct tuple_subset<Superset, std::tuple<T, Ts...>> : std::false_type
{
};

template<typename Superset, typename T, typename... Ts>
    requires(tuple_contains_type<T, Superset>)
struct tuple_subset<Superset, std::tuple<T, Ts...>> : tuple_subset<Superset, std::tuple<Ts...>>
{
};

template<typename Superset>
struct tuple_subset<Superset, std::tuple<>> : std::true_type
{
};

/**
 * \brief Check if all element types in subset are contained in superset. Note that this does not take into account element order or duplicates.
 * \tparam Subset Tuple type.
 * \tparam Superset Tuple type.
 */
template<typename Subset, typename Superset>
concept tuple_is_subset = is_tuple<Subset> && is_tuple<Superset> && tuple_subset<Superset, Subset>::value;

template<is_tuple Tuple, int64_t Index>
struct tuple_index_wrapped
{
    static constexpr size_t value = static_cast<size_t>(Index);
};

template<is_tuple Tuple, int64_t Index>
    requires(Index < 0)
struct tuple_index_wrapped<Tuple, Index>
{
    static constexpr size_t value = static_cast<size_t>(
      (static_cast<int64_t>(std::tuple_size_v<Tuple>) + Index % static_cast<int64_t>(std::tuple_size_v<Tuple>)) %
      static_cast<int64_t>(std::tuple_size_v<Tuple>));
};

/**
 * \brief Wrap a signed integer index around the length of the tuple type list.
 * I in [0, std::tuple_size_v<Tuple>) is returned as-is.
 * I < 0 is returned as std::tuple_size_v<Tuple> + I % std::tuple_size_v<Tuple>.
 * \tparam Tuple Tuple type.
 * \tparam I Index.
 */
template<is_tuple Tuple, int64_t I>
inline constexpr size_t tuple_index_wrapped_v = tuple_index_wrapped<Tuple, I>::value;

/**
 * \brief Get the element type at the wrapped index.
 * \tparam Tuple Tuple type.
 * \tparam I Index.
 */
template<is_tuple Tuple, int64_t I>
using tuple_element_wrapped_t = std::tuple_element_t<tuple_index_wrapped_v<Tuple, I>, Tuple>;

template<typename Tuple, int64_t...>
struct tuple_swizzle
{
    using type = std::tuple<>;
};

template<is_tuple Tuple, int64_t I, int64_t... Is>
struct tuple_swizzle<Tuple, I, Is...>
{
    using type =
      tuple_merge_t<std::tuple<tuple_element_wrapped_t<Tuple, I>>, typename tuple_swizzle<Tuple, Is...>::type>;
};

/**
 * \brief Get a tuple type with the element types of the input tuple at each index. Returned tuple will have sizeof...(Is) elements. 
 * \tparam Tuple Tuple type.
 * \tparam Is Indices.
 */
template<is_tuple Tuple, int64_t... Is>
using tuple_swizzle_t = typename tuple_swizzle<Tuple, Is...>::type;

////////////////////////////////////////////////////////////////
// std::vector
////////////////////////////////////////////////////////////////

template<typename T>
struct is_vector : std::false_type
{
};

template<typename T>
struct is_vector<std::vector<T>> : std::true_type
{
};

template<typename T>
inline constexpr bool is_vector_v = is_vector<T>::value;


////////////////////////////////////////////////////////////////
// std::optional
////////////////////////////////////////////////////////////////

template<typename T>
struct is_optional : std::false_type
{
};

template<typename T>
struct is_optional<std::optional<T>> : std::true_type
{
};

template<typename T>
inline constexpr bool is_optional_v = is_optional<T>::value;

////////////////////////////////////////////////////////////////
// std::unique_ptr
////////////////////////////////////////////////////////////////

template<typename T>
struct is_unique_ptr : std::false_type
{
};

template<typename T, typename D>
struct is_unique_ptr<std::unique_ptr<T, D>> : std::true_type
{
};

template<typename T>
inline constexpr bool is_unique_ptr_v = is_unique_ptr<std::remove_cvref_t<T>>::value;

////////////////////////////////////////////////////////////////
// std::shared_ptr
////////////////////////////////////////////////////////////////

template<typename T>
struct is_shared_ptr : std::false_type
{
};

template<typename T>
struct is_shared_ptr<std::shared_ptr<T>> : std::true_type
{
};

template<typename T>
inline constexpr bool is_shared_ptr_v = is_shared_ptr<std::remove_cvref_t<T>>::value;


////////////////////////////////////////////////////////////////
// Conversions.
////////////////////////////////////////////////////////////////

template<class T, class U>
concept explicitly_convertible_to = requires(T t) { static_cast<U>(t); };
