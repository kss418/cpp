#include <iostream>
#include <concepts>
#include <type_traits>
#include <utility>

template <class T, class = void>
struct is_move_assignable : std::false_type{};

template <class T>
struct is_move_assignable<T, std::void_t<
    decltype(std::declval<T&>() = std::declval<T&&>())
>> : std::true_type{};

template <class T, class = void>
struct is_move_constructible : std::false_type{};

template <class T>
struct is_move_constructible<T, std::void_t<
    decltype(T(std::declval<T&&>()))
>> : std::true_type{};

template <class T>
constexpr bool is_move_assignable_v = is_move_assignable<std::remove_cvref_t<T>>::value;

template <class T>
constexpr bool is_move_constructible_v = is_move_constructible<std::remove_cvref_t<T>>::value;

template <class T>
constexpr bool is_swappable_v = is_move_assignable_v<T> && is_move_constructible_v<T>;

template <class T, std::enable_if_t<is_swappable_v<T>, int> = 0>
void swap_like(T& a, T& b){
    T tmp = std::move(b);
    b = std::move(a);
    a = std::move(tmp);
}

template <class T, std::enable_if_t<!is_swappable_v<T>, int> = 0>
void swap_like(T& a, T& b) = delete;

struct good{
    int v{};
    explicit good(int x = 0) : v(x){}
};

struct no_move_assign {
    int v{};
    explicit no_move_assign(int x = 0) : v(x){}
    no_move_assign(no_move_assign&&) = default;          
    no_move_assign& operator=(no_move_assign&&) = delete; 
};

struct no_move_construct {
    int v{};
    explicit no_move_construct(int x = 0) : v(x){}
    no_move_construct(no_move_construct&&) = delete;          
    no_move_construct& operator=(no_move_construct&&) = default; 
};

int main(){
    static_assert(is_swappable_v<good>);
    static_assert(!is_swappable_v<no_move_assign>);
    static_assert(!is_swappable_v<no_move_construct>);
    return 0;
}

/*
swap_like(a,b)

move-assignable, move_constructible일 때만 활성화
*/