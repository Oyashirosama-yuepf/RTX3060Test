# Initialize default parameters used by holo project.
# Author Zhang Jiannan(zhangjiannan@holomaitc.com)
# Date 2018-12-6
# Attention Copyright © Holomatic Technology (Beijing) Co.Ltd
# Attention Please refer to COPYRIGHT.txt for terms of copyright notice.

# The following environment variable affect the output of this script.
#
#    HOLO_ROOT             -- Root directory of holo project files.
#
#    HOLO_3RDPARTY_ROOT    -- Root directory of holo 3rdparty project files.
#
#    HOLO_CONFIG_ROOT      -- Root directory of holo project configurations.
#
#    HOLO_LOG_ROOT         -- Root directory of holo project logs.
#
#
# The script defines the following variables:
# 
#    HOLO_ROOT             -- Root directory of holo project files. (Default /opt/holo)
#    HOLO_3RDPARTY_ROOT    -- Rood directory of holo 3rdparty project files. (Default ${HOLO_ROOT}/3rdparty)
#    HOLO_CONFIG_ROOT      -- Root directory of holo project configurations. (Default ${HOLO_ROOT}/config)
#    HOLO_LOG_ROOT         -- Root directory of holo logs. (Default ${HOLO_ROOT}/log)
#    CMAKE_INSTALL_PREFIX  -- Install prefix for holo project. (Default ${HOLO_ROOT}).
#    CMAKE_PREFIX_PATH     -- Additional prefix paths used for cmake to find packages. (Default "${HOLO_ROOT};${HOLO_3RDPARTY_ROOT}")
#

unset(_DEFAULT_HOLO_ROOT)
set(_DEFAULT_HOLO_ROOT "${CMAKE_SYSROOT}/opt/holo")

macro(_is_directory output dir)
    if(${dir} MATCHES "^(.*)/([^/]+)$")
        set(${output} TRUE)
        MESSAGE("${dir} is a directory")
    else()
        set(${output} FALSE)
        MESSAGE("${dir} is not a directory")
    endif()
endmacro()

if(NOT HOLO_ROOT)
    if(DEFINED ENV{HOLO_ROOT})
        _is_directory(_IS_DIRECTORY $ENV{HOLO_ROOT})
        if(_IS_DIRECTORY)
            set(HOLO_ROOT $ENV{HOLO_ROOT})
            MESSAGE(STATUS "Set holo root directory from environment variable HOLO_ROOT:$ENV{HOLO_ROOT}")
        else()
            MESSAGE(WARNING "Environment variable HOLO_ROOT is set to $ENV{HOLO_ROOT},"
                " but it is not a valid directory! Will set HOLO_ROOT to default value \"${_DEFAULT_HOLO_ROOT}\"")
            set(HOLO_ROOT ${_DEFAULT_HOLO_ROOT})
        endif()
    else()
        set(HOLO_ROOT ${_DEFAULT_HOLO_ROOT})
    endif()
else()
    _is_directory(_IS_DIRECTORY ${HOLO_ROOT})
    if(NOT _IS_DIRECTORY)
        MESSAGE(WARNING "HOLO_ROOT is set to \"${HOLO_ROOT}\" but it is not a valid directory!"
            " Will set HOLO_ROOT to default value \"${_DEFAULT_HOLO_ROOT}\"")
        set(HOLO_ROOT ${_DEFAULT_HOLO_ROOT})
    endif()
endif()

if(NOT HOLO_3RDPARTY_ROOT)
    if(DEFINED ENV{HOLO_3RDPARTY_ROOT})
        _is_directory(_IS_DIRECTORY $ENV{HOLO_3RDPARTY_ROOT})
        if(_IS_DIRECTORY)
            set(HOLO_3RDPARTY_ROOT $ENV{HOLO_3RDPARTY_ROOT})
            MESSAGE(STATUS "Set holo 3rdparty root directory from environment variable HOLO_3RDPARTY_ROOT:$ENV{HOLO_3RDPARTY_ROOT}")
        else()
            MESSAGE(WARNING "Environment variable HOLO_3RDPARTY_ROOT is set to $ENV{HOLO_3RDPARTY_ROOT},"
                " but it is not a valid directory! Will set HOLO_3RDPARTY_ROOT to default value \"${_DEFAULT_HOLO_ROOT}/3rdparty\"")
            set(HOLO_3RDPARTY_ROOT ${HOLO_ROOT}/3rdparty)
        endif()
    else()
        set(HOLO_3RDPARTY_ROOT ${HOLO_ROOT}/3rdparty)
    endif()
else()
    _is_directory(_IS_DIERCTORY ${HOLO_3RDPARTY_ROOT})
    if(NOT _IS_DIRECTORY)
        MESSAGE(WARNING "HOLO_3RDPARTY_ROOT is set to \"${HOLO_3RDPARTY_ROOT}\" but it is not a valid directory!"
            " Will set HOLO_3RDPARTY_ROOT to default value \"${_DEFAULT_HOLO_ROOT}/3rdparty\"")
        set(HOLO_3RDPARTY_ROOT ${HOLO_ROOT}/3rdparty)
    endif()
endif()

if(NOT HOLO_CONFIG_ROOT)
    if(DEFINED ENV{HOLO_CONFIG_ROOT})
        _is_directory(_IS_DIRECTORY $ENV{HOLO_CONFIG_ROOT})
        if(_IS_DIRECTORY)
            set(HOLO_CONFIG_ROOT $ENV{HOLO_CONFIG_ROOT})
            MESSAGE(STATUS "Set holo config root directory from environment variable HOLO_CONFIG_ROOT:$ENV{HOLO_CONFIG_ROOT}")
        else()
            MESSAGE(WARNING "Environment variable HOLO_CONFIG_ROOT is set to $ENV{HOLO_CONFIG_ROOT},"
                " but it is not a valid directory! Will set HOLO_CONFIG_ROOT to default value \"${_DEFAULT_HOLO_ROOT}/config\"")
            set(HOLO_CONFIG_ROOT ${HOLO_ROOT}/config)
        endif()
    else()
        set(HOLO_CONFIG_ROOT ${HOLO_ROOT}/config)
    endif()
else()
    _is_directory(_IS_DIERCTORY ${HOLO_CONFIG_ROOT})
    if(NOT _IS_DIRECTORY)
        MESSAGE(WARNING "HOLO_CONFIG_ROOT is set to \"${HOLO_CONFIG_ROOT}\" but it is not a valid directory!"
            " Will set HOLO_CONFIG_ROOT to default value \"${_DEFAULT_HOLO_ROOT}/config\"")
        set(HOLO_CONFIG_ROOT ${HOLO_ROOT}/config)
    endif()
endif()

if(NOT HOLO_LOG_ROOT)
    if(DEFINED ENV{HOLO_LOG_ROOT})
        _is_directory(_IS_DIRECTORY $ENV{HOLO_LOG_ROOT})
        if(_IS_DIRECTORY)
            set(HOLO_LOG_ROOT $ENV{HOLO_LOG_ROOT})
            MESSAGE(STATUS "Set holo log root directory from environment variable HOLO_LOG_ROOT:$ENV{HOLO_LOG_ROOT}")
        else()
            MESSAGE(WARNING "Environment variable HOLO_LOG_ROOT is set to $ENV{HOLO_LOG_ROOT},"
                " but it is not a valid directory! Will set HOLO_LOG_ROOT to default value \"${_DEFAULT_HOLO_ROOT}/log\"")
            set(HOLO_LOG_ROOT ${HOLO_ROOT}/log)
        endif()
    else()
        set(HOLO_LOG_ROOT ${HOLO_ROOT}/log)
    endif()
else()
    _is_directory(_IS_DIERCTORY ${HOLO_LOG_ROOT})
    if(NOT _IS_DIRECTORY)
        MESSAGE(WARNING "HOLO_LOG_ROOT is set to \"${HOLO_LOG_ROOT}\" but it is not a valid directory!"
            " Will set HOLO_LOG_ROOT to default value \"${_DEFAULT_HOLO_ROOT}/log\"")
        set(HOLO_LOG_ROOT ${HOLO_ROOT}/log)
    endif()
endif()

set(CMAKE_INSTALL_PREFIX ${HOLO_ROOT})
set(CMAKE_PREFIX_PATH ${HOLO_ROOT};${HOLO_3RDPARTY_ROOT};$ENV{CMAKE_PREFIX_PATH})
STRING(REPLACE ":" ";" CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}")

MESSAGE(STATUS "HOLO_ROOT=${HOLO_ROOT}")
MESSAGE(STATUS "HOLO_3RDPARTY_ROOT=${HOLO_3RDPARTY_ROOT}")
MESSAGE(STATUS "HOLO_CONFIG_ROOT=${HOLO_CONFIG_ROOT}")
MESSAGE(STATUS "HOLO_LOG_ROOT=${HOLO_LOG_ROOT}")

unset(_IS_DIRECTORY)
unset(_DEFAULT_HOLO_ROOT)
