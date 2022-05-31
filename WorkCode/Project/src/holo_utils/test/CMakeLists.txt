project(${PROJECT_NAME}_unit_test)

GENERATE_DOXYGEN(INPUT ${CMAKE_CURRENT_LIST_DIR})

find_package(GTest 1.8.1 EXACT REQUIRED)
set(lib_support holo_utils GTest::GTest)

set(agent_lib_support  holo_utils)

HOLO_COMPILE_TEST("serialization/test_utility.cpp" LIBRARIES "${lib_support}")

HOLO_COMPILE_TEST("log/test_async_to_console.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("log/test_async_to_rolling_file.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("log/test_console_configure.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("log/test_daily_rolling_file_configure.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("log/test_single_file_configure.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("log/test_multhread.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("log/test_no_initialize.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("log/test_rolling_file_configure.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("log/test_time_based_rolling_file_configure.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("log/test_initialize_with_yaml.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("log/test_log_every_n.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("log/test_log_every_n_with_multhread.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("log/test_log_if_every_n_with_multhread.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("log/test_memory.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("log/test_color_hash.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("log/test_loglevel_hash.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("log/test_stream.cpp" LIBRARIES "${lib_support}")

HOLO_COMPILE_TEST("pcapng/test_pcapng.cpp" LIBRARIES "${lib_support}")

#HOLO_COMPILE_TEST("log/test_glog_performance_console_multhread.cpp" LIBRARIES "${lib_support}")
#HOLO_COMPILE_TEST("log/test_glog_performance_console_single.cpp" LIBRARIES "${lib_support}")
#HOLO_COMPILE_TEST("log/test_glog_performance_file_multhread.cpp" LIBRARIES "${lib_support}")
#HOLO_COMPILE_TEST("log/test_glog_performance_file_single.cpp" LIBRARIES "${lib_support}")

HOLO_COMPILE_TEST("log/test_hololog_performance_console_multhread.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("log/test_hololog_performance_console_single.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("log/test_hololog_performance_file_multhread.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("log/test_hololog_performance_file_multhread_rolling.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("log/test_hololog_performance_file_single.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("log/test_hololog_performance_file_single_rolling.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("log/test_hololog_performance_file_single_daily.cpp" LIBRARIES "${lib_support}")

#HOLO_COMPILE_TEST("log/test_hololog_mmap_performance_file_multhread.cpp" LIBRARIES "${lib_support}")
#HOLO_COMPILE_TEST("log/test_hololog_mmap_performance_file_single.cpp" LIBRARIES "${lib_support}")

HOLO_COMPILE_TEST("os/test_signal_handler.cpp" LIBRARIES "${lib_support}")

HOLO_COMPILE_TEST("thread/test_threadpool.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("thread/test_threadpool_1_32.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("thread/test_threadpool_4_32.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("thread/test_threadpool_8_32.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("thread/test_threadpool_1_1024.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("thread/test_threadpool_4_1024.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("thread/test_threadpool_8_1024.cpp" LIBRARIES "${lib_support}")

HOLO_COMPILE_TEST("thread/test_objectpool.cpp" LIBRARIES "${lib_support}")

HOLO_COMPILE_TEST("serialization/test_serializer_network_4.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("serialization/test_serializer_host_4.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("serialization/test_serializer_network_8.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("serialization/test_serializer_host_8.cpp" LIBRARIES "${lib_support}")

HOLO_COMPILE_TEST("serialization/test_deserializer_network_4.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("serialization/test_deserializer_host_4.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("serialization/test_deserializer_network_8.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("serialization/test_deserializer_host_8.cpp" LIBRARIES "${lib_support}")

HOLO_COMPILE_TEST("core/test_allocator.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("core/test_exception.cpp" LIBRARIES "${lib_support}")

HOLO_COMPILE_TEST("os/test_filesystem.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("os/test_shared_memory_block_writer.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("os/test_shared_memory_block_reader.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("os/test_shared_memory_block_writer1.cpp" LIBRARIES "${lib_support}")
HOLO_COMPILE_TEST("os/test_shared_memory_block_reader1.cpp" LIBRARIES "${lib_support}")

HOLO_COMPILE_TEST("os/test_shared_memory_notification.cpp" LIBRARIES "${lib_support}")

HOLO_COMPILE_TEST("utils/test_configuration.cpp" LIBRARIES "${lib_support}")

CompileTest("bag/test_agent_record_no_video" "${agent_lib_support}")
CompileTest("bag/test_agent_replay_no_video" "${agent_lib_support}")
CompileTest("bag/test_agent_record_no_video2" "${agent_lib_support}")
CompileTest("bag/test_agent_replay_no_video2" "${agent_lib_support}")
CompileTest("bag/test_agent_record_block" "${agent_lib_support}")
CompileTest("bag/test_agent_replay_block" "${agent_lib_support}")

