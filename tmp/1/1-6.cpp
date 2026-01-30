#include <iostream>
#include <utility>
#include <type_traits>
#include <concepts>
#include <memory>

template <class T>
struct remove_ref{ using type = T; };

template <class T>
struct remove_ref<T&>{ using type = T; };

template <class T>
struct remove_ref<T&&>{ using type = T; };

template <class T>
struct remove_cv{ using type = T; };

template <class T>
struct remove_cv<const T>{ using type = T; };

template <class T>
struct remove_cv<volatile T>{ using type = T; };

template <class T>
struct remove_cv<const volatile T>{ using type = T; };

template <class T>
struct remove_cvref{ using type = typename remove_cv<typename remove_ref<T>::type>::type; };

int main(){
    static_assert(std::is_same_v<remove_cvref<const int&>::type, int>);
    static_assert(std::is_same_v<remove_cvref<volatile int&&>::type, int>);
    static_assert(std::is_same_v<remove_cvref<const volatile int&>::type, int>);
    return 0;
}

/*
remove_cvref 직접 구현

const/volatile + &/&& 제거한 remove_cvref<T>::type 구현

std::remove_cvref_t 사용 금지
*/