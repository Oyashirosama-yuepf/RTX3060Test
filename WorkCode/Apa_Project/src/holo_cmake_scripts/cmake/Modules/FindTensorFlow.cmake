find_library(TensorFlow_CC_LIBRARY
             NAMES tensorflow_cc
             PATH_SUFFIXES bazel-bin/tensorflow
             )

find_library(TensorFlow_Framework_LIBRARY
             NAMES tensorflow_framework
             PATH_SUFFIXES bazel-bin/tensorflow
             )

find_path(TensorFlow_genfiles_INCLUDE_DIR
          NAMES
          bazel-genfiles
          )

find_path(TensorFlow_eigen_INCLUDE_DIR
          NAMES
          bazel-tensorflow/external/eigen_archive
          )

find_path(TensorFlow_protobuf_INCLUDE_DIR
          NAMES
          bazel-tensorflow/external/protobuf_archive/src
          )

find_path(TensorFlow_com_google_absl_INCLUDE_DIR
          NAMES
          bazel-tensorflow/external/com_google_absl
          )

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(TensorFlow REQUIRED_VARS 
                                  TensorFlow_CC_LIBRARY 
                                  TensorFlow_Framework_LIBRARY
                                  TensorFlow_genfiles_INCLUDE_DIR
                                  TensorFlow_eigen_INCLUDE_DIR
                                  TensorFlow_protobuf_INCLUDE_DIR
                                  TensorFlow_com_google_absl_INCLUDE_DIR
                                  )

mark_as_advanced(TensorFlow_CC_LIBRARY 
                 TensorFlow_Framework_LIBRARY
                 TensorFlow_genfiles_INCLUDE_DIR
                 TensorFlow_eigen_INCLUDE_DIR
                 TensorFlow_protobuf_INCLUDE_DIR
                 TensorFlow_com_google_absl_INCLUDE_DIR
                 )

if(TensorFlow_FOUND)
    set(TensorFlow_INCLUDE_DIRS ${TensorFlow_genfiles_INCLUDE_DIR}
                                ${TensorFlow_genfiles_INCLUDE_DIR}/bazel-genfiles
                                ${TensorFlow_eigen_INCLUDE_DIR}/bazel-tensorflow/external/eigen_archive
                                ${TensorFlow_protobuf_INCLUDE_DIR}/bazel-tensorflow/external/protobuf_archive/src
                                ${TensorFlow_com_google_absl_INCLUDE_DIR}/bazel-tensorflow/external/com_google_absl
                                )

    if(NOT TARGET tensorflow_cc)
        add_library(tensorflow_cc UNKNOWN IMPORTED)
        
        set_target_properties(tensorflow_cc PROPERTIES
            IMPORTED_LOCATION "${TensorFlow_CC_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${TensorFlow_INCLUDE_DIRS}"
            CXX_STANDARD 11
        )
    endif()

    if(NOT TARGET tensorflow_framework)
        add_library(tensorflow_framework UNKNOWN IMPORTED)
        
        set_target_properties(tensorflow_framework PROPERTIES
            IMPORTED_LOCATION "${TensorFlow_FRAMEWORK_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${TensorFlow_INCLUDE_DIRS}"
            CXX_STANDARD 11
        )
    endif()

    include_directories(${TensorFlow_INCLUDE_DIRS})
endif(TensorFlow_FOUND)

