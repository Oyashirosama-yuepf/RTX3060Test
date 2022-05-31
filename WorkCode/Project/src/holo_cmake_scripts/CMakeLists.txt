cmake_minimum_required(VERSION 2.8)

project(holo_cmake_scripts)

include(${CMAKE_CURRENT_LIST_DIR}/cmake/HoloProjectConfiguration.cmake)

install(DIRECTORY cmake/ DESTINATION cmake)
install(FILES scripts/activate.sh DESTINATION .)
