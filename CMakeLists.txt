cmake_minimum_required(VERSION 3.21)

project(winfetch
    VERSION 0.0.1
    DESCRIPTION "Windows系统信息展示工具"
    LANGUAGES CXX
)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
add_executable(winfetch ${SOURCES})

# Windows系统库链接
target_link_libraries(winfetch PRIVATE
    advapi32
    user32
    ws2_32
    gdi32
    ole32
    oleaut32
)

if(MSVC)
  # 通用选项
  target_compile_options(winfetch PRIVATE
        /utf-8
        /arch:AVX2
        /MP
    )

  # Debug
  string(APPEND CMAKE_CXX_FLAGS_DEBUG "/Zi /MDd")

  # Release
  string(APPEND CMAKE_CXX_FLAGS_RELEASE "/fp:fast /Gy /GL /Gw /MD /MP /Oi /Os /GR- /GS-")

  # /LTCG /MANIFEST:NO /MERGE:_RDATA=.rdata /OPT:REF /OPT:ICF
  add_link_options(
        $<$<CONFIG:Release>:/NORESOURCE>
        $<$<CONFIG:Release>:/LTCG>
        $<$<CONFIG:Release>:/MANIFEST:NO>
        $<$<CONFIG:Release>:/MERGE:_RDATA=.rdata>
        $<$<CONFIG:Release>:/OPT:REF>
        $<$<CONFIG:Release>:/OPT:ICF>
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
