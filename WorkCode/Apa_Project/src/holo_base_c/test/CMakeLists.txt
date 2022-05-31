project(${PROJECT_NAME}_unit_test)

GENERATE_DOXYGEN(OPTIMIZE_OUTPUT_FOR_C INPUT ${CMAKE_CURRENT_LIST_DIR})

set(lib_support unity ${CMAKE_PROJECT_NAME} m)

# common
HOLO_COMPILE_TEST("common/test_chassis_state.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_control_command.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_coordinate.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_dequeue.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_extrinsic_float32.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_gnss_position.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_gnss_pvt.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_imu_float32.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_imu_bias_float32.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_light_signal_request.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_odometry_float32.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_path_float32.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_queue.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_someip.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_sensor_id.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_timestamp.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_vehicle_location.c" LIBRARIES "${lib_support}")

# filter
HOLO_COMPILE_TEST("filters/test_kalman_filter_float32.c" LIBRARIES "${lib_support}")

# geometry
HOLO_COMPILE_TEST("geometry/test_angle_float32.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_box2_float32.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_box3_float32.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_convex_polygon2_float32.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_point2_float32.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_point2_float64.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_point3_float32.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_point3_float64.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_pose2_float32.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_pose3_float32.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_quaternion_float32.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_rot2_float32.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_rot3_float32.c" LIBRARIES "${lib_support}")

# numerics
HOLO_COMPILE_TEST("numerics/test_cubic_polynomial.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("numerics/test_cubic_spline.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("numerics/test_matrix_float32.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("numerics/test_vector_float32.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("port/test_endian.c" LIBRARIES "${lib_support}")

#utils
HOLO_COMPILE_TEST("utils/test_serialization.c" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("utils/test_geographical_transformation.c" LIBRARIES "${lib_support}")

