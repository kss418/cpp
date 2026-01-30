#include <iostream>
#include <utility>
#include <type_traits>
#include <concepts>
#include <memory>

template<class T>
struct type_identity {
    using type = T;
};

template<class T>
using type_identity_t = typename type_identity<T>::type;

template<class T>
void f(T x){ return; }

template<class T>
void g(type_identity_t<T> x){ return; }

int main(){
    f("abc");
    // g("abc");
    g<const char[4]>("abc");
    return 0;
}

/*
type_identity + “우회 추론” 실험

type_identity<T>::type 구현

f(type_identity_t<T> x) 형태로 받으면 추론이 어떻게 달라지는지 관찰
*/