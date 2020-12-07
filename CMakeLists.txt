cmake_minimum_required(VERSION 3.10)

project(CourierCXX VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

find_package(Threads REQUIRED)
find_package(PostgreSQL REQUIRED)

add_definitions(-DNOMINMAX)

if(WIN32)
	set(LIBEVENT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/libevent/include/)
	set(LIBEVENT_INCLUDE_DIR_EXT ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/libevent/build_win/include)
	set(LIBEVENT_LIB ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/libevent/build_win/lib/Debug/event.lib)
	
	set(LIBPQXX_LIB ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/libpqxx/build_win/src/Debug/pqxx.lib)

	set(LIBBLUETOOTH_LIB)
else(UNIX)
	set(LIBEVENT_INCLUDE_DIR /usr/local/include)
	set(LIBEVENT_LIB /usr/local/lib/libevent.a)
	set(LIBPCAP_LIB "pcap")
	set(LIBJPEG_LIB "jpeg")
	set(LIBBLUETOOTH_LIB "bluetooth")
	
	find_library(LIBPQXX_LIB libpqxx.a)
endif()

add_subdirectory(couriercxx)
add_subdirectory(tests)
add_subdirectory(examples)
add_subdirectory(utils)
