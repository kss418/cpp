#include <iostream>
#include <type_traits>
#include <utility>
#include <tuple>
#include <functional>
#include <concepts>

template <class F, class Tup, size_t... Is> requires(
    ((std::invocable<F&, decltype(std::get<Is>(std::declval<Tup&>()))> &&
    std::assignable_from<
        decltype(std::get<Is>(std::declval<Tup&>())),
        std::invoke_result_t<F&, decltype(std::get<Is>(std::declval<Tup&>()))>
    >) && ...)
)
void tuple_transform_inplace_impl(F& f, Tup& tup, std::index_sequence<Is...>){
    ((std::get<Is>(tup) = std::invoke(f, std::get<Is>(tup))), ...);
}

template <class F, class Tup>
void tuple_transform_inplace(F&& f, Tup& tup){
    constexpr size_t sz = std::tuple_size_v<std::remove_cvref_t<Tup>>;
    tuple_transform_inplace_impl(f, tup, std::make_index_sequence<sz>{});
}

int main(){
    auto tup = std::tuple{1, 2.5, std::string{"hi"}};
    tuple_transform_inplace([](auto&& x) {
        using T = std::remove_cvref_t<decltype(x)>;
        if constexpr (std::is_same_v<T, int>) return x + 10;           
        else if constexpr (std::is_same_v<T, double>) return x * 2.0;      
        else return x + "!";                                                
    }, tup);

    std::cout << std::get<0>(tup) << " " << std::get<1>(tup) << " " << std::get<2>(tup);
    return 0;
}

/*
튜플을 새로 만들지 말고, 각 원소를 f(elem) 결과로 제자리 대입

f(elem)의 결과가 해당 원소 타입에 대입 가능해야 함

tup은 lvalue만 받도록 제한
*/