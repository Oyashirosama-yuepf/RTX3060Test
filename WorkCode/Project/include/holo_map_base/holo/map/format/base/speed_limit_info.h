/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file speed_limit_info.h
 * @brief Auto generated code for SpeedLimitInfo format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_BASE_SPEED_LIMIT_INFO_H_
#define HOLO_MAP_FORMAT_BASE_SPEED_LIMIT_INFO_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/base/speed_limit_info.pb.h>


#include <holo/map/format/base/base.h>


#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  SpeedLimitInfo: public Base
{
public:




private:
    double start_pos_; 
    double end_pos_; 
    ::std::uint32_t max_speed_; 
    ::std::uint32_t min_speed_; 

private:
    void DecodeProto(const ::holo::map::proto::base::SpeedLimitInfo& _proto_handler);
    ::holo::map::proto::base::SpeedLimitInfo EncodeProto();

public:
    SpeedLimitInfo();
    explicit SpeedLimitInfo(const ::holo::map::proto::base::SpeedLimitInfo& _proto_handler);
    // init all format data
    SpeedLimitInfo(const double _start_pos,const double _end_pos,const ::std::uint32_t _max_speed,const ::std::uint32_t _min_speed);
    ~SpeedLimitInfo();

    bool operator==(const ::holo::map::format::SpeedLimitInfo& _other) const;
    SpeedLimitInfo& operator=(const ::holo::map::proto::base::SpeedLimitInfo& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::base::SpeedLimitInfo GetProtoHandler()
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

    ::std::uint32_t GetMaxSpeed() const
    {
        return max_speed_;
    }
    void SetMaxSpeed(const ::std::uint32_t _max_speed)
    {
        max_speed_ = _max_speed;
    }

    ::std::uint32_t GetMinSpeed() const
    {
        return min_speed_;
    }
    void SetMinSpeed(const ::std::uint32_t _min_speed)
    {
        min_speed_ = _min_speed;
    }











};  // class SpeedLimitInfo

typedef ::std::shared_ptr<SpeedLimitInfo> PtrSpeedLimitInfo;
typedef const ::std::vector<SpeedLimitInfo>* ConstRawPtrVecSpeedLimitInfo;
typedef ::std::vector<SpeedLimitInfo>* RawPtrVecSpeedLimitInfo;
typedef ::std::shared_ptr<SpeedLimitInfo const> ConstPtrSpeedLimitInfo;
typedef ::std::shared_ptr<::std::vector<SpeedLimitInfo> const> ConstPtrVecSpeedLimitInfo;
typedef ::std::unordered_map<::std::uint64_t, PtrSpeedLimitInfo> HashmapSpeedLimitInfo;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_SPEED_LIMIT_INFO_H_