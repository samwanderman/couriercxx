add_executable(GPIOPinUtil GPIOPinUtil.cpp)
add_executable(PortUtil PortUtil.cpp)

#add_library(event STATIC IMPORTED)

#set_target_properties(event PROPERTIES IMPORTED_LOCATION ${LIBEVENT_LIB_DIR})

target_link_libraries(GPIOPinUtil CourierCXX)
target_link_libraries(PortUtil CourierCXX)

target_include_directories(GPIOPinUtil PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)
target_include_directories(PortUtil PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)
