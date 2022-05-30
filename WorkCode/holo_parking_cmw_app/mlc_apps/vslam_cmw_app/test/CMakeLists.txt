project(${PROJECT_NAME}_unit_test)

GENERATE_DOXYGEN(INPUT ${CMAKE_CURRENT_LIST_DIR})

find_package(GTest 1.8.1 EXACT REQUIRED)
set(lib_support GTest::GTest)

# test
#e.g. HOLO_COMPILE_TEST("test_main.cpp" LIBRARIES "${lib_support}")
