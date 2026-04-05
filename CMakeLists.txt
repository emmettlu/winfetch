cmake_minimum_required(VERSION 3.21)

project(winfetch
    VERSION 0.0.2
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
  target_compile_options(winfetch PRIVATE
        /utf-8
        /arch:AVX2
        /MP
    )

  # Release
  string(APPEND CMAKE_CXX_FLAGS_RELEASE " /fp:fast /Gy /GL /Gw /MD /MP /Oi /Os /GR- /GS-")
  string(APPEND CMAKE_EXE_LINKER_FLAGS_RELEASE " /LTCG /OPT:REF /OPT:ICF /MERGE:_RDATA=.rdata")

  # 强烈推荐：显式禁用默认 manifest 生成（对 CMake + MSVC 非常有效）
  set_target_properties(winfetch PROPERTIES
    LINK_FLAGS_RELEASE " /MANIFEST:NO"
  )
endif()

# 编译定义
add_compile_definitions(
    UNICODE
    _UNICODE
    _CONSOLE
    _WINDOWS
)
