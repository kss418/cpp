#include <iostream>
#include <concepts>
#include <string>

template <class T, class U>
bool equal_like(const T& a, const U& b) requires (
    requires (const T& x, const U& y){ static_cast<bool>(x == y); }
){
    return static_cast<bool>(a == b);
}

template <class T, class U>
bool equal_like(const T& a, const U& b) requires (
    !requires (const T& x, const U& y){ static_cast<bool>(x == y); }
) = delete;

struct bool_proxy {
    int v{};
    explicit bool_proxy(bool b) : v(b ? 1 : 0) {}
    explicit operator bool() const { return v != 0; }
};

struct proxy_eq {
    int v{};
    friend bool_proxy operator==(const proxy_eq& l, const proxy_eq& r) {
        return bool_proxy(l.v == r.v);
    }
};

struct no_eq {
    int v{};
};

int main(){
    int a = 3;
    double b = 3.0;
    std::cout << equal_like(a, b) << "\n";

    std::string s1 = "abc", s2 = "abd";
    std::cout << equal_like(s1, s2) << "\n";

    proxy_eq p1{10}, p2{10};
    std::cout << equal_like(p1, p2) << "\n";

    
    // no_eq p1{10}, p2{10};
    // std::cout << equal_like(p1, p2) << "\n";

    return 0;
}

/*
equal_like(a, b)를 구현하라.

a == b가 유효하면 그 결과를 bool로 변환해서 반환

반환은 bool 

a == b가 유효하지 않으면 컴파일 에러가 나야 함

a == b의 결과 타입이 bool이 아닐 수도 있으므로 제약을 걸어라.

T, U가 서로 다른 타입일 때도 동작해야 함.
*/