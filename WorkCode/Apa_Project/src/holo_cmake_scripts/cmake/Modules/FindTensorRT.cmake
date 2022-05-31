# This module defines the following variables:
#
# ::
#
#   TensorRT_INCLUDE_DIRS
#   TensorRT_LIBRARIES
#   TensorRT_FOUND
#
# ::
#
#   TensorRT_VERSION_STRING - version (x.y.z)
#   TensorRT_VERSION_MAJOR  - major version (x)
#   TensorRT_VERSION_MINOR  - minor version (y)
#   TensorRT_VERSION_PATCH  - patch version (z)
#
# Hints
# ^^^^^
# A user may set ``TensorRT_ROOT`` to an installation root to tell this module where to look.
#


# Include dir
find_path(TensorRT_INCLUDE_DIR NAMES NvInfer.h HINTS ${TensorRT_ROOT} PATH_SUFFIXES include)

mark_as_advanced(TensorRT_INCLUDE_DIR)

if(TensorRT_INCLUDE_DIR AND EXISTS "${TensorRT_INCLUDE_DIR}/NvInferVersion.h")
    file(STRINGS "${TensorRT_INCLUDE_DIR}/NvInferVersion.h" TensorRT_MAJOR REGEX "^#define NV_TENSORRT_MAJOR [0-9]+.*$")
    file(STRINGS "${TensorRT_INCLUDE_DIR}/NvInferVersion.h" TensorRT_MINOR REGEX "^#define NV_TENSORRT_MINOR [0-9]+.*$")
    file(STRINGS "${TensorRT_INCLUDE_DIR}/NvInferVersion.h" TensorRT_PATCH REGEX "^#define NV_TENSORRT_PATCH [0-9]+.*$")

    string(REGEX REPLACE "^#define NV_TENSORRT_MAJOR ([0-9]+).*$" "\\1" TensorRT_VERSION_MAJOR "${TensorRT_MAJOR}")
    string(REGEX REPLACE "^#define NV_TENSORRT_MINOR ([0-9]+).*$" "\\1" TensorRT_VERSION_MINOR "${TensorRT_MINOR}")
    string(REGEX REPLACE "^#define NV_TENSORRT_PATCH ([0-9]+).*$" "\\1" TensorRT_VERSION_PATCH "${TensorRT_PATCH}")
    set(TensorRT_VERSION_STRING "${TensorRT_VERSION_MAJOR}.${TensorRT_VERSION_MINOR}.${TensorRT_VERSION_PATCH}")
elseif(TensorRT_INCLUDE_DIR AND EXISTS "${TensorRT_INCLUDE_DIR}/NvInfer.h")
    file(STRINGS "${TensorRT_INCLUDE_DIR}/NvInfer.h" TensorRT_MAJOR REGEX "^#define NV_TENSORRT_MAJOR [0-9]+.*$")
    file(STRINGS "${TensorRT_INCLUDE_DIR}/NvInfer.h" TensorRT_MINOR REGEX "^#define NV_TENSORRT_MINOR [0-9]+.*$")
    file(STRINGS "${TensorRT_INCLUDE_DIR}/NvInfer.h" TensorRT_PATCH REGEX "^#define NV_TENSORRT_PATCH [0-9]+.*$")

    string(REGEX REPLACE "^#define NV_TENSORRT_MAJOR ([0-9]+).*$" "\\1" TensorRT_VERSION_MAJOR "${TensorRT_MAJOR}")
    string(REGEX REPLACE "^#define NV_TENSORRT_MINOR ([0-9]+).*$" "\\1" TensorRT_VERSION_MINOR "${TensorRT_MINOR}")
    string(REGEX REPLACE "^#define NV_TENSORRT_PATCH ([0-9]+).*$" "\\1" TensorRT_VERSION_PATCH "${TensorRT_PATCH}")
    set(TensorRT_VERSION_STRING "${TensorRT_VERSION_MAJOR}.${TensorRT_VERSION_MINOR}.${TensorRT_VERSION_PATCH}")
endif()

if (TensorRT_VERSION_STRING VERSION_LESS 7)
    set(TensorRT_COMPONENTS nvcaffe_parser  nvinfer_plugin nvinfer nvonnxparser_runtime nvonnxparser nvparsers)
else()
    set(TensorRT_COMPONENTS nvcaffe_parser  nvinfer_plugin nvinfer nvonnxparser nvparsers)
endif()

foreach (comp ${TensorRT_COMPONENTS})
    if (NOT TensorRT_${comp}_LIBRARY)
	find_library(TensorRT_${comp}_LIBRARY ${comp} HINTS ${TensorRT_ROOT} PATH_SUFFIXES lib)
        if (TensorRT_${comp}_LIBRARY)
            set(TensorRT_${comp}_FOUND 1)
            mark_as_advanced(TensorRT_${comp}_LIBRARY)
            set(TensorRT_${comp}_LIBRARIES ${TensorRT_${comp}_LIBRARY})
        endif ()
    endif ()
    list(APPEND TensorRT_LIBRARIES ${TensorRT_${comp}_LIBRARY})
    list(APPEND TensorRT_REQUIRED_VARS TensorRT_${comp}_LIBRARY)
endforeach ()

find_package(CUDA QUIET)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(TensorRT REQUIRED_VARS ${TensorRT_REQUIRED_VARS} TensorRT_INCLUDE_DIR CUDA_CUBLAS_LIBRARIES VERSION_VAR TensorRT_VERSION_STRING)

if(TensorRT_FOUND)
  set(TensorRT_INCLUDE_DIRS ${TensorRT_INCLUDE_DIR})

    foreach (comp ${TensorRT_COMPONENTS})
        if (NOT TARGET TensorRT::${comp})
            add_library(TensorRT::${comp} UNKNOWN IMPORTED)    
            set_target_properties(TensorRT::${comp} PROPERTIES
                    INTERFACE_INCLUDE_DIRECTORIES "${TensorRT_INCLUDE_DIR}"
                    IMPORTED_LOCATION "${TensorRT_${comp}_LIBRARY}"
		    INTERFACE_LINK_LIBRARIES "${CUDA_CUBLAS_LIBRARIES}"
                    )
        endif ()
    endforeach ()

    if(NOT TARGET TensorRT::TensorRT)
        add_library(TensorRT::TensorRT INTERFACE IMPORTED)
        set_target_properties(TensorRT::TensorRT PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${TensorRT_INCLUDE_DIR}"
		INTERFACE_LINK_LIBRARIES "${TensorRT_LIBRARIES};${CUDA_CUBLAS_LIBRARIES}"
                )
    endif()
endif()
