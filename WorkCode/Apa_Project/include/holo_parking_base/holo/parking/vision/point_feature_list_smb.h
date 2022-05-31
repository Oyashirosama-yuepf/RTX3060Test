/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point_feature_list_smb.h.
 * @brief Point feature list shared memery block.
 * @author guo peikai(guopeikai@holomatic.com).
 * @date 2021-04-24.
 */

#ifndef _HOLO_PARKING_VISION_POINT_FEATURE_LIST_SMB_H
#define _HOLO_PARKING_VISION_POINT_FEATURE_LIST_SMB_H

#include <holo/os/shared_memory_block.h>
#include <holo/utils/serialization_exception.h>
#include <holo/utils/buffer.h>
#include <holo/parking/vision/point_feature_list_common_types.h>

namespace holo
{
namespace parking
{
namespace vision
{
class PointFeatureListSMBWriter
{
public:
    /**
     * @brief Construct a new Point Feature List SMB Writer object
     *
     * @param smb_name
     */
    PointFeatureListSMBWriter(const std::string& smb_name, uint16_t block_size);

    /**
     * @brief Destroy the Point Feature List SMB Writer object
     *
     */
    ~PointFeatureListSMBWriter();

    /**
     * @brief this function is used to get shared memory block Ptr to set data
     *
     *
     * @return point feature list ptr and writer index
     */
    std::pair<PointFeaturefList_ST*, uint16_t> GetSMBBlockPtrAndWriterIndexToSetData();

private:
    holo::os::SharedMemoryBlockWriter point_feature_list_smb_writer_;
    uint16_t                          write_msg_index_;
    uint32_t                          block_size_;
};

class PointFeatureListSMBReader
{
public:
    /**
     * @brief Construct a new Point Feature List SMB Reader object
     *
     * @param smb_name
     */
    PointFeatureListSMBReader(const std::string& smb_name);

    /**
     * @brief Destroy the Point Feature List SMB Reader object
     *
     */
    ~PointFeatureListSMBReader();

    /**
     * @brief this function is used to get point feature list Ptr from shared
     * memory block
     *
     * @param[in] read_msg_index  share memory block index
     *
     * @return point feature list Ptr
     */
    PointFeaturefList_ST* GetPointFeatureListDataPtr(uint16_t read_msg_index);

private:
    holo::os::SharedMemoryBlockReader point_feature_list_smb_reader_;
};

}  // namespace vision
}  // namespace parking
}  // namespace holo
#endif  //_HOLO_PARKING_VISION_POINT_FEATURE_LIST_SMB_H