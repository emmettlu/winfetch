cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

project(neofetch-win
    VERSION 1.0.0
    DESCRIPTION "Windows系统信息展示工具"
    LANGUAGES CXX
)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# MinimalRelease 构建类型配置
set(CMAKE_CXX_FLAGS_MINIMALRELEASE "/Os /Oi /GL" CACHE STRING "MinimalRelease flags")
set(CMAKE_EXE_LINKER_FLAGS_MINIMALRELEASE "/LTCG" CACHE STRING "MinimalRelease linker flags")

# 输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# 包含目录
include_directories(
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/external"
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/src/core"
    "${CMAKE_SOURCE_DIR}/src/system"
    "${CMAKE_SOURCE_DIR}/src/hardware"
    "${CMAKE_SOURCE_DIR}/src/windows"
    "${CMAKE_SOURCE_DIR}/src/display"
    "${CMAKE_SOURCE_DIR}/src/utils"
)

# 源文件
set(SOURCES
    src/main.cpp
    src/core/neofetch.cpp
    src/display/display.cpp
    src/hardware/hardware.cpp
    src/system/system.cpp
    src/utils/utils.cpp
    src/windows/windows.cpp
    external/Registry.cpp
)

# 创建可执行文件
add_executable(neofetch-win ${SOURCES})

# Windows系统库链接
target_link_libraries(neofetch-win PRIVATE
    advapi32
    user32
    ws2_32
    gdi32
    ole32
    oleaut32
)

# MSVC编译选项
if(MSVC)
    # 通用选项
    target_compile_options(neofetch-win PRIVATE
        /W3
        /WX-
        /EHsc
        /utf-8
        /sdl
        /arch:AVX2
    )

    # Debug配置
    string(APPEND CMAKE_CXX_FLAGS_DEBUG " /Zi /Od")

    # Release配置
    string(APPEND CMAKE_CXX_FLAGS_RELEASE " /Os /Oi /GL")

    # 链接选项
    target_link_options(neofetch-win PRIVATE /SUBSYSTEM:CONSOLE)
endif()

# 其他编译器选项（GCC/Clang）
if(NOT MSVC)
    target_compile_options(neofetch-win PRIVATE
        -Wall
        -Wextra
        -pedantic
    )
endif()

# 编译定义
add_compile_definitions(
    UNICODE
    _UNICODE
    _CONSOLE
    _WINDOWS
)

# 输出信息
message(STATUS "====================================")
message(STATUS "项目名称: ${PROJECT_NAME}")
message(STATUS "版本: ${PROJECT_VERSION}")
message(STATUS "C++标准: ${CMAKE_CXX_STANDARD}")
message(STATUS "编译器: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "====================================")
