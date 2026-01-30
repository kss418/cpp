#include <iostream>
#include <utility>
#include <type_traits>
#include <concepts>

template <class V, class L, class R>
using Base = std::remove_cvref_t<V>;

template <class V, class L, class R>
concept SameBase = 
    std::same_as<Base<V, L, R>, std::remove_cvref_t<L>> && 
    std::same_as<Base<V, L, R>, std::remove_cvref_t<R>>;

template <class V, class L, class R>
concept AllLv = 
    std::is_lvalue_reference_v<V> &&
    std::is_lvalue_reference_v<L> &&
    std::is_lvalue_reference_v<R>;

template <class V, class L, class R> requires (SameBase<V, L, R> && AllLv<V, L, R>)
const Base<V, L, R>& clamp_like(V&& v, L&& l, R&& r){
    if(v <= l) return l;
    if(v >= r) return r;
    return v;
}

template <class V, class L, class R> requires (SameBase<V, L, R> && !AllLv<V, L, R>)
Base<V, L, R> clamp_like(V&& v, L&& l, R&& r){
    using T = Base<V, L, R>;
    if(v <= l) return T(std::forward<L>(l));
    if(v >= r) return T(std::forward<R>(r));
    return T(std::forward<V>(v));
}

int main(){
    return 0;   
}

/*
clamp_like

v를 [lo,hi] 범위로 clamp

모두 lvalue면 const T& 반환

rvalue 포함되면 값 반환
*/