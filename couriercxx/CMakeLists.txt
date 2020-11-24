file(GLOB_RECURSE Sources ${CMAKE_CURRENT_SOURCE_DIR}/**/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/**/*.h)

add_library(CourierCXX SHARED ${Sources})

install(
	TARGETS CourierCXX 
	ARCHIVE DESTINATION /usr/local/lib 
	LIBRARY DESTINATION /usr/local/lib 
	COMPONENT library
)

install(DIRECTORY ../couriercxx DESTINATION /usr/local/include FILES_MATCHING PATTERN "*.h")

target_link_libraries(CourierCXX ${LIBEVENT_LIB} PostgreSQL::PostgreSQL ${LIBPQXX_LIB} Threads::Threads "bluetooth" "pcap" "jpeg")

target_include_directories(CourierCXX PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${LIBEVENT_INCLUDE_DIR} ${LIBEVENT_INCLUDE_DIR_EXT})
