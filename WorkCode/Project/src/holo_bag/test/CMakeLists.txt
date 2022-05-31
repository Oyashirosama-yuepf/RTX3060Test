set(GTEST_VERSION 1.8.1)

find_package(GTest ${GTEST_VERSION} EXACT REQUIRED)
find_package(Boost REQUIRED COMPONENTS system filesystem)
set(lib_support holo_base::holo_base Boost::system Boost::filesystem holo_3d::holo_3d holo_sensors_ibeo holo_sensors_camera GTest::GTest)
include_directories(${PROJECT_SOURCE_DIR}/include)

# # ibeo
# CompileTest("sensors/ibeo/test_ibeo" "${lib_support}")

# #camera
# CompileTest("sensors/camera/test_camera_ipc" "${lib_support}")
