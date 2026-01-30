#include <iostream>
#include <utility>
#include <functional>
#include <tuple>
#include <type_traits>

template <class F, class TA, class TB> requires (
    std::tuple_size_v<std::remove_cvref_t<TA>> ==
    std::tuple_size_v<std::remove_cvref_t<TB>>
)
void zip_for_each(F&& f, TA&& a, TB&& b){
    constexpr std::size_t N = std::tuple_size_v<std::remove_cvref_t<TA>>;
    [&]<std::size_t... I>(std::index_sequence<I...>){
        auto&& fn = f;
        (std::invoke(fn, 
            std::get<I>(std::forward<TA>(a)), 
            std::get<I>(std::forward<TB>(b))), ...);
    }(std::make_index_sequence<N>{});
}

struct checker {
    int idx = 0;
    template <class X, class Y>
    void operator()(X&& x, Y&& y) {
        std::cout << "call#" << idx++ << " : ";
        std::cout << (std::is_lvalue_reference_v<X> ? "X=L " : "X=R ");
        std::cout << (std::is_lvalue_reference_v<Y> ? "Y=L " : "Y=R ");
        std::cout << "| x=" << x << ", y=" << y << "\n";
    }
};

int main(){
    std::tuple<int, std::string> t1{1, "hello"};
    std::tuple<double, std::string_view> t2{3.14, "sv"};

    checker c1;
    zip_for_each(c1, t1, t2);

    checker c2;
    zip_for_each(c2, std::move(t1), std::move(t2));
    return 0;
}

/*
zip_for_each(f, a..., b...)

두 팩을 “같은 길이”로 묶어 처리

sizeof...(As) == sizeof...(Bs)가 아니면 컴파일 에러(static_assert 또는 requires)

i번째 원소 쌍에 대해 f(ai, bi)를 순서대로 호출

완전 전달: f와 원소 모두 forwarding 고려

호출 순서 보장: 출력 같은 부작용이 있으면 순서가 안정적이어야 함
*/