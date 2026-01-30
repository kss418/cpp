#include <iostream>
#include <type_traits>

template <class T>
using norm_t = std::remove_cvref_t<T>;

template <class T, class... Args>
std::size_t type_count(const Args&...){
    return (0 + ... + (std::is_same_v<norm_t<T>, norm_t<Args>> ? 1u : 0u));
}

int main(){
    std::cout << type_count<int>(1, 2, 3u, 2LL);
    return 0;
}

/*
type_count<T>(args...)

인자 중 T와 “같은 타입” 개수.
*/