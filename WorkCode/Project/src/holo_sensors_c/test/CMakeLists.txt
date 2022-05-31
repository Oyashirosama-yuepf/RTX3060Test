project(${PROJECT_NAME}_unit_test)

GENERATE_DOXYGEN(OPTIMIZE_OUTPUT_FOR_C INPUT ${CMAKE_CURRENT_LIST_DIR})

set(lib_support unity ${CMAKE_PROJECT_NAME} m)

# sensors
HOLO_COMPILE_TEST("sensors/aceinna/test_aceinna_imu_driver.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("sensors/can/test_vehicle_can_driver.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("sensors/conti_radar/test_conti_radar_driver.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("sensors/mpc/test_mpc_driver.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("sensors/tc297_cpu/test_cpu_state.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("sensors/ublox/test_ublox_driver.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("sensors/uss/test_bosch_uss_driver.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("sensors/vehicle_body_state/test_vehicle_body_state.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("sensors/ifv300/test_ifv300_driver.c" LIBRARIES "${lib_support}")
