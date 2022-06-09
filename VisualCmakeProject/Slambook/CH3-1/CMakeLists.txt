aux_source_directory(. DIR_SRCS)

include_directories(../ThirdPartyLib/eigen)

add_library( libEigenMatrixTest SHARED eigenMatrix.cpp)
