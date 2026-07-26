cmake_minimum_required(VERSION 3.10)
project(nexusrootd)

set(CMAKE_CXX_STANDARD 17)

# 从环境变量获取 NDK 路径
set(NDK_ROOT $ENV{ANDROID_NDK_HOME})
set(SYSROOT ${NDK_ROOT}/toolchains/llvm/prebuilt/linux-x86_64/sysroot)

# 确定目标三元组
if(ANDROID_ABI STREQUAL "arm64-v8a")
    set(TRIPLE "aarch64-linux-android")
elseif(ANDROID_ABI STREQUAL "armeabi-v7a")
    set(TRIPLE "armv7a-linux-androideabi")
elseif(ANDROID_ABI STREQUAL "x86_64")
    set(TRIPLE "x86_64-linux-android")
elseif(ANDROID_ABI STREQUAL "x86")
    set(TRIPLE "i686-linux-android")
endif()

# 可执行文件
add_executable(nexusrootd
    src/main.cpp
    src/NexusRootService.cpp
)

# 包含路径：AIDL 生成目录 + NDK 系统头文件目录
target_include_directories(nexusrootd PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/gen
    ${SYSROOT}/usr/include
)

# 链接：使用 -lbinder_ndk -llog，NDK 会从标准位置搜索这些库
target_link_libraries(nexusrootd
    binder_ndk
    log
)
