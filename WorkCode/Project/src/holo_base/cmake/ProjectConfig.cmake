if(HOLO_CONFIG_USE_FIXED_SIZE_CONTAINER)
    set(HOLO_CONFIG_USE_FIXED_SIZE_CONTAINER 1)
else()
    set(HOLO_CONFIG_USE_FIXED_SIZE_CONTAINER 0)
endif()

MACRO(CONFIG_CONTAINER type)
    if(HOLO_CONFIG_USE_FIXED_SIZE_CONTAINER)
        if(DEFINED HOLO_CONFIG_USE_FIXED_SIZE_${type} AND NOT HOLO_CONFIG_USE_FIXED_SIZE_${type})
            set(HOLO_CONFIG_USE_FIXED_SIZE_${type} 0)
        else()
            set(HOLO_CONFIG_USE_FIXED_SIZE_${type} 1)
        endif()
    else()
        if(DEFINED HOLO_CONFIG_USE_FIXED_SIZE_${type} AND HOLO_CONFIG_USE_FIXED_SIZE_${type})
            set(HOLO_CONFIG_USE_FIXED_SIZE_${type} 1)
        else()
            set(HOLO_CONFIG_USE_FIXED_SIZE_${type} 0)
        endif()
    endif()
ENDMACRO()

set(container_types 
    VECTOR 
    DEQUE 
    LIST 
    FORWARD_LIST 
    MAP 
    MULTIMAP 
    SET 
    MULTISET 
    UNORDERED_MAP 
    UNORDERED_MULTIMAP 
    UNORDERED_SET 
    UNORDERED_MULTISET
    )

foreach(type ${container_types})
    CONFIG_CONTAINER(${type})
endforeach()
