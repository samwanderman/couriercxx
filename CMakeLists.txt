cmake_minimum_required(VERSION 3.10)

project(CourierCXX VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_definitions(-DNOMINMAX)

# WIN
#set(LIBEVENT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/libevent/include/)
#set(LIBEVENT_INCLUDE_DIR_EXT ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/libevent/build_win_vc/include)
#set(LIBEVENT_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/libevent/build_win_vc/lib/Release/event.lib)

add_subdirectory(couriercxx)
add_subdirectory(tests)
add_subdirectory(examples)
add_subdirectory(utils)
