cmake_minimum_required(VERSION 3.10)
project(nexusrootd)

set(CMAKE_CXX_STANDARD 17)

# 查找 NDK 库
find_library(binder_ndk_lib binder_ndk)
find_library(log_lib log)

add_executable(nexusrootd
    src/main.cpp
    src/NexusRootService.cpp
)

# 包含 AIDL 生成目录和 NDK 系统头文件
target_include_directories(nexusrootd PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/gen
    ${ANDROID_NDK}/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include
)

target_link_libraries(nexusrootd
    ${binder_ndk_lib}
    ${log_lib}
)
