
# 添加Eigen头文件
include_directories(../ThirdPartyLib/eigen)

# 添加Pangolin依赖
find_package( Pangolin )
include_directories( ${Pangolin_INCLUDE_DIRS} )

add_library( visualizeGeometry SHARED visualizeGeometry.cpp )
target_link_libraries( visualizeGeometry ${Pangolin_LIBRARIES} )
