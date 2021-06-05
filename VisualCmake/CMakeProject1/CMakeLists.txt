
project(CMakeProject1)
aux_source_directory(. DIR_SRCS)
# 添加math子目录
add_subdirectory(AStarLib)
add_subdirectory(Hanoi)
# 指定生成目标
add_executable(demo ${DIR_SRCS})
# 添加链接库
target_link_libraries(demo AStarFunctions)
target_link_libraries(demo Hanoi)