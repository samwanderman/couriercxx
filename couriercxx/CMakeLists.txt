file(GLOB_RECURSE Sources ${CMAKE_CURRENT_SOURCE_DIR}/**/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/**/*.h)

add_library(CourierCXX STATIC ${Sources})
add_library(LibEvent STATIC IMPORTED)

set_target_properties(CourierCXX PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(CourierCXX PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${LIBEVENT_INCLUDE_DIR} ${LIBEVENT_INCLUDE_DIR_EXT})
