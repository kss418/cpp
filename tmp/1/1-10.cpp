#include <iostream>
#include <utility>
#include <type_traits>
#include <concepts>
#include <functional>

template <class T, class U>
concept AllLv = std::is_lvalue_reference_v<T> && std::is_lvalue_reference_v<U>;

template <class T, class U, class F> requires (AllLv<T, U>)
constexpr decltype(auto) best_of_two(T&& a, U&& b, const F& cmp){
    if (std::invoke(cmp, a, b)) return (a);
    return (b);
}

template <class T, class U, class F> requires (!AllLv<T, U>)
constexpr std::common_type_t<std::remove_cvref_t<T>, std::remove_cvref_t<U>> best_of_two(T&& a, U&& b, const F& cmp){
    using R = std::common_type_t<std::remove_cvref_t<T>, std::remove_cvref_t<U>>;
    if (std::invoke(cmp, a, b)) return R(std::forward<T>(a));
    else return R(std::forward<U>(b));
}

int main(){
    constexpr int a=1, b=2;
    constexpr auto cmp = [](auto const& l, auto const& r){ return l < r; };

    static_assert(std::is_same_v<decltype(best_of_two(a,b,cmp)), const int&>);
    static_assert(std::is_same_v<decltype(best_of_two(1,b,cmp)), int>); 
    static_assert(std::is_same_v<decltype(best_of_two(a,2,cmp)), int>);
    static_assert(std::is_same_v<decltype(best_of_two(1,2,cmp)), int>);
    return 0;
}

/*
best_of_two

비교 함수 cmp를 받아 best_of_two(a,b,cmp) 작성

cmp(a,b)가 true면 a, 아니면 b 선택

lvalue면 참조 유지, rvalue 섞이면 값 반환
*/