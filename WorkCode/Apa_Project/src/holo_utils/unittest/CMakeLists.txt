add_library(unittest OBJECT EXCLUDE_FROM_ALL
	src/core/endian.cpp
	src/serialization/serialization.cpp
	src/thread/thread_pool.cpp
	src/thread/sync_queue.cpp
	src/thread/lockfree_queue.cpp
	src/thread/lockfree_stack.cpp
	src/thread/lockfree_circular_queue.cpp
	src/thread/object_pool.cpp
)

target_link_libraries(unittest holo_utils)
