cmake_minimum_required(VERSION 3.10)
project(nexusrootd)

set(CMAKE_CXX_STANDARD 17)

# 根据 ABI 推导 Android 目标三元组
if(ANDROID_ABI STREQUAL "arm64-v8a")
    set(TRIPLE "aarch64-linux-android")
elseif(ANDROID_ABI STREQUAL "armeabi-v7a")
    set(TRIPLE "armv7a-linux-androideabi")
elseif(ANDROID_ABI STREQUAL "x86_64")
    set(TRIPLE "x86_64-linux-android")
elseif(ANDROID_ABI STREQUAL "x86")
    set(TRIPLE "i686-linux-android")
endif()

set(API_LEVEL "24")
set(SYSROOT "${ANDROID_NDK}/toolchains/llvm/prebuilt/linux-x86_64/sysroot")
set(BINDER_NDK "${SYSROOT}/usr/lib/${TRIPLE}/${API_LEVEL}/libbinder_ndk.so")
set(LOG_LIB "${SYSROOT}/usr/lib/${TRIPLE}/${API_LEVEL}/liblog.so")

add_executable(nexusrootd
    src/main.cpp
    src/NexusRootService.cpp
)

target_include_directories(nexusrootd PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/gen)

target_link_libraries(nexusrootd
    ${BINDER_NDK}
    ${LOG_LIB}
)
