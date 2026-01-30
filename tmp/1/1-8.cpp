#include <iostream>
#include <utility>
#include <type_traits>
#include <concepts>
#include <memory>

int x = 2;
auto g1(){ return x; }
decltype(auto) g2() { return x; }
decltype(auto) g3() { return (x); }
auto g4() { return (x); }

int main(){
    using g1t = decltype(g1()); // int
    using g2t = decltype(g2()); // int
    using g3t = decltype(g3()); // int&
    using g4t = decltype(g4()); // int
    return 0;
}

/*
return_expr
아래 4개를 작성하고 int x에 대해 반환 타입 비교:

auto g1() { return x; }

decltype(auto) g2() { return x; }

decltype(auto) g3() { return (x); }

auto g4() { return (x); }
*/