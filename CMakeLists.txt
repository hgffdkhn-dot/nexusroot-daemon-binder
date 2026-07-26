cmake_minimum_required(VERSION 3.10)
project(nexusrootd)

set(CMAKE_CXX_STANDARD 17)

# 从环境变量获取 NDK 根目录
set(NDK $ENV{ANDROID_NDK_HOME})
set(SYSROOT ${NDK}/toolchains/llvm/prebuilt/linux-x86_64/sysroot)

# 根据 ABI 选择库子目录
if(ANDROID_ABI STREQUAL "arm64-v8a")
    set(LIB_ARCH "aarch64-linux-android")
elseif(ANDROID_ABI STREQUAL "armeabi-v7a")
    set(LIB_ARCH "armv7a-linux-androideabi")
elseif(ANDROID_ABI STREQUAL "x86_64")
    set(LIB_ARCH "x86_64-linux-android")
elseif(ANDROID_ABI STREQUAL "x86")
    set(LIB_ARCH "i686-linux-android")
else()
    message(FATAL_ERROR "Unsupported ABI: ${ANDROID_ABI}")
endif()

# 可执行文件
add_executable(nexusrootd
    src/main.cpp
    src/NexusRootService.cpp
)

# 头文件路径
target_include_directories(nexusrootd PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/gen
    ${SYSROOT}/usr/include
)

# 直接链接 .so 文件，确保找到
target_link_libraries(nexusrootd
    ${SYSROOT}/usr/lib/${LIB_ARCH}/24/libbinder_ndk.so
    ${SYSROOT}/usr/lib/${LIB_ARCH}/24/liblog.so
)
