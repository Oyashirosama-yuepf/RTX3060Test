cmake_minimum_required(VERSION 3.12)
project(CMakeProject1)

# 收集指定路径下的所有源文件：aux_source_directory(dir variable), 列表存入variable中
aux_source_directory(. DIR_SRCS)
# 添加子目录，允许将另外一个目录带入构建，该目录下必须要有自己的cmakelists，add时会调用
#add_subdirectory(sourcedir [binarydir] [exclude_form_all]) sourcedir: 子目录路径
#include 、include_directories添加文件名,用于包含头文件
add_subdirectory(AStarLib)

find_package(Hanoi)

include_directories(ExternFunction)
# 指定生成目标
add_executable(demo ${DIR_SRCS})

# 添加链接库
target_link_libraries(demo AStarFunctions)
target_link_libraries(demo ${Hanoi_LIBS})     


