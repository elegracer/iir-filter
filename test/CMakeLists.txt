cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

enable_testing()

add_executable (test_butterworth butterworth.cpp)
target_link_libraries(test_butterworth iir)
add_test(TestButterworth test_butterworth)

add_executable (test_chebyshev1 chebyshev1.cpp)
target_link_libraries(test_chebyshev1 iir)
add_test(TestChebyshev1 test_chebyshev1)

add_executable (test_chebyshev2 chebyshev2.cpp)
target_link_libraries(test_chebyshev2 iir)
add_test(TestChebyshev2 test_chebyshev2)

add_executable (test_rbj rbj.cpp)
target_link_libraries(test_rbj iir)
add_test(TestRBJ test_rbj)

add_executable (test_custom custom.cpp)
target_link_libraries(test_custom iir)
add_test(TestCUSTOM test_custom)

add_executable (test_badparam badparam.cpp)
target_link_libraries(test_badparam iir)
add_test(TestBadParam test_badparam)

add_executable (test_state state.cpp)
target_link_libraries(test_state iir)
add_test(TestState test_state)
