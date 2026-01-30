#include <iostream>
#include <utility>
#include <type_traits>

template <class T>
const T& max_like(const T& a, const T& b){
    return a > b ? a : b;
}

template<class T>
T max_like(T&& a, const T& b) requires (!std::is_lvalue_reference_v<T>){
    return a > b ? std::forward<T>(a) : T(b);
}

template<class T> 
T max_like(const T& a, T&& b) requires (!std::is_lvalue_reference_v<T>){
    return a > b ? T(a) : std::forward<T>(b);
}

template<class T> 
T max_like(T&& a, T&& b) requires (!std::is_lvalue_reference_v<T>){
    return a > b ? std::forward<T>(a) : std::forward<T>(b);
}

int main(){
    return 0;   
}

/*
max_like

1차: (lvalue,lvalue)면 const T& 반환

2차: rvalue가 섞이면 값 반환으로 안전 처리(오버로드 분리 가능)
*/