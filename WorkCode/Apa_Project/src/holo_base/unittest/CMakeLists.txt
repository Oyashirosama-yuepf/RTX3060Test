aux_source_directory(src/common common_test_files)
aux_source_directory(src/numerics numerics_test_files)
aux_source_directory(src/geometry geometry_test_files)
aux_source_directory(src/map map_test_files)
aux_source_directory(src/core core_test_files)
aux_source_directory(src/freespace freespace_test_files)
aux_source_directory(src/vision vision_test_files)
aux_source_directory(src/obstacle obstacle_test_files)
aux_source_directory(src/point_cloud point_cloud_test_files)
aux_source_directory(src/planning planning_test_files)
aux_source_directory(src/prediction prediction_test_files)
aux_source_directory(src/sensors sensors_test_files)
aux_source_directory(src/probability probability_test_files)
aux_source_directory(src/utils utils_test_files)
aux_source_directory(src/container container_test_files)
aux_source_directory(src/filters filters_test_files)
aux_source_directory(src/math math_test_files)
aux_source_directory(src/metadata metadata_test_files)
aux_source_directory(src/os os_test_files)
aux_source_directory(src/io/common io_common_test_files)
aux_source_directory(src/io/geometry io_geometry_test_files)
aux_source_directory(src/io/numerics io_numerics_test_files)
aux_source_directory(src/io/utils io_utils_test_files)

add_library(unittest OBJECT EXCLUDE_FROM_ALL	
    ${common_test_files}
    ${numerics_test_files}
    ${geometry_test_files}
    ${map_test_files}
    ${core_test_files}
    ${freespace_test_files}
    ${vision_test_files}
    ${obstacle_test_files}
    ${point_cloud_test_files}
    ${planning_test_files}
    ${prediction_test_files}
    ${sensors_test_files}
    ${probability_test_files}
    ${utils_test_files}
    ${container_test_files}
    ${filters_test_files}
    ${math_test_files}
    ${metadata_test_files}
    ${os_test_files}
    ${io_common_test_files}
    ${io_geometry_test_files}
    ${io_numerics_test_files}
    ${io_utils_test_files})

target_include_directories(unittest PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(unittest PUBLIC holo_base_numerics holo_base_geometry 
 holo_base_common holo_base_map holo_base_core holo_base_freespace, holo_base_vision, holo_base_obstacle)
