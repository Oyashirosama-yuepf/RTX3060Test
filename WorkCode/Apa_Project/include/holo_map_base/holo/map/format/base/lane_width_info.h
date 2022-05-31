/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_width_info.h
 * @brief Auto generated code for LaneWidthInfo format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_BASE_LANE_WIDTH_INFO_H_
#define HOLO_MAP_FORMAT_BASE_LANE_WIDTH_INFO_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/base/lane_width_info.pb.h>


#include <holo/map/format/base/base.h>


#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  LaneWidthInfo: public Base
{
public:




private:
    double start_pos_; 
    double end_pos_; 
    ::std::uint32_t lane_width_cm_; 

private:
    void DecodeProto(const ::holo::map::proto::base::LaneWidthInfo& _proto_handler);
    ::holo::map::proto::base::LaneWidthInfo EncodeProto();

public:
    LaneWidthInfo();
    explicit LaneWidthInfo(const ::holo::map::proto::base::LaneWidthInfo& _proto_handler);
    // init all format data
    LaneWidthInfo(const double _start_pos,const double _end_pos,const ::std::uint32_t _lane_width_cm);
    ~LaneWidthInfo();

    bool operator==(const ::holo::map::format::LaneWidthInfo& _other) const;
    LaneWidthInfo& operator=(const ::holo::map::proto::base::LaneWidthInfo& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::base::LaneWidthInfo GetProtoHandler()
    {
        return EncodeProto();
    }

    


    double GetStartPos() const
    {
        return start_pos_;
    }
    void SetStartPos(const double _start_pos)
    {
        start_pos_ = _start_pos;
    }

    double GetEndPos() const
    {
        return end_pos_;
    }
    void SetEndPos(const double _end_pos)
    {
        end_pos_ = _end_pos;
    }

    ::std::uint32_t GetLaneWidthCm() const
    {
        return lane_width_cm_;
    }
    void SetLaneWidthCm(const ::std::uint32_t _lane_width_cm)
    {
        lane_width_cm_ = _lane_width_cm;
    }











};  // class LaneWidthInfo

typedef ::std::shared_ptr<LaneWidthInfo> PtrLaneWidthInfo;
typedef const ::std::vector<LaneWidthInfo>* ConstRawPtrVecLaneWidthInfo;
typedef ::std::vector<LaneWidthInfo>* RawPtrVecLaneWidthInfo;
typedef ::std::shared_ptr<LaneWidthInfo const> ConstPtrLaneWidthInfo;
typedef ::std::shared_ptr<::std::vector<LaneWidthInfo> const> ConstPtrVecLaneWidthInfo;
typedef ::std::unordered_map<::std::uint64_t, PtrLaneWidthInfo> HashmapLaneWidthInfo;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_LANE_WIDTH_INFO_H_