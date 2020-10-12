file(GLOB_RECURSE Sources ${CMAKE_CURRENT_SOURCE_DIR}/**/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/**/*.h)

add_library(CourierCXX STATIC ${Sources})
add_library(LibEvent STATIC IMPORTED)

set_target_properties(CourierCXX PROPERTIES LINKER_LANGUAGE CXX)

install(TARGETS CourierCXX LIBRARY DESTINATION /usr/local/lib)
install(DIRECTORY ../couriercxx DESTINATION /usr/local/include FILES_MATCHING PATTERN "*.h")

target_include_directories(CourierCXX PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
