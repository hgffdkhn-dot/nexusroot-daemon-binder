cmake_minimum_required(VERSION 3.10)
project(nexusrootd)

set(CMAKE_CXX_STANDARD 17)

# 查找 NDK 库（备用，实际直接链接 .so）
find_library(binder_ndk_lib binder_ndk)
find_library(log_lib log)

add_executable(nexusrootd
    src/main.cpp
    src/NexusRootService.cpp
)

# 包含生成的头文件目录
target_include_directories(nexusrootd PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/gen/include
    ${ANDROID_NDK}/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include
)

# 添加 AIDL 生成的 .cpp 文件
file(GLOB_RECURSE AIDL_SRC "gen/src/**/*.cpp")
target_sources(nexusrootd PRIVATE ${AIDL_SRC})

# 链接库
target_link_libraries(nexusrootd
    ${binder_ndk_lib}
    ${log_lib}
)
