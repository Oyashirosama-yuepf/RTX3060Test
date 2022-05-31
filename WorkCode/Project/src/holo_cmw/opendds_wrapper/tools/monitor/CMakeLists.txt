add_executable(openddsnode openddsnode.cpp)

target_link_libraries(openddsnode PRIVATE opendds_wrapper)

add_executable(openddstopic openddstopic.cpp)

target_link_libraries(openddstopic PRIVATE opendds_wrapper)

INSTALL(TARGETS openddsnode openddstopic DESTINATION bin)
