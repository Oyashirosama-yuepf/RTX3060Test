project(${PROJECT_NAME}_unit_test)

GENERATE_DOXYGEN(INPUT ${CMAKE_CURRENT_LIST_DIR})

find_package(GTest 1.8.1 EXACT REQUIRED)
set(lib_support GTest::GTest holo_base::holo_base_common)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=unused-variable")

HOLO_COMPILE_TEST("cpu_monitor/test_cpu_monitor.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("holo_socket/test_socket.cpp" LIBRARIES "${lib_support}" INCLUDES "${CMAKE_SOURCE_DIR}/include")
