#include <iostream>
#include <concepts>
#include <type_traits>
#include <utility>

template <class T>
constexpr bool is_arithmetic_v = 
    std::is_arithmetic<std::remove_cvref_t<T>>::value;

template <class T, class U, std::enable_if_t<
    is_arithmetic_v<T> && is_arithmetic_v<U>, int> = 0>
auto add(T a, U b){
    return a + b;
}

template <class T, class U, std::enable_if_t<
    !is_arithmetic_v<T> || !is_arithmetic_v<U>, int> = 0>
void add(T a, U b) = delete;

int main(){
    return 0;
}

/*
add(a,b)

산술 타입만 허용, 아니면 컴파일 에러 메시지가 나야 함.
*/