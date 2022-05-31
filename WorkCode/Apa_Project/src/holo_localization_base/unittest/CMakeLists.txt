add_library(unittest OBJECT EXCLUDE_FROM_ALL
    src/common/stamped.cpp
)

target_link_libraries(unittest holo_localization_base)