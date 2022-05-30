aux_source_directory(. DIR_LIB_SRCS)
# 生成链接库 cpp源文件生成一个so

#add_library(Hanoi SHARED ${DIR_LIB_SRCS})
#add_library(Hanoi STATIC ${DIR_LIB_SRCS})

add_library(Hanoi ${DIR_LIB_SRCS})