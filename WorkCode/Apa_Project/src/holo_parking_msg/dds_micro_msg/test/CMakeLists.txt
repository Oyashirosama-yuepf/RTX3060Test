project(holo_base_dds_micro_msg_unit_test)

GENERATE_DOXYGEN(INPUT ${CMAKE_CURRENT_LIST_DIR})

find_package(GTest 1.8.1 EXACT REQUIRED)

set(lib_support holo_base_msg_dds_micro GTest::GTest)

