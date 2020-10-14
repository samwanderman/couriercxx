cmake_minimum_required(VERSION 3.10)

project(CourierCXX VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)

find_package(Threads REQUIRED)

add_definitions(-DNOMINMAX)

if(WIN32)
	set(LIBEVENT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/libevent/include/)
	set(LIBEVENT_INCLUDE_DIR_EXT ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/libevent/build_win_vc/include)
	set(LIBEVENT_LIB ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/libevent/build_win_vc/lib/Release/event.lib)
	
	set(LIBPQXX_LIB ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/libpqxx/build/src/Release/pqxx.lib)
else(UNIX)
	set(LIBEVENT_INCLUDE_DIR /usr/local/include)
	set(LIBEVENT_LIB /usr/local/lib/libevent.a)
	
	set(LIBPQXX_LIB "pqxx")
	set(LIBPQ_LIB "pq")
endif()

add_subdirectory(couriercxx)
add_subdirectory(tests)
add_subdirectory(examples)
add_subdirectory(utils)
