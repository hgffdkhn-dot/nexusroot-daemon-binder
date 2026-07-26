cmake_minimum_required(VERSION 3.10)
project(nexusrootd)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 NDK 库
find_library(binder_ndk_lib binder_ndk)
find_library(log_lib log)

# 可执行文件（注意：不需要 libutils、libbinder）
add_executable(nexusrootd
    src/main.cpp
    src/NexusRootService.cpp
)

target_include_directories(nexusrootd PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/gen)

target_link_libraries(nexusrootd
    ${binder_ndk_lib}
    ${log_lib}
)
