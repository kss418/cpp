#include <iostream>
#include <concepts>
#include <utility>
#include <vector>
#include <list>
#include <deque>
#include <set>


template <class T, class U>
concept can_eb = requires (T& c, U&& x){ c.emplace_back(std::forward<U>(x)); };

template <class T, class U>
concept can_pb = requires (T& c, U&& x){ c.push_back(std::forward<U>(x)); };

template <class T, class U>
concept can_ib = requires (T& c, U&& x){ c.insert(c.end(), std::forward<U>(x)); };

template <class T, class U> requires can_eb<T, U>
void emplace_one(T& c, U&& x){
    std::cout << "select 1" << "\n";
    c.emplace_back(std::forward<U>(x));
}

template <class T, class U> requires (!can_eb<T, U> && can_pb<T, U>) 
void emplace_one(T& c, U&& x){
    std::cout << "select 2" << "\n";
    c.push_back(std::forward<U>(x));
}

template <class T, class U> requires (!can_eb<T, U> && !can_pb<T, U> && can_ib<T, U>) 
void emplace_one(T& c, U&& x){
    std::cout << "select 3" << "\n";
    c.insert(c.end(), std::forward<U>(x));
}

template <class T, class U> requires (!can_eb<T, U> && !can_pb<T, U> && !can_ib<T, U>) 
void emplace_one(T&, U&&) = delete;

struct move_only {
    int v;
    explicit move_only(int x) : v(x) {}
    move_only(const move_only&) = delete;
    move_only(move_only&&) = default;
    move_only& operator=(const move_only&) = delete;
    move_only& operator=(move_only&&) = default;
};

int main(){
    std::vector<int> v;
    emplace_one(v, 1);

    std::list<int> lst;
    emplace_one(lst, 10);

    std::deque<int> dq;
    emplace_one(dq, 100);

    std::set<int> st;
    emplace_one(st, 7);

    std::vector<move_only> mv;
    emplace_one(mv, move_only{3});
}

/*
시퀀스/컨테이너 c에 원소 x를 “가장 적절한 방식으로 1개 넣는” emplace_one(c, x)를 구현하라.

우선순위 규칙

c.emplace_back(x)가 가능하면 그걸 호출

아니면 c.push_back(x)가 가능하면 그걸 호출

아니면 c.insert(c.end(), x)가 가능하면 그걸 호출

아니면 컴파일 에러

x는 완전 전달(forwarding)해야 한다: x가 rvalue이면 move 경로가 열리도록.

오버로드가 여러 개 열릴 수 있으므로 우선순위가 확실히 적용되어야 한다.

c.insert(c.end(), x)의 경우 end()가 있는지, insert 시그니처가 맞는지까지 정확히 제약.

컨테이너 종류별 테스트:

std::vector<T>

std::list<T>

std::deque<T> 

std::set<T>
*/