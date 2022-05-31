set(GTEST_VERSION 1.8.1)

find_package(GTest ${GTEST_VERSION} EXACT REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
set(lib_support 
    GTest::GTest    
    holo_base::holo_base_core
    holo_base::holo_base_common
    holo_base::holo_base_geometry
    holo_base::holo_base_numerics
    holo_base::holo_base_probability 
    holo_localization::holo_localization_base 
    holo_localization_parking
    Boost::system)
include_directories(${PROJECT_SOURCE_DIR}/test)

# vision
CompileTest("vision/vslam/test_common_types" "${lib_support}")
CompileTest("vision/vslam/test_descriptor_matcher" "${lib_support}")
CompileTest("vision/vslam/test_essential_matrix_factor" "${lib_support}")
CompileTest("vision/vslam/test_failure_detection" "${lib_support}")
CompileTest("vision/vslam/test_feature_track_vslam" "${lib_support}")
CompileTest("vision/vslam/test_initializer" "${lib_support}")
CompileTest("vision/vslam/test_landmark_vslam" "${lib_support}")
CompileTest("vision/vslam/test_localization" "${lib_support}")
CompileTest("vision/vslam/test_measurements_manager_vslam" "${lib_support}")
CompileTest("vision/vslam/test_pose_only_unit3_factor" "${lib_support}")
CompileTest("vision/vslam/test_rotation_only_imu_factor" "${lib_support}")
CompileTest("vision/vslam/test_sliding_window_estimator" "${lib_support}")
CompileTest("vision/vslam/test_sliding_window_state" "${lib_support}")
CompileTest("vision/vslam/test_track_state_transition" "${lib_support}")
CompileTest("vision/vslam/test_tracker_vslam" "${lib_support}")
CompileTest("vision/vslam/test_unit3_factor" "${lib_support}")
CompileTest("vision/vslam/test_velocity_factor_vslam" "${lib_support}")
CompileTest("vision/vslam/test_initial_matching" "${lib_support}")
CompileTest("vision/vslam/test_desc_matching_on_dsp" "${lib_support}")
CompileTest("vision/vslam/test_global_relocalization" "${lib_support}")
