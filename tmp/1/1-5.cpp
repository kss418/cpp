#include <iostream>
#include <utility>
#include <type_traits>
#include <concepts>
#include <memory>

template <class T>
struct is_pointer_like : std::false_type{};

template <class T>
struct is_pointer_like<T*> : std::true_type{};

template <class T>
struct is_pointer_like<std::unique_ptr<T>> : std::true_type{};

int main(){
    static_assert(std::is_same_v<is_pointer_like<int>::type, std::false_type>);
    static_assert(std::is_same_v<is_pointer_like<int*>::type, std::true_type>);
    static_assert(std::is_same_v<is_pointer_like<std::unique_ptr<int>>::type, std::true_type>);
    return 0;
}

/*
is_pointer_like

기본 false

T*이면 true (부분 특수화)

std::unique_ptr<T>도 true (부분 특수화)
*/