file(GLOB_RECURSE Sources ${CMAKE_CURRENT_SOURCE_DIR}/**/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/**/*.h)

add_library(CourierCXX STATIC ${Sources})

set_target_properties(CourierCXX PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(CourierCXX PROPERTIES POSITION_INDEPENDENT_CODE ON)

install(TARGETS CourierCXX ARCHIVE DESTINATION /usr/local/lib COMPONENT library)
install(DIRECTORY ../couriercxx DESTINATION /usr/local/include FILES_MATCHING PATTERN "*.h")

target_include_directories(CourierCXX PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${LIBEVENT_INCLUDE_DIR} ${LIBEVENT_INCLUDE_DIR_EXT})
