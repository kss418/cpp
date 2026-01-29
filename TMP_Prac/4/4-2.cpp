#include <iostream>
#include <type_traits>
#include <tuple>

template <size_t... Is, class Tup>
constexpr auto tuple_select(Tup&& tuple){
    return std::tuple{ std::get<Is>(std::forward<Tup>(tuple))... };
}

int main(){
    return 0;
}

/*
지정한 인덱스 Is...에 해당하는 원소만 뽑아서 새 튜플 생성

예: tuple_select<2,0>(t) → (get<2>(t), get<0>(t))
*/