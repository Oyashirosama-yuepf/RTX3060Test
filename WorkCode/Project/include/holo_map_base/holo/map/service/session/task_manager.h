/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file task_manager.h
 * @brief Session manager.
 * @author wanghaiyang@holomatic.com
 * @date "2020-11-12"
 */

#ifndef HOLO_MAP_SERVICE_SESSION_TASK_MANAGER_H_
#define HOLO_MAP_SERVICE_SESSION_TASK_MANAGER_H_

#include <map>
#include <string>

#include <holo/log/hololog.h>

#include <holo/map/common/types.h>
#include <holo/map/service/io/types.h>
#include <holo/map/service/session/utility.h>

namespace holo
{
namespace map
{
namespace service
{
namespace session
{
/**
 * @addtogroup session
 * @{
 *
 */

/**
 * @brief Task package, container multiple session fro every sequence id. If a data package
 *        is too large, we will split it into multiple slices.
 */
struct TaskPackage
{
    /// Redefine type for inner members.
    using SessionType       = holo::map::service::session::SessionType;
    using SessionPtrType    = holo::map::service::session::SessionPtrType;

    using SequenceIdType     = SessionType::SequenceIdType;
    using SliceIndexType     = SessionType::SliceIndexType;
    using SliceCountType     = SessionType::SliceCountType;

    using ContainerType      = std::map<SliceIndexType, SessionPtrType>;

    /// Sequence id, it used for identifying who those sessions are belonged to.
    SequenceIdType          sequence_id = 0;
    /// Slice count, if the package is compeleted, this value should equal to size of container.
    SliceCountType          slice_count = 0;
    /// Slice container, contains all the slices for a large package.
    ContainerType           container;

    /**
     * @brief Format task session container to a JSON string.
     * 
     * @param[in] container Task session container.
     * @return A JSON string.
     */
    static std::string FormatToString(ContainerType const& container);

    /**
     * @brief Format a task package to a JSON string.
     * 
     * @param[in] package A task package.
     * @return A JSON string.
     */
    static std::string FormatToString(TaskPackage const& package);

};

/**
 * @brief Task bucket, contains multiple session packages, client maybe setup multiple
 *        request, therefore server shoule handle all the requests at the same time.
 */
struct TaskBucket
{
    /// Redefine type for inner members.
    using SessionType       = holo::map::service::session::SessionType;
    using SessionPtrType    = holo::map::service::session::SessionPtrType;

    using TokenIdType       = SessionType::TokenIdType;
    using SequenceIdType    = SessionType::SequenceIdType;

    /// Redefine task container.
    using ContainerType = std::map<SequenceIdType, TaskPackage>;
    
    /// UUID for map service client.
    TokenIdType                 token_id = 0;
    /// Task package container.
    ContainerType               container;

    /**
     * @brief Format task package container to a JSON string.
     * 
     * @param[in] container Task package container.
     * @return A JSON string.
     */
    static std::string FormatToString(ContainerType const& container);

    /**
     * @brief Format a task bucket to a JSON string.
     * 
     * @param[in] package A task bucket.
     * @return A JSON string.
     */
    static std::string FormatToString(TaskBucket const& item);
};

/**
 * @brief Manage all the session task for all the client.
 */
class TaskManager
{
public:
    /// Redefine inner type for inner members.
    using TokenIdType           = TaskBucket::TokenIdType;
    using SessionIdType         = TaskBucket::SequenceIdType;
    using SliceIndexType        = TaskPackage::SliceIndexType;
    using SliceCountType        = TaskPackage::SliceCountType;
    
    /// Redefine container type for TaskBucket.
    using ContainerType         = std::map<TokenIdType, TaskBucket>;
    
    /// Redefine Session types.
    using SessionPtrType        = holo::map::service::session::SessionPtrType;
    using SessionPtrVectorType  = holo::map::service::session::SessionPtrVectorType;

    /**
     * @brief Constructor.
     */
    TaskManager() = default;

    /**
     * @brief Desconstructor.
     */
    virtual ~TaskManager() = default;

    TaskManager(TaskManager const&) = delete;
    TaskManager(TaskManager&&) = delete;
    TaskManager& operator = (TaskManager const&) = delete;
    TaskManager& operator = (TaskManager&&) = delete;

    /**
     * @brief Access verbose flag.
     * 
     * @return Verbose flag.
     */
    holo::bool_t GetVerbose() const noexcept;

    /**
     * @brief Assign verbose flag.
     *  
     * @param[in] v If true, TaskManager object will print debug message to log.
     */
    void SetVerbose(holo::bool_t const v);

    /**
     * @brief Add session slice to session container.
     * 
     * @note Task manager only refer to session slice pointer, don't release it, the caller
     *       should handle the lifecycle of this pointer.
     * 
     * @param[in] ptr A session slice pointer.
     * @return true: No error.
     *         false: An error occurs in this function.
     */
    holo::bool_t AddTask(SessionType* ptr);

    /**
     * @brief If a session task is ready, get the complete session back and remove them
     *        from task manager.
     * 
     * @param[in] token_id UUID for map client.
     * @param[in] session_id Session id.
     * @param[out] package a complete session task.
     * @return true: No error.
     *         false: An error occurs in this function.
     */
    holo::bool_t DropTask(TokenIdType const token_id, SessionIdType const session_id,
        SessionPtrVectorType& sessions);

    /**
     * @brief Whether or not a session task is ready.
     * 
     * @param[in] token_id UUID for map client.
     * @param[in] session_id Session id.
     * @return true: The session task is ready.
     *         false: The session task is not ready.
     */
    holo::bool_t IsTaskReady(TokenIdType const token_id, SessionIdType const session_id) const;

    /**
     * @brief Access the status information.
     *
     * @return Status information with JSON format.
     */
    std::string GetStatus() const;

private:
    /// Handle all the sessions for all the clients.
    ContainerType   buckets_;
    /// If true, print debugging message to log.
    holo::bool_t    verbose_ = false;
}; ///< End of class TaskManager

/**
 * @}
 *
 */

} ///< namespace session
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_SESSION_TASK_MANAGER_H_ */
