#include <iostream>
#include <type_traits>
#include <functional>
#include <tuple>
#include <utility>
#include <cassert>

template <class F, class Tuple, std::size_t... I>
constexpr auto tuple_map_impl(F& fn, Tuple&& tup, std::index_sequence<I...>) {
    return std::tuple{ std::invoke(fn, std::get<I>(std::forward<Tuple>(tup)))... };
}

template <class F, class Tuple>
constexpr auto tuple_map(F&& f, Tuple&& tup){
    constexpr size_t sz = std::tuple_size_v<std::remove_cvref_t<Tuple>>;
    auto fn = std::forward<F>(f);
    return tuple_map_impl(fn, std::forward<Tuple>(tup), std::make_index_sequence<sz>{});
}

int main(){
    auto t = std::make_tuple(1, 2, 3);
    auto r = tuple_map([](int x){ return x * 10; }, t);
    static_assert(std::is_same_v<decltype(r), std::tuple<int,int,int>>);
    assert((r == std::tuple{10,20,30}));
    return 0;
}

/*
tup의 각 원소 x에 대해 f(x)를 적용한 결과를 새 튜플로 만든다.

return std::tuple{ f(get<0>(tup)), f(get<1>(tup)), ... };

f의 결과가 참조일 수도 있음 (T& 반환).

std::tuple은 참조 타입도 담을 수 있지만, 실수하면 dangling 위험이 생김.

f가 move-only일 수 있음.

팩 확장에서 std::forward<F>(f)를 여러 번 쓰면 “한 번만 move”가 아니라 “여러 번 move 시도” 문제가 생길 수 있음.
*/