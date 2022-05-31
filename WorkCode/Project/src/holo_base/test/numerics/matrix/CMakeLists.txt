# This cmake script is used for generating unit test sources
#
# usage:
# 1 Add test instance
# 2 mkdir build
# 3 cd build && cmake ..
# 4 All test source files are generated, remove build directory. "rm -r build"
#

cmake_minimum_required(VERSION 2.8.11)

set(NUMERICS_GENERATED_TEST_SOURCES)

MACRO(GENERATE_FIXED_SIZE_MATRIX_TEST type row col)
    set(_matrix_inst_scalar ${type})
    set(_matrix_inst_row ${row})
    set(_matrix_inst_col ${col})
    math(EXPR _matrix_init_size "${row} * ${col}")
    math(EXPR _matrix_short_init_size "${_matrix_init_size}/2")
    math(EXPR _matrix_long_init_size "${_matrix_init_size} + 1")
    set(_output_file ${CMAKE_CURRENT_LIST_DIR}/generated/test_fixed_size_matrix_${type}_${row}_${col}.cpp)
    configure_file(${CMAKE_CURRENT_LIST_DIR}/template/test_fixed_size_matrix_type_row_col.cpp.in 
        ${_output_file} @ONLY) 
    LIST(APPEND NUMERICS_GENERATED_TEST_SOURCES ${_output_file})
ENDMACRO(GENERATE_FIXED_SIZE_MATRIX_TEST)

MACRO(GENERATE_FIXED_SIZE_VECTOR_TEST type size)
    set(_matrix_inst_scalar ${type})
    set(_matrix_inst_row ${size})
    set(_matrix_inst_col 1)
    math(EXPR _matrix_init_size "${size} * 1")
    math(EXPR _matrix_short_init_size "${_matrix_init_size}/2")
    math(EXPR _matrix_long_init_size "${_matrix_init_size} + 1")
    set(_output_file ${CMAKE_CURRENT_LIST_DIR}/generated/test_fixed_size_vector_${type}_${size}.cpp)
    configure_file(${CMAKE_CURRENT_LIST_DIR}/template/test_fixed_size_vector_type_size.cpp.in 
        ${_output_file} @ONLY) 
    LIST(APPEND NUMERICS_GENERATED_TEST_SOURCES ${_output_file})
ENDMACRO(GENERATE_FIXED_SIZE_VECTOR_TEST)

MACRO(GENERATE_DYNAMIC_SIZE_MATRIX_TEST type row col)
    set(_matrix_inst_scalar ${type})
    set(_matrix_inst_row ${row})
    set(_matrix_inst_col ${col})
    math(EXPR _matrix_init_size "${row} * ${col}")
    math(EXPR _matrix_short_init_size "${_matrix_init_size}/2")
    math(EXPR _matrix_long_init_size "${_matrix_init_size} + 1")
    set(_output_file ${CMAKE_CURRENT_LIST_DIR}/generated/test_dynamic_size_matrix_${type}_${row}_${col}.cpp)
    configure_file(${CMAKE_CURRENT_LIST_DIR}/template/test_dynamic_size_matrix_type_row_col.cpp.in 
        ${_output_file} @ONLY) 
    LIST(APPEND NUMERICS_GENERATED_TEST_SOURCES ${_output_file})
ENDMACRO(GENERATE_DYNAMIC_SIZE_MATRIX_TEST)

MACRO(GENERATE_DYNAMIC_SIZE_VECTOR_TEST type size)
    set(_matrix_inst_scalar ${type})
    set(_matrix_inst_row ${size})
    set(_matrix_inst_col 1)
    math(EXPR _matrix_init_size "${size} * 1")
    math(EXPR _matrix_short_init_size "${_matrix_init_size}/2")
    math(EXPR _matrix_long_init_size "${_matrix_init_size} + 1")
    set(_output_file ${CMAKE_CURRENT_LIST_DIR}/generated/test_dynamic_size_vector_${type}_${size}.cpp)
    configure_file(${CMAKE_CURRENT_LIST_DIR}/template/test_dynamic_size_vector_type_size.cpp.in 
        ${_output_file} @ONLY) 
    LIST(APPEND NUMERICS_GENERATED_TEST_SOURCES ${_output_file})
ENDMACRO(GENERATE_DYNAMIC_SIZE_VECTOR_TEST)

foreach(dim ${MATRIX_INST_DIMS})
    string(REPLACE " " ";" dims ${dim})
    LIST(GET dims 0 _row)
    LIST(GET dims 1 _col)
    if((NOT _row EQUAL -1) AND (NOT _col EQUAL -1))
        GENERATE_FIXED_SIZE_MATRIX_TEST(float32_t ${dims})
        GENERATE_FIXED_SIZE_MATRIX_TEST(float64_t ${dims})
        GENERATE_DYNAMIC_SIZE_MATRIX_TEST(float32_t ${dims})
        GENERATE_DYNAMIC_SIZE_MATRIX_TEST(float64_t ${dims})
    endif()
endforeach(dim)

foreach(dim ${VECTOR_INST_DIMS})
    if(NOT dim  EQUAL -1)
        GENERATE_FIXED_SIZE_VECTOR_TEST(float32_t ${dim})
        GENERATE_FIXED_SIZE_VECTOR_TEST(float64_t ${dim})
        GENERATE_DYNAMIC_SIZE_VECTOR_TEST(float32_t ${dim})
        GENERATE_DYNAMIC_SIZE_VECTOR_TEST(float64_t ${dim})
    endif()
endforeach(dim)

set(NUMERICS_GENERATED_TEST_SOURCES ${NUMERICS_GENERATED_TEST_SOURCES} PARENT_SCOPE)

