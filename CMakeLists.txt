cmake_minimum_required(VERSION 3.10)
project(nexusrootd)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_library(libbinder libbinder)
find_library(libutils libutils)
find_library(liblog liblog)

add_library(nexusroot_service SHARED
    src/NexusRootService.cpp
)

target_include_directories(nexusroot_service PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(nexusroot_service
    ${libbinder}
    ${libutils}
    ${liblog}
)

# 可执行文件
add_executable(nexusrootd src/main.cpp)
target_include_directories(nexusrootd PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(nexusrootd
    nexusroot_service
    ${libbinder}
    ${libutils}
    ${liblog}
)