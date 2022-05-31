/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file map_status_buffer.h
 * @brief Definition of map status container
 * @author wanghaiyang(wanghaiyang@holomatic.h)
 * @date 2019-12-13
 */

#ifndef HOLO_MAP_COMMON_CLASSES_MAP_STATUS_BUFFER_H_
#define HOLO_MAP_COMMON_CLASSES_MAP_STATUS_BUFFER_H_

#include <deque>

#include <holo/map/common/classes/map_status.h>
#include <holo/map/common/classes/spin_mutex.h>

namespace holo
{
namespace map
{
/**
 * @addtogroup map
 * @{
 *
 */

/**
 * @brief MapStatusBuffer is a singleton queue container.
 */
class MapStatusBuffer final
{
public:
    /**
     * @brief Access a global instance of MapStatus container.
     * 
     * @return Returns a instance of MapStatusBuffer.
     */
    static MapStatusBuffer* Instance();

    /**
     * @brief Removes all elements from the queue (which are destroyed), leaving an empty container.
     * 
     * @return Returns nothing.
     */
    void Clear() noexcept;

    /**
     * @brief Returns whether the queue container is empty (i.e. whether its size is 0).
     * 
     * @return Returns true: if the container size is 0;
     *         Returns false: Otherwise.
     */
    bool IsEmpty() const noexcept;

    /**
     * @brief Returns the number of elements in the queue buffer.
     * 
     * @return The number of elements in the container.
     */
    std::size_t GetCount() const noexcept;

    /**
     * @brief Add element at the end.
     * 
     * @param [in] s Value to be pushed at the tail of queue.
     * @return Returns nothing.
     */
    void PushBack(const MapStatus& s) noexcept;

    /**
     * @brief Delete last element.
     * 
     * @return Returns nothing.
     */
    void PopBack() noexcept;

    /**
     * @brief Insert element at beginning.
     * 
     * @param [in] s Value to be pushed at the head of queue.
     * @return Returns nothing.
     */
    void PushFront(const MapStatus& s) noexcept;

    /**
     * @brief Delete first element.
     * 
     * @return Returns nothing.
     */
    void PopFront() noexcept;
    
    /**
     * @brief Access first element.
     * 
     * @return Returns an object at the head of queue.
     */
    MapStatus GetFront() const noexcept;

    /**
     * @brief Access last element.
     * 
     * @return Returns an object at the tail of queue.
     */
    MapStatus GetBack() const noexcept;

    /**
     * @brief Access first element.
     * 
     * @note Not thread-safe.
     * @return Returns a const reference to the first element in the queue container.
     */
    const MapStatus& GetFrontUnsafe() const noexcept;

    /**
     * @brief Access last element
     * 
     * @note Not thread-safe.
     * @return Returns a const reference to the last element in the queue container.
     */
    const MapStatus& GetBackUnsafe() const noexcept;
    
private:
    /**
     * @brief Default constructor.
     * 
     * @return Returns nothing.
     */
    MapStatusBuffer() = default;

    /**
     * @brief Default destructor.
     * 
     * @return Returns nothing.
     */
    ~MapStatusBuffer() = default;

    /**
     * @brief Copy constructor.
     * 
     * @return Returns nothing.
     */
    MapStatusBuffer(const MapStatusBuffer&) = delete;

    /**
     * @brief Move constructor.
     * 
     * @return Returns nothing.
     */
    MapStatusBuffer(MapStatusBuffer&&) = delete;

    /**
     * @brief Copy assignment.
     * 
     * @return Returns *this;
     */
    MapStatusBuffer& operator=(const MapStatusBuffer&) = delete;

    /**
     * @brief Move assignment.
     * 
     * @return Returns *this.
     */
    MapStatusBuffer& operator=(MapStatusBuffer&&) = delete;

private:
    static MapStatusBuffer* MAP_STATIS_BUFFER_POINTER;

#ifdef HOLO_MAP_MULTITHREADS
    SpinMutex buffer_mutext_;
#endif // HOLO_MAP_MULTITHREADS

    std::deque<MapStatus> buffer_container_;
};

/**
 * @}
 */
} // namespace map
} // namespace holo

#ifndef HOLO_MAP_STATUS_GENERATOR_WITH_1_PARAMETER
#define HOLO_MAP_STATUS_GENERATOR_WITH_1_PARAMETER(code) \
    do { \
        holo::map::MapStatusBuffer* __map_status_buffer_instance__ = holo::map::MapStatusBuffer::Instance(); \
        if (nullptr != __map_status_buffer_instance__) \
        { \
            if (__map_status_buffer_instance__->IsEmpty()) \
            { \
                __map_status_buffer_instance__->PushBack(holo::map::MapStatus(code)); \
            } \
        } \
        else \
        { \
            LOG(ERROR) << "MapStatusBuffer::Instance fail, invalid instance with 1 parameter"; \
        } \
    } while (0);
#endif // HOLO_MAP_STATUS_GENERATOR_WITH_1_PARAMETER

#ifndef HOLO_MAP_STATUS_GENERATOR_WITH_2_PARAMETERS
#define HOLO_MAP_STATUS_GENERATOR_WITH_2_PARAMETERS(code, ts) \
    do { \
        holo::map::MapStatusBuffer* __map_status_buffer_instance__ = holo::map::MapStatusBuffer::Instance(); \
        if (nullptr != __map_status_buffer_instance__) \
        { \
            if (__map_status_buffer_instance__->IsEmpty()) \
            { \
                __map_status_buffer_instance__->PushBack(holo::map::MapStatus(code, ts)); \
            } \
        } \
        else \
        { \
            LOG(ERROR) << "MapStatusBuffer::Instance fail, invalid instance with 2 parameters"; \
        } \
    } while (0);
#endif // HOLO_MAP_STATUS_GENERATOR_WITH_2_PARAMETERS

#endif /* HOLO_MAP_COMMON_CLASSES_MAP_STATUS_BUFFER_H_ */
