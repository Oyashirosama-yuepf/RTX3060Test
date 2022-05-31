/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file geofence_feature_info.h
 * @brief Auto generated code for GeofenceFeatureInfo format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_BASE_GEOFENCE_FEATURE_INFO_H_
#define HOLO_MAP_FORMAT_BASE_GEOFENCE_FEATURE_INFO_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/base/geofence_feature_info.pb.h>


#include <holo/map/format/base/base.h>


#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  GeofenceFeatureInfo: public Base
{
public:




private:
    ::std::uint64_t feature_id_; 
    double start_pos_; 
    double end_pos_; 

private:
    void DecodeProto(const ::holo::map::proto::base::GeofenceFeatureInfo& _proto_handler);
    ::holo::map::proto::base::GeofenceFeatureInfo EncodeProto();

public:
    GeofenceFeatureInfo();
    explicit GeofenceFeatureInfo(const ::holo::map::proto::base::GeofenceFeatureInfo& _proto_handler);
    // init all format data
    GeofenceFeatureInfo(const ::std::uint64_t _feature_id,const double _start_pos,const double _end_pos);
    ~GeofenceFeatureInfo();

    bool operator==(const ::holo::map::format::GeofenceFeatureInfo& _other) const;
    GeofenceFeatureInfo& operator=(const ::holo::map::proto::base::GeofenceFeatureInfo& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::base::GeofenceFeatureInfo GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetFeatureId() const
    {
        return feature_id_;
    }
    void SetFeatureId(const ::std::uint64_t _feature_id)
    {
        feature_id_ = _feature_id;
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











};  // class GeofenceFeatureInfo

typedef ::std::shared_ptr<GeofenceFeatureInfo> PtrGeofenceFeatureInfo;
typedef const ::std::vector<GeofenceFeatureInfo>* ConstRawPtrVecGeofenceFeatureInfo;
typedef ::std::vector<GeofenceFeatureInfo>* RawPtrVecGeofenceFeatureInfo;
typedef ::std::shared_ptr<GeofenceFeatureInfo const> ConstPtrGeofenceFeatureInfo;
typedef ::std::shared_ptr<::std::vector<GeofenceFeatureInfo> const> ConstPtrVecGeofenceFeatureInfo;
typedef ::std::unordered_map<::std::uint64_t, PtrGeofenceFeatureInfo> HashmapGeofenceFeatureInfo;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_GEOFENCE_FEATURE_INFO_H_