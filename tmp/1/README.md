# 1번 연습 문제

| 파일 | 구현 내용 |
| --- | --- |
| `1-1.cpp` | `select_ref` 템플릿으로 조건에 따라 `a` 또는 `b`를 선택하며 lvalue/const 참조를 유지. |
| `1-2.cpp` | `max_like` 오버로드로 lvalue/lvalue는 참조 반환, rvalue 포함 시 값 반환으로 안전하게 `max` 동작 구현. |
| `1-3.cpp` | `minmax_like`로 `(min, max)` 반환하며 lvalue-only는 참조, rvalue 포함 시 값으로 반환. |
| `1-4.cpp` | `clamp_like`로 같은 기반 타입에서 clamp 수행, 모두 lvalue면 참조 반환, rvalue 포함 시 값 반환. |
| `1-5.cpp` | `is_pointer_like` 타입 특성으로 `T*`와 `std::unique_ptr<T>`를 포인터 유사 타입으로 판별. |
| `1-6.cpp` | `remove_ref`, `remove_cv`, `remove_cvref`를 직접 구현해 cv/ref 제거. |
| `1-7.cpp` | `type_identity`와 `type_identity_t`를 정의하고 템플릿 인자 추론 차이를 실험. |
| `1-8.cpp` | `auto`/`decltype(auto)`와 괄호 유무에 따른 반환 타입 차이를 비교. |
| `1-9.cpp` | `get_nth<I>`로 tuple/pair의 I번째 요소 접근 시 참조/const 보존. |
| `1-10.cpp` | `best_of_two`로 비교 함수 기반 선택, lvalue는 참조 유지, rvalue 섞이면 값 반환. |
