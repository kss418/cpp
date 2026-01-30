#include <iostream>

template <class T>
T& select_ref(bool cond, T& a, T& b){
    return cond ? a : b;
}

template <class T> 
const T& select_ref(bool cond, const T& a, const T& b){
    return cond ? a : b;
}

int main(){
    return 0;   
}

/*
select_ref

cond에 따라 a 또는 b를 반환

lvalue 입력이면 참조 반환 유지, const도 유지
*/
