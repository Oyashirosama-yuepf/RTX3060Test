project(${PROJECT_NAME}_unit_test)

GENERATE_DOXYGEN(INPUT ${CMAKE_CURRENT_LIST_DIR})

find_package(GTest 1.8.1 EXACT REQUIRED)

set(lib_support GTest::GTest holo_localization_base holo_localization_base_sam)

#backend
HOLO_COMPILE_TEST("backend/factors/test_camera_imu_extrinsic_factor" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("backend/factors/test_gnss_position_velocity_factor" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("backend/factors/test_imu_body_extrinsic_factor" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("backend/factors/test_lane_factor" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("backend/factors/test_point2line_factor" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("backend/factors/test_point2plane_factor" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("backend/factors/test_point2point_factor" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("backend/factors/test_pose_only_unit3_factor" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("backend/factors/test_prior_rpy_factor" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("backend/factors/test_projection_line_factor" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("backend/test_factor_graph" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("backend/test_smoother" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("backend/test_velocity_factor" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("backend/test_wheel_speed_factor" LIBRARIES "${lib_support}")

#common
HOLO_COMPILE_TEST("common/test_advanced_navstated" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_advanced_navstatef" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_diagnostics" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_imu_preintegration" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_localization_base" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_measurements_manager_base" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_navstated" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_navstatef" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_stamped" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_wheel_preintegration" LIBRARIES "${lib_support}")

#sam
HOLO_COMPILE_TEST("sam/test_type_converter" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("sam/factors/test_line_projection_factor" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("sam/vision/line/test_line_triangulation" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("sam/vision/line/test_orthonormal_line" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("sam/vision/line/test_plucker_line" LIBRARIES "${lib_support}")

#tools
HOLO_COMPILE_TEST("tools/test_pose_spline" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("tools/test_source_checker_chassis_state" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("tools/test_source_checker_gnss_position" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("tools/test_source_checker_gnss_pvt" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("tools/test_source_checker_imu" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("tools/test_source_checker_odometry" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("tools/test_source_checker_road_frame" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("tools/test_spline_fitting" LIBRARIES "${lib_support}")

#vision
HOLO_COMPILE_TEST("vision/common/test_image_undistorterd" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("vision/common/test_image_undistorterf" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("vision/common/test_key_point" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("vision/common/test_mask" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("vision/common/test_mat" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("vision/common/test_range" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("vision/common/test_rect" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("vision/common/test_size" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("vision/feature/test_fast" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("vision/feature/test_feature2d" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("vision/feature/test_gridding_feature_extractor" LIBRARIES "${lib_support}")
