# CMake 版本要求
cmake_minimum_required(VERSION 3.14)
# 项目名称
project(MocliaDiceCore)
# 设置项目C++标准
set(CMAKE_CXX_STANDARD 17)

# 递归搜索 src 目录中的源文件
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

#add_executable(${PROJECT_NAME} ${SOURCE_FILES})
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# 设置头文件目录
target_include_directories(${PROJECT_NAME} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    )

# gcc 要连接 pthread
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
endif()