cmake_minimum_required(VERSION 3.14)
project(copy-file)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")
find_package(Boost REQUIRED COMPONENTS
# regex
filesystem   # 我的工程中只使用了 boost 的 filesystem 功能,因此这里只有一个组件
)
if(NOT Boost_FOUND)
    message("Not found Boost")
endif()

include_directories(${Boost_INCLUDE_DIRS})
message("${Boost_INCLUDE_DIRS}")
message("${Boost_LIBRARIES}")

add_executable(copy-file ./copy_file.cpp )
target_link_libraries(copy-file ${Boost_LIBRARIES}) 