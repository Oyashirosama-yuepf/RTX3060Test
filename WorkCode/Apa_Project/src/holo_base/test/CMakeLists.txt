project(${PROJECT_NAME}_unit_test)

GENERATE_DOXYGEN(INPUT ${CMAKE_CURRENT_LIST_DIR})

find_package(GTest 1.8.1 EXACT REQUIRED)
set(lib_support ${${CMAKE_PROJECT_NAME}_TARGETS} GTest::GTest)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=unused-variable")

# os
HOLO_COMPILE_TEST("os/test_time.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("os/test_tictoc_timer.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("os/test_timer.cpp" LIBRARIES "${lib_support}")

#common
HOLO_COMPILE_TEST("common/details/test_intrinsic32.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_alarm.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_apa_control_command.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_app_status.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_chassis_state.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_classification.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_control_command.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_coordinate.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_duration.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_extrinsic.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_freespace.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_gnss_position.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_gnss_pvt.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_gnss_raw_measurement.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_image.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_imu_float32.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_imu_float64.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_imu_bias_float32.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_imu_bias_float64.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_lane2.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_lane_boundary2.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_light_signal_request.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_odm.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_ddt.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_odometry_float32.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_odometry_float64.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_optional.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_parking_slot.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_path.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_road_frame2.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_segmentation_2d.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_sensor_id.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_timestamp.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_traffic_light.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_vehicle_body_state.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_vehicle_location.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_vehicle_specification.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_camera_fisheye.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_weather.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_perception_ability.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_lane_scene.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_road_type.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("common/test_road_category.cpp" LIBRARIES "${lib_support}")

# core
HOLO_COMPILE_TEST("core/test_epsilon.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("core/test_type_traits.cpp" LIBRARIES "${lib_support}")

# filters
HOLO_COMPILE_TEST("filters/test_kalman_filter.cpp" LIBRARIES "${lib_support}")

# freespace
HOLO_COMPILE_TEST("freespace/test_local_map_free_space.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("freespace/test_local_map_free_space_v2.cpp" LIBRARIES "${lib_support}")

# geometry
HOLO_COMPILE_TEST("geometry/test_angle.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_angle_axis.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_box2.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_box3.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_convex_polygon2.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/curve/test_curve_base.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/curve/test_curve_polynomial.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/curve/test_curve_bezier.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_line_segment2.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_line2.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_point2.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_point3.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_point3_spline.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_polyfit2.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_polynomial_curve2d.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_pose2.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_pose3.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_quaternion.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_rot2.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("geometry/test_rot3.cpp" LIBRARIES "${lib_support}")

#io
HOLO_COMPILE_TEST("io/common/test_coordinate_io.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("io/common/test_extrinsic_io.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("io/common/test_intrinsic_io.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("io/common/test_road_category_io.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("io/common/test_road_type_io.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("io/common/test_timestamp_io.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("io/common/test_sensor_id_io.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("io/common/test_vehicle_location_io.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("io/geometry/test_point3_io.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("io/geometry/test_rot3_io.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("io/geometry/test_pose3_io.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("io/utils/test_utils.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("io/common/test_odometry_io.cpp" LIBRARIES "${lib_support}")

# numerics
HOLO_COMPILE_TEST("numerics/bspline/test_float64_point2_3degree_bspline.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("numerics/test_eigen_solver.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("numerics/test_matrix.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("numerics/test_spline.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("numerics/test_utility.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("numerics/test_vector.cpp" LIBRARIES "${lib_support}")
add_subdirectory(numerics/matrix)
set_source_files_properties(${NUMERICS_GENERATED_TEST_SOURCES} PROPERTIES GENERATED TRUE)
foreach(f ${NUMERICS_GENERATED_TEST_SOURCES})
    file(RELATIVE_PATH f ${CMAKE_CURRENT_LIST_DIR} ${f})
    HOLO_COMPILE_TEST("${f}" LIBRARIES "${lib_support}")
endforeach(f)


# ------------map-------------------------------------------
# map message advice
HOLO_COMPILE_TEST("map/test_map_msg_base.cpp" LIBRARIES "${lib_support}")
# map message advice
HOLO_COMPILE_TEST("map/test_holo_map_advice_msg.cpp" LIBRARIES "${lib_support}")
# map service current route info
HOLO_COMPILE_TEST("map/test_current_route_info.cpp" LIBRARIES "${lib_support}")
# map service structure link info
HOLO_COMPILE_TEST("map/test_link_info.cpp" LIBRARIES "${lib_support}")
# map service structure lane info
HOLO_COMPILE_TEST("map/test_lane_info.cpp" LIBRARIES "${lib_support}")
# map service structure lane mark info
HOLO_COMPILE_TEST("map/test_lane_mark_info.cpp" LIBRARIES "${lib_support}")
# map service structure lane path 
HOLO_COMPILE_TEST("map/test_lane_path.cpp" LIBRARIES "${lib_support}")
# map service structure navigation request 
HOLO_COMPILE_TEST("map/test_map_navigation_request.cpp" LIBRARIES "${lib_support}")
# map service structure map app status
HOLO_COMPILE_TEST("map/test_map_app_status.cpp" LIBRARIES "${lib_support}")
# map service structure map enum to string
HOLO_COMPILE_TEST("map/test_map_enum_to_string.cpp" LIBRARIES "${lib_support}")
# map common object
HOLO_COMPILE_TEST("map/test_common_object.cpp" LIBRARIES "${lib_support}")
# map geofence
HOLO_COMPILE_TEST("map/test_map_geofence" LIBRARIES "${lib_support}")
# road attributes
HOLO_COMPILE_TEST("map/test_road_ref_point_attributes" LIBRARIES "${lib_support}")

# ------------map-------------------------------------------

#math
HOLO_COMPILE_TEST("math/test_math.cpp" LIBRARIES "${lib_support}")

# probability
HOLO_COMPILE_TEST("probability/ransac/test_ransac_line2_fitting_problem.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("probability/ransac/test_ransac_plane3_fitting_problem.cpp" LIBRARIES "${lib_support}")

# utils
HOLO_COMPILE_TEST("utils/test_holo_root.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("utils/test_geographical_transformation.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("utils/tlv/test_tlv_network_2_2.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("utils/tlv/test_tlv_host_2_2.cpp" LIBRARIES "${lib_support}")

# obstacle
HOLO_COMPILE_TEST("obstacle/test_obstacle_general.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("obstacle/test_fused_obstacle.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("obstacle/test_obstacle_lidar.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("obstacle/test_obstacle_radar.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("obstacle/test_obstacle_uss.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("obstacle/test_obstacle_vision.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("obstacle/test_obstacle_list.cpp" LIBRARIES "${lib_support}")

# prediction
HOLO_COMPILE_TEST("prediction/test_intention.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("prediction/test_intentions.cpp" LIBRARIES "${lib_support}")

#container
HOLO_COMPILE_TEST("container/details/test_deque.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("container/details/test_ordered_buffer.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("container/details/test_fixed_size_vector.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("container/test_vector.cpp" LIBRARIES "${lib_support}")

# vision
HOLO_COMPILE_TEST("vision/test_image_objects.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("vision/test_object.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("vision/test_keypoint2.cpp" LIBRARIES "${lib_support}")

# planning
HOLO_COMPILE_TEST("planning/test_state.cpp" LIBRARIES "${lib_support}")

# point_cloud
HOLO_COMPILE_TEST("point_cloud/test_linear_storage.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("point_cloud/test_point_type.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("point_cloud/test_point_cloud.cpp" LIBRARIES "${lib_support}")

# metadata
HOLO_COMPILE_TEST("metadata/common/test_app_status_type_description.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("metadata/common/test_chassis_state_type_description.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("metadata/common/test_ddt_type_description.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("metadata/common/test_gnss_pvt_type_description.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("metadata/common/test_imu_type_description.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("metadata/common/test_lane_boundary_type_description.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("metadata/common/test_odometry_type_description.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("metadata/common/test_timestamp_type_description.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("metadata/common/test_path_type_description.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("metadata/common/test_road_frame_type_description.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("metadata/common/test_road_type_type_description.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("metadata/common/test_road_category_type_description.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("metadata/common/test_vehicle_body_state_type_description.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("metadata/numerics/test_matrix_type_description.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("metadata/numerics/test_utility_type_description.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("metadata/point_cloud/test_point_type_type_description.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("metadata/point_cloud/test_point_cloud_type_description.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("metadata/obstacle/test_obstacle_uss_type_description.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("metadata/obstacle/test_obstacle_lidar_type_description.cpp" LIBRARIES "${lib_support}")

HOLO_COMPILE_TEST("metadata/metastruct/common/test_app_status_meta_struct.cpp" LIBRARIES "${lib_support}")

# test data
FILE(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
