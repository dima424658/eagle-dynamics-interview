cmake_minimum_required(VERSION 3.7)

project(EagleDynamics)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options (-fdiagnostics-color=always)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options (-fcolor-diagnostics)
endif ()

add_executable(${PROJECT_NAME} Main.cpp Application.cpp Ball.cpp)

find_package(SFML 2 COMPONENTS graphics audio REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics)