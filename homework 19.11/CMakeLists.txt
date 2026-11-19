cmake_minimum_required(VERSION 3.10)
project(Fleet CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(fleet
    main.cpp
    Inventory.cpp
    Transport.cpp
    Things.cpp
    ServiceCenter.cpp
    Fleet.cpp)

if (MSVC)
    target_compile_options(fleet PRIVATE /W4 /utf-8)
else()
    target_compile_options(fleet PRIVATE -Wall -Wextra)
endif()
