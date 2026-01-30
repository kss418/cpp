#include <iostream>
#include <utility>
#include <type_traits>

template <class T>
std::pair<const T&, const T&> minmax_like(const T& a, const T& b){
    using P = std::pair<const T&, const T&>;
    return (b > a) ? P{a, b} : P{b, a};
}

template <class T> requires(!std::is_lvalue_reference_v<T>)
std::pair<std::remove_cvref_t<T>, std::remove_cvref_t<T>> minmax_like(T&& a, T&& b){
    if(b > a) return { std::forward<T>(a), std::forward<T>(b) };
    return { std::forward<T>(b), std::forward<T>(a) };
}

template <class T> requires(!std::is_lvalue_reference_v<T>)
std::pair<std::remove_cvref_t<T>, std::remove_cvref_t<T>> minmax_like(const T& a, T&& b){
    if(b > a) return { a, std::forward<T>(b) };
    return { std::forward<T>(b), a };
}

template <class T> requires(!std::is_lvalue_reference_v<T>)
std::pair<std::remove_cvref_t<T>, std::remove_cvref_t<T>> minmax_like(T&& a, const T& b){
    if(b > a) return { std::forward<T>(a), b };
    return { b, std::forward<T>(a) };
}

int main(){
    return 0;   
}

/*
minmax_like

(min, max)를 반환

lvalue-only: std::pair<const T&, const T&>

rvalue 포함: std::pair<T, T>(또는 remove_cvref_t 기반) 값 반환
*/