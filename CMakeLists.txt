cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules")
project(iir-filter VERSION 2.0.0 LANGUAGES CXX)

set(CMAKE_POLICY_DEFAULT_CMP0120 OLD)
set(CMAKE_POLICY_DEFAULT_CMP0069 NEW)

include(CMakeDependentOption)

# ccache
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    message(STATUS "Found CCache")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

# set global cxx standard
set(CMAKE_CXX_STANDARD 17)
# always generate position independent code, no matter static or shared library
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# disable cpp extensions
set(CMAKE_CXX_EXTENSIONS OFF)
# # link time optimization
# set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

set(IIR_SOURCES
    #
    ${CMAKE_CURRENT_SOURCE_DIR}/src/iir/biquad.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/iir/biquad.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/iir/butterworth.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/iir/butterworth.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/iir/cascade.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/iir/cascade.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/iir/chebyshev_i.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/iir/chebyshev_i.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/iir/chebyshev_ii.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/iir/chebyshev_ii.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/iir/common.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/iir/custom.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/iir/custom.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/iir/iir.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/iir/layout.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/iir/math_supplement.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/iir/pole_filter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/iir/pole_filter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/iir/rbj.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/iir/rbj.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/iir/state.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/iir/types.h
)

add_library(iir)
target_sources(iir PRIVATE ${IIR_SOURCES})

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(
        iir PRIVATE -Qunused-arguments -mllvm -inline-threshold=5000 -fno-exceptions
    )
endif()

target_include_directories(iir
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_library(iir::iir ALIAS iir)

add_subdirectory(test)
add_subdirectory(examples)
