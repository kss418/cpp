#include <iostream>
#include <concepts>
#include <utility>

template <class T, class U>
decltype(auto) min_like(T&& a, U&& b) requires(
    requires (const T& x, const U& y){ static_cast<bool>(x < y); }
){
    if(a < b) return std::forward<T>(a);
    return std::forward<U>(b);
}

template <class T, class U>
decltype(auto) min_like(T&& a, U&& b) requires(
    !requires (const T& x, const U& y){ static_cast<bool>(x < y); } &&
    requires (const T& x, const U& y){ static_cast<bool>(x.size() < y.size()); }
){
    if(a.size() < b.size()) return std::forward<T>(a);
    return std::forward<U>(b);
}

template <class T, class U>
decltype(auto) min_like(T&& a, U&& b) requires(
    !requires (const T& x, const U& y){ static_cast<bool>(x < y); } &&
    !requires (const T& x, const U& y){ static_cast<bool>(x.size() < y.size()); }
) = delete;

struct only_size {
    std::string s;
    std::size_t size() const { return s.size(); }
};

struct neither{};

int main(){
    int a = 1, b = 2;
    static_assert(std::is_lvalue_reference_v<decltype(min_like(a, b))>);

    only_size x{"hello"}, y ={"hi"};
    static_assert(std::is_lvalue_reference_v<decltype(min_like(x, y))>);

    // neither n1, n2;
    // min_like(n1, n2);

    return 0;
}

/*
min_like(a, b)를 구현하라.

우선순위 규칙

1. a < b가 가능하고 결과가 bool로 변환 가능하면

b가 더 작으면 b, 아니면 a를 반환

1)이 불가능하면, size_of(a)/size_of(b) 형태로 “크기 비교”가 가능할 때(= a.size()가 가능하고 b.size()도 가능)

2. size()가 작은 쪽을 반환

3. 둘 다 불가능하면 컴파일 에러

요구 사항(중간 난이도 포인트)

반환은 decltype(auto)로 하고, 참조를 유지하도록 설계해라.
즉, a/b가 lvalue면 lvalue 참조로 반환되어야 함.
*/