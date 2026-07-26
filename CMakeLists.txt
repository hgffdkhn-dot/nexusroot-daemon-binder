cmake_minimum_required(VERSION 3.10)
project(nexusrootd)

set(CMAKE_CXX_STANDARD 17)

# 确定 NDK 路径（由 android.toolchain.cmake 设置）
set(NDK ${ANDROID_NDK})

# 根据 ABI 确定三元组
if(ANDROID_ABI STREQUAL "arm64-v8a")
    set(TRIPLE "aarch64-linux-android")
elseif(ANDROID_ABI STREQUAL "armeabi-v7a")
    set(TRIPLE "armv7a-linux-androideabi")
elseif(ANDROID_ABI STREQUAL "x86_64")
    set(TRIPLE "x86_64-linux-android")
elseif(ANDROID_ABI STREQUAL "x86")
    set(TRIPLE "i686-linux-android")
endif()

set(SYSROOT ${NDK}/toolchains/llvm/prebuilt/linux-x86_64/sysroot)
set(NDK_INCLUDE ${SYSROOT}/usr/include)

# 添加头文件搜索路径：AIDL 生成目录 + NDK 头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gen)
include_directories(${NDK_INCLUDE})

# 可执行文件
add_executable(nexusrootd
    src/main.cpp
    src/NexusRootService.cpp
)

# 链接库：使用 -lbinder_ndk 和 -llog，通过 linker 查找
target_link_libraries(nexusrootd
    binder_ndk
    log
)
