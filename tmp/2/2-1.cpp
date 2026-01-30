#include <iostream>
#include <concepts>
#include <type_traits>
#include <utility>
#include <vector>

template <class T, class = void>
struct is_streamable : std::false_type{};

template <class T>
struct is_streamable<T, std::void_t<
    decltype(std::declval<std::ostream&>() << std::declval<const T&>())
>> : std::true_type{};

template <class T>
constexpr bool is_streamable_v = is_streamable<T>::value;

template <class T, std::enable_if_t<is_streamable_v<T>, int> = 0> 
void print(const T& x){
    std::cout << x << "\n";
} 

template <class T, std::enable_if_t<!is_streamable_v<T>, int> = 0> 
void print(const T& x){
    std::cout << "N/A" << "\n";
} 

int main(){
    std::vector <int> arr = {1, 2, 3};
    int x = 3;

    print(x);
    print(arr);
    return 0;
}

/*
print(x)

streamable이면 출력, 아니면 "N/A" 출력 (컴파일 분기)

std::ostream& os; os << x;가 유효한 식인지를 검사
*/