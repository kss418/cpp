#include <iostream>
#include <functional>
#include <utility>
#include <concepts>
#include <type_traits>

template<class F, class... Args> requires(
    requires (F& f, Args&&... args){
       ((static_cast<bool>(std::invoke(f, std::forward<Args>(args)))), ...); 
    }
)
bool all_of(F&& f, Args&&... args){
    auto&& fn = f;
    return (true && ... && static_cast<bool>(std::invoke(fn, std::forward<Args>(args))));
}

template<class F, class... Args> requires(
    requires (F& f, Args&&... args){
       ((static_cast<bool>(std::invoke(f, std::forward<Args>(args)))), ...); 
    }
)
bool any_of(F&& f, Args&&... args){
    auto&& fn = f;
    return (false || ... || static_cast<bool>(std::invoke(fn, std::forward<Args>(args))));
}

int main(){
    std::cout << all_of([&](int x){ return x > 0; }, 1, 2, 3, 4) << "\n";
    std::cout << any_of([&](int x){ return x > 0; }, -1, 0, -2, -3) << "\n";
    return 0;
}

/*
all_of(pred, args...) / any_of(...)

pred를 각 args에 적용해 모두 true인지/하나라도 true인지.
*/