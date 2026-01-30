#include <iostream>
#include <tuple>
#include <utility>
#include <concepts>
#include <type_traits>

template<template<class> class Pred, class T>
concept bool_pred = requires{
    { Pred<T>::value } -> std::convertible_to<bool>;
};

template<template<class> class Pred, class Tup, std::size_t... Is>
consteval bool tuple_pred_impl(std::index_sequence<Is...>) {
    using Base = std::remove_reference_t<Tup>;
    return (bool_pred<Pred, std::remove_cvref_t<std::tuple_element_t<Is, Base>>> && ...);
}

template<template<class> class Pred, class Tup>
concept tuple_pred =
    tuple_pred_impl<Pred, Tup>(std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<Tup>>>{});


template<template<class> class Pred, class Tup> requires tuple_pred<Pred, Tup>
decltype(auto) tuple_filter_types(Tup&& tup){
    constexpr size_t sz = std::tuple_size_v<std::remove_cvref_t<Tup>>;
    auto pick = [&]<std::size_t I>() -> decltype(auto){
        using T = decltype(std::get<I>(std::forward<Tup>(tup)));
        using U = std::remove_cvref_t<T>;
        if constexpr (Pred<U>::value) return std::forward_as_tuple(std::get<I>(std::forward<Tup>(tup)));
        else return std::tuple<>{};
    };

    auto f = [&]<std::size_t... Is>(std::index_sequence<Is...>) -> decltype(auto){
        return std::tuple_cat(pick.template operator()<Is>()...);
    };

    return f(std::make_index_sequence<sz>{});
}

int main(){
    auto t = std::make_tuple(1, 2.5, 3L, std::string{"hi"}, 'x');
    auto r = tuple_filter_types<std::is_integral>(t);
    std::cout << std::get<0>(r) << " " << std::get<1>(r) << " " << std::get<2>(r) << "\n";
    return 0;
}

/*
Pred<T>::value == true 인 원소 타입만 남긴 튜플을 반환

예: Pred = std::is_integral이면 정수 타입 원소만 남김

tup의 값 범주 보존
*/