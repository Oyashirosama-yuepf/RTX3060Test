project(${PROJECT_NAME}_unit_test)

GENERATE_DOXYGEN(INPUT ${CMAKE_CURRENT_LIST_DIR})

find_package(GTest 1.8.1 EXACT REQUIRED)
set(lib_support ${${CMAKE_PROJECT_NAME}_TARGETS} GTest::GTest)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=unused-variable")

# vision
HOLO_COMPILE_TEST("vision/test_point_feature.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("vision/test_point_feature_list.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("vision/test_point_feature_list_ipc.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("vision/test_point_feature_list_smb_writer.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("vision/test_point_feature_list_smb_reader.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("control/test_apa_control_command.cpp" LIBRARIES "${lib_support}")

# surrounding
find_package(dds_micro_wrapper QUIET)
set(lib_support_camera_cover ${${CMAKE_PROJECT_NAME}_TARGETS} GTest::GTest holo_cmw::dds_micro_wrapper)
#HOLO_COMPILE_TEST("surrounding/test_camera_cover.cpp" LIBRARIES "${lib_support_camera_cover}")
