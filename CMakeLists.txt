cmake_minimum_required(VERSION 3.16)
project(HotelListaDoble)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(HotelListaDoble
    src/main.cpp
    src/lista.cpp
    src/nodo.cpp
)
target_include_directories(HotelListaDoble PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
