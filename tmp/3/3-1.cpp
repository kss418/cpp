#include <iostream>
#include <utility>

template <class... Ts> requires requires (Ts&&... xs){
    (0 + ... + std::forward<Ts>(xs));
}
auto sum_all(Ts&&... xs){
    return (0 + ... + std::forward<Ts>(xs));
}

int main(){
    std::cout << sum_all(1, 3.2, 4.1, -1, -2);
    return 0;
}

/*
sum_all(args...)

여러 인자를 더해 합 반환.
*/