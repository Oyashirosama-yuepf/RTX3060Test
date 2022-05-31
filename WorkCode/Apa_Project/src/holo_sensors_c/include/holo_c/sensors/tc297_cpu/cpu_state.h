/*!
 * @file cpu_state_driver.h
 * @brief This header file defines tc297 cpu state structure and functions
 * @author liuya@holomatic.com
 * @date 2020-02-24
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_C_SENSORS_TC297_CPU_CPU_STATE_H_
#define HOLO_C_SENSORS_TC297_CPU_CPU_STATE_H_

#include <holo_c/common/timestamp.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup sensors
 * @{
 */

#define TASK_MAX_NUM 16
#define TASK_NAME_MAX_LEN 16

/**
 * @brief TC297 task state
 *
 */
struct TaskState
{
    char      task_name[TASK_NAME_MAX_LEN];
    float32_t cpu_load;
};
HOLO_STATIC_ASSERT(sizeof(struct TaskState) == 20);

/**
 * @brief TC297 CPU state
 *
 */
struct CpuState
{
    struct Timestamp timestamp;
    uint16_t         core_id;
    uint16_t         task_num;
    struct TaskState list[TASK_MAX_NUM];
};
HOLO_STATIC_ASSERT(sizeof(struct CpuState) == 332);

/**
 * @brief Set cpu state timestamp
 *
 * @param state Cpu state pointer
 * @param timestamp Time stamp pointer
 * @return retcode_t RC_SUCCESS
 */
retcode_t cpu_state_set_timestamp(struct CpuState* state, const struct Timestamp* timestamp);

/**
 * @brief Set cpu state core id
 *
 * @param state Cpu state pointer
 * @param id Core id
 * @return retcode_t RC_SUCCESS
 */
retcode_t cpu_state_set_core_id(struct CpuState* state, uint16_t id);

/**
 * @brief Set cpu state task number
 *
 * @param state Cpu state pointer
 * @param num Task number
 * @return retcode_t RC_SUCCESS
 */
retcode_t cpu_state_set_task_num(struct CpuState* state, uint16_t num);

/**
 * @brief Set task name
 *
 * @param state Cpu state pointer
 * @param index Task index
 * @param name Task name
 * @return retcode_t RC_SUCCESS
 */
retcode_t cpu_state_set_task_name(struct CpuState* state, uint16_t index, char* name);

/**
 * @brief Set task's cpu load
 *
 * @param state Cpu state pointer
 * @param load Task's cpu load
 * @return retcode_t RC_SUCCESS
 */
retcode_t cpu_state_set_cpu_load(struct CpuState* state, uint16_t index, float32_t load);

/**
 * @brief Get cpu state timestamp
 *
 * @param state Cpu state pointer
 * @return const struct Timestamp* Timestamp pointer
 */
const struct Timestamp* cpu_state_get_timestamp(struct CpuState* state);

/**
 * @brief Get cpu core id
 *
 * @param state Cpu state pointer
 * @return uint16_t Core id
 */
uint16_t cpu_state_get_core_id(struct CpuState* state);

/**
 * @brief Get task number
 *
 * @param state Cpu state pointer
 * @return uint16_t Task number
 */
uint16_t cpu_state_get_task_num(struct CpuState* state);

/**
 * @brief Get task name
 *
 * @param state Cpu state pointer
 * @param index Task index
 * @return char* Task name
 */
char* cpu_state_get_task_name(struct CpuState* state, uint16_t index);

/**
 * @brief Get task's cpu load
 *
 * @param state Cpu state pointer
 * @param index Task index
 * @return float32_t Task's cpu load
 */
float32_t cpu_state_get_cpu_load(struct CpuState* state, uint16_t index);

/**
 * @brief Get cpu state serialized size
 *
 * @param state Cpu state pointer
 * @return uint32_t Serailized size
 */
uint32_t cpu_state_get_serialized_size(const struct CpuState* state);

/**
 * @brief Seriliaze cpu state to buffer
 *
 * @param state Cpu state pointer
 * @param buffer Buffer to store serialize result
 * @param buffer_size Buffer size
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW if buffer_size is smaller than needed
 * @return Positive integer Number of bytes serialized into buffer
 */
retcode_t cpu_state_serialize(const struct CpuState* state, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize cpu state from buffer
 *
 * @param state Cpu state pointer
 * @param buffer The buffer to deserialize from
 * @param buffer_size Buffer size
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW if buffer_size is smaller than needed
 * @return Positive integer Number of bytes deserialized from buffer
 */
retcode_t cpu_state_deserialize(struct CpuState* state, const uint8_t* buffer, uint32_t buffer_size);

#ifdef __cplusplus
}
#endif

#endif
