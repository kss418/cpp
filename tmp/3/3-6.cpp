#include <iostream>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <sstream>

template<class... Args> requires(
    requires(std::ostream& os, const Args&... args){ ((os << args), ...); }
)
std::string join_to_string(std::string_view delim, const Args&... args){
    bool first = true; std::ostringstream oss;
    auto f = [&](const auto& v){
        if(!first) oss << delim;
        first = false;
        oss << v;
    };
    (f(args), ...);
    return oss.str();
}

int main(){
    std::cout << join_to_string(", ", 1, "x", 3.14) << "\n";    
    return 0;
}

/*
결과: "x<delim>y<delim>z" 형태의 std::string

첫 원소 전에는 delim 없음

빈 팩이면 "" 반환

args가 std::ostream << 가능할 때만 허용되도록 제약 걸기
*/