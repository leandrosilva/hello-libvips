cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(hello-libvips VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(/usr/include/glib-2.0)
include_directories(/usr/lib/x86_64-linux-gnu/glib-2.0/include)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE vips-cpp vips gobject-2.0 -lglib-2.0)

target_compile_options(${PROJECT_NAME} PRIVATE
    "-fPIC"
    "-Wall"
    "-Wextra"
    "-Wconversion"
    "-Wshadow"
    "-Wno-sign-conversion")

target_compile_features(${PROJECT_NAME} PRIVATE "cxx_std_20")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
