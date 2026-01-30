#include <iostream>
#include <utility>
#include <type_traits>
#include <concepts>
#include <memory>
#include <tuple>

template <std::size_t I, class T>
constexpr decltype(auto) get_nth(T&& x){
    using U = std::remove_cvref_t<T>;
    static_assert(I < std::tuple_size_v<U>);
    return std::get<I>(std::forward<T>(x));
}
int main(){
    constexpr std::tuple <int, int, int> tup = {1, 2, 3};
    constexpr int one = 1;
    constexpr int two = 2;
    constexpr int three = 3;

    static_assert(get_nth<0>(tup) == one);
    static_assert(get_nth<1>(tup) == two);
    static_assert(get_nth<2>(tup) == three);
    return 0;
}

/*
get_nth<I> (tuple/pair 접근)

std::tuple 또는 std::pair에서 I번째 요소 반환

요소 접근 시 참조/const 정확히 보존
*/