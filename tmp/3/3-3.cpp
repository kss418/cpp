#include <iostream>

template <class... Args> requires(
    requires(const Args&... args){
        ((std::cout << args), ...);
    }
)
void print_csv(const Args&... args){
    bool first = true;
    auto f = [&](const auto& v){
        if(!first) std::cout << ", ";
        first = false;
        std::cout << v;
    };
    (f(args), ...);
    std::cout << "\n";
}   

int main(){
    print_csv(1, 2, "abc", -1, 0.2);
    return 0;
}

/*
print_csv(args...)

a,b,c 형태로 출력(구분자 포함), 마지막에 개행.
*/