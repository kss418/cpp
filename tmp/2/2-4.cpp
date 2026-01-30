#include <iostream>
#include <concepts>
#include <utility>
#include <vector>

template <class T> requires requires (const T& x, std::size_t i){ x.at(i); }
decltype(auto) at_like(const T& x, std::size_t i){
    std::cout << "select x.at(i)" << "\n";
    return x.at(i);
}

template <class T> requires (
    !requires (const T& x, std::size_t i){ x.at(i); } &&
    requires (const T& x, std::size_t i){ x[i]; }
)
decltype(auto) at_like(const T& x, std::size_t i){
    std::cout << "select x[i]" << "\n";
    return x[i];
}

struct neither {};
struct only_index {
    int data[3] = {1, 2, 3};
    int operator[](std::size_t i) const { return data[i]; }
};

int main(){
    std::vector<int> v{1, 2, 3};
    std::cout << at_like(v, 1) << "\n";

    only_index oi;
    std::cout << at_like(oi, 1) << "\n";

    // Neither n{};
    // std::cout << at_like(neither, 1) << "\n";
    return 0;
}

/*
at_like(x, i)를 구현하라.

우선순위:

x.at(i)가 가능하면 그걸 사용

아니면 x[i]가 가능하면 그걸 사용

둘 다 안 되면 컴파일 타임에 제외

요구:
우선순위 분기를 오버로드로 구현할 것
(가능하면 “더 제약이 강한” 후보가 선택되게)
*/