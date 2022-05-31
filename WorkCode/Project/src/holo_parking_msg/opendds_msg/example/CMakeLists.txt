add_executable(parking_command_publisher parking_command_publisher.cpp)
target_link_libraries(parking_command_publisher PRIVATE holo_cmw::opendds_wrapper)
install(TARGETS parking_command_publisher DESTINATION ${HOLO_ROOT}/bin/opendds)

add_executable(heartbeat_publisher heartbeat_publisher.cpp)
target_link_libraries(heartbeat_publisher PRIVATE holo_cmw::opendds_wrapper)
install(TARGETS heartbeat_publisher DESTINATION ${HOLO_ROOT}/bin/opendds)