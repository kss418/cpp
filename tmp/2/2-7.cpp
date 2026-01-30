#include <iostream> 
#include <concepts> 
#include <string_view>
#include <type_traits>
#include <string>
#include <vector>

template <class T>
std::string_view read_view(T&& x) requires(
    std::convertible_to<T, std::string_view> &&
    std::is_lvalue_reference_v<T> &&
    !std::same_as<std::remove_cvref_t<T>, const char*>
){
    std::cout << "select 1" << "\n";
    return std::string_view(x);
}

template <class T>
std::string_view read_view(T&& x) requires(
    requires(const std::remove_reference_t<T>& v){ static_cast<const char*>(v.data()); v.size(); } &&
    std::is_lvalue_reference_v<T> &&
    !std::convertible_to<T, std::string_view>
){
    std::cout << "select 2" << "\n";
    return std::string_view(x.data(), x.size());
}

template <class T>
std::string_view read_view(T&& x) requires(
    std::same_as<std::remove_cvref_t<T>, const char*>
){
    std::cout << "select 3" << "\n";
    return std::string_view(x);
}

struct data_size {
    std::vector<char> buf;
    const char* data() const { return buf.data(); }
    std::size_t size() const { return buf.size(); }
};

int main(){
    std::string s = "hello";
    std::string_view sv1 = read_view(s);

    data_size ds = { std::vector<char>{'w','o','r','l','d'} };
    std::string_view sv2 = read_view(ds);

    const char* cstr = "c-string";
    std::string_view sv3 = read_view(cstr);

    // auto bad = read_view(std::string{"tmp"});
    return 0;
}

/*
read_view(x)가 **가능하면 std::string_view**를 반환하도록 구현하라. 단, 수명 문제를 피해야 한다.

우선순위 규칙

x가 이미 std::string_view로 암시적 변환 가능하고, 그 변환이 lvalue에서 안전하면 std::string_view(x) 반환

아니면 x.data()와 x.size()가 가능하고,

x.data()가 const char*로 변환 가능이며

x가 lvalue일 때만 허용

이 경우 std::string_view(x.data(), x.size()) 반환

아니면 const char*(C-string)일 때만 std::string_view(x) 허용

그 외는 컴파일 에러

read_view(std::string{"tmp"}) 같은 rvalue에서 2) 경로가 열리면 안 된다.

즉, “가능한 연산”만 보지 말고 **value category(lvalue/rvalue)**까지 제약에 포함하라.
*/