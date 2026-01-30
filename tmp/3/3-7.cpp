#include <iostream>
#include <functional>
#include <concepts>
#include <type_traits>
#include <utility>

template<class Init, class Op, class F>
constexpr auto transform_reduce(Init&& init, Op&& op, F&& transform){
    return std::forward<Init>(init);
}

template<class Init, class Op, class F, class T0, class... Ts> requires(
    std::invocable<F&, T0&&> && 
    std::invocable<Op&, Init&&, std::invoke_result_t<F&, T0&&>>
)
constexpr auto transform_reduce(Init&& init, Op&& op, F&& transform, T0&& x0, Ts&&... xs){
    auto acc = std::invoke(op, 
        std::forward<Init>(init), std::invoke(transform, std::forward<T0>(x0)));

    if constexpr (sizeof...(xs) == 0) return acc;
    else return transform_reduce(std::move(acc), op, transform, std::forward<Ts>(xs)...);
}

int main(){
    auto r = transform_reduce(
        std::string("init"),
        [](std::string a, std::string b){ return "(" + a + "+" + b + ")"; },
        [](const char* s){ return std::string(s); },
        "A", "B", "C"
    );
    
    std::cout << r;
    return 0;
}

/*
transform_reduce(init, op, transform, args...)
std::transform_reduce의 미니 버전(팩 + fold + 타입 추론)

각 x에 transform(x) 적용

누적: init = op(init, transform(x))를 왼쪽부터 수행

반드시 왼쪽 결합(순서 중요)

op/transform 모두 std::invoke로 호출

가능한 한 constexpr 친화적으로(가능하면)

제약:
transform(x)가 유효
op(acc, t)가 유효
빈 팩이면 init 반환
*/