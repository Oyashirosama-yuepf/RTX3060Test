set(_OLD_CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH})
set(CMAKE_PREFIX_PATH ${HOLO_3RDPARTY_ROOT}/torch ${CMAKE_PREFIX_PATH})

if(NOT TORCH_FOUND)
    # Torch cmake script will try to compile and run a test program.
    # In cross compiling mode, the compiled program cannot be executed on host machine. 
    # So cmake will bypass run program step when cross compiling.
    # But cmake still needs to know the program output to continue configuration.
    #
    # The following variables provide necessary output needed by cmake.
    # 
    if(CMAKE_CROSSCOMPILING)
        set( run_result 
             "0"
             CACHE STRING "Result from TRY_RUN" FORCE)
        
        set( run_result__TRYRUN_OUTPUT 
             ${CUDA_VERSION_STRING}
             CACHE STRING "Output from TRY_RUN" FORCE)
    endif()

    if(TORCH_FIND_REQUIRED)
        find_package(Torch ${TORCH_FIND_VERSION} REQUIRED)
    else()
        find_package(Torch ${TORCH_FIND_VERSION} QUIET)
    endif()

endif()

set(CMAKE_PREFIX_PATH ${_OLD_CMAKE_PREFIX_PATH})
