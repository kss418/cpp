#include <iostream>
#include <utility>
#include <type_traits>

template <class... Fs>
struct overloaded : Fs...{
    using Fs::operator()...;
};

template <class... Fs>
auto overload_set(Fs&&... fs){
    return overloaded<std::remove_cvref_t<Fs>...>{ std::forward<Fs>(fs)... };
}

int main(){
    auto ov = overload_set(
        [](int){return 1;},
        [](double){return 2;},
        [](auto&&){return 3;}
    );
    std::cout << ov(1) << " " << ov(3.14) << " " << ov('x');
    return 0;
}

/*
overload_set는 여러 callable을 받아 하나의 객체로 합성

auto ov = overload_set(
  [](int){...},
  [](std::string_view){...},
  [](auto&&){...}
);

상속 + using을 이용한 classic overloaded 패턴을 variadic로 만들 것

perfect forwarding
*/