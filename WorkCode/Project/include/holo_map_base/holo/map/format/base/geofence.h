/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file geofence.h
 * @brief Auto generated code for Geofence format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_BASE_GEOFENCE_H_
#define HOLO_MAP_FORMAT_BASE_GEOFENCE_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/base/geofence.pb.h>

#include <holo/map/proto/common/interval_uint64.pb.h>

#include <holo/map/proto/base/geofence_feature_info.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/interval_uint64.h>

#include <holo/map/format/base/geofence_feature_info.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  Geofence: public Base
{
public:

        
    enum Type
    {
        TYPE_UNKNOWN=  0,  
        TYPE_REGION_COMMON=  1,  
        TYPE_REGION_COUNTRY=  2,  
        TYPE_REGION_PROVINCE=  3,  
        TYPE_REGION_CITY=  4,  
        TYPE_REGION_COUNTY=  5,  
        TYPE_INTERVAL_COMMON=  6,  
    };

        
    enum Geotype
    {
        GEOTYPE_UNKNOWN=  0,  
        GEOTYPE_POLYLINE=  1,  
        GEOTYPE_POLYGON=  2,  
    };

        
    enum FeatureType
    {
        FEATURE_TYPE_LANE=  1,  
        FEATURE_TYPE_LINK=  2,  
        FEATURE_TYPE_ROAD=  3,  
    };

        
    enum ValidType
    {
        VALID_TYPE_UNKNOWN=  0,  
        VALID_TYPE_PERMANENT=  1,  
        VALID_TYPE_FROM_A_CERTAIN_POINT=  2,  
        VALID_TYPE_INTERMITTENT=  3,  
        VALID_TYPE_PERIODIC=  4,  
    };

    static const ::std::map<::std::string, Type>& ENUMSTR_TYPE() 
    { 
        static const ::std::map<::std::string, Type> data{
        { "UNKNOWN", Type::TYPE_UNKNOWN },
        { "REGION_COMMON", Type::TYPE_REGION_COMMON },
        { "REGION_COUNTRY", Type::TYPE_REGION_COUNTRY },
        { "REGION_PROVINCE", Type::TYPE_REGION_PROVINCE },
        { "REGION_CITY", Type::TYPE_REGION_CITY },
        { "REGION_COUNTY", Type::TYPE_REGION_COUNTY },
        { "INTERVAL_COMMON", Type::TYPE_INTERVAL_COMMON }};
        return data;
    }

    static const ::std::map<::std::string, Geotype>& ENUMSTR_GEOTYPE() 
    { 
        static const ::std::map<::std::string, Geotype> data{
        { "UNKNOWN", Geotype::GEOTYPE_UNKNOWN },
        { "POLYLINE", Geotype::GEOTYPE_POLYLINE },
        { "POLYGON", Geotype::GEOTYPE_POLYGON }};
        return data;
    }

    static const ::std::map<::std::string, FeatureType>& ENUMSTR_FEATURETYPE() 
    { 
        static const ::std::map<::std::string, FeatureType> data{
        { "LANE", FeatureType::FEATURE_TYPE_LANE },
        { "LINK", FeatureType::FEATURE_TYPE_LINK },
        { "ROAD", FeatureType::FEATURE_TYPE_ROAD }};
        return data;
    }

    static const ::std::map<::std::string, ValidType>& ENUMSTR_VALIDTYPE() 
    { 
        static const ::std::map<::std::string, ValidType> data{
        { "UNKNOWN", ValidType::VALID_TYPE_UNKNOWN },
        { "PERMANENT", ValidType::VALID_TYPE_PERMANENT },
        { "FROM_A_CERTAIN_POINT", ValidType::VALID_TYPE_FROM_A_CERTAIN_POINT },
        { "INTERMITTENT", ValidType::VALID_TYPE_INTERMITTENT },
        { "PERIODIC", ValidType::VALID_TYPE_PERIODIC }};
        return data;
    }


private:
    ::std::uint64_t geofence_id_; 
    ::std::uint32_t function_; 
    Type type_; 
    ::std::string version_; 
    ::std::uint32_t country_; 
    ::std::uint32_t province_; 
    ::std::uint32_t city_; 
    ::std::uint32_t county_; 
    Geotype geotype_; 
    ::std::string geometry_; 
    ::std::uint32_t level_; 
    ::std::vector<::std::uint64_t> tile_ids_; 
    FeatureType feature_type_; 
    ::std::vector<GeofenceFeatureInfo> feature_infos_; 
    bool enable_; 
    ValidType valid_type_; 
    ::std::vector<IntervalUint64> valid_time_; 
    ::std::uint64_t create_timestamp_; 
    ::std::uint64_t update_timestamp_; 

private:
    void DecodeProto(const ::holo::map::proto::base::Geofence& _proto_handler);
    ::holo::map::proto::base::Geofence EncodeProto();

public:
    Geofence();
    explicit Geofence(const ::holo::map::proto::base::Geofence& _proto_handler);
    // init all format data
    Geofence(const ::std::uint64_t _geofence_id,const ::std::uint32_t _function,const Type& _type,const ::std::string& _version,const ::std::uint32_t _country,const ::std::uint32_t _province,const ::std::uint32_t _city,const ::std::uint32_t _county,const Geotype& _geotype,const ::std::string& _geometry,const ::std::uint32_t _level,const ::std::vector<::std::uint64_t>& _tile_ids,const FeatureType& _feature_type,const ::std::vector<GeofenceFeatureInfo>& _feature_infos,const bool _enable,const ValidType& _valid_type,const ::std::vector<IntervalUint64>& _valid_time,const ::std::uint64_t _create_timestamp,const ::std::uint64_t _update_timestamp);
    ~Geofence();

    bool operator==(const ::holo::map::format::Geofence& _other) const;
    Geofence& operator=(const ::holo::map::proto::base::Geofence& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::base::Geofence GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetGeofenceId() const
    {
        return geofence_id_;
    }
    void SetGeofenceId(const ::std::uint64_t _geofence_id)
    {
        geofence_id_ = _geofence_id;
    }

    ::std::uint32_t GetFunction() const
    {
        return function_;
    }
    void SetFunction(const ::std::uint32_t _function)
    {
        function_ = _function;
    }

    const Type& GetType() const
    {
        return type_;
    }
    void SetType(const Type& _type)
    {
        type_ = _type;
    }

    const ::std::string& GetVersion() const
    {
        return version_;
    }
    void SetVersion(const ::std::string& _version)
    {
        version_ = _version;
    }

    ::std::uint32_t GetCountry() const
    {
        return country_;
    }
    void SetCountry(const ::std::uint32_t _country)
    {
        country_ = _country;
    }

    ::std::uint32_t GetProvince() const
    {
        return province_;
    }
    void SetProvince(const ::std::uint32_t _province)
    {
        province_ = _province;
    }

    ::std::uint32_t GetCity() const
    {
        return city_;
    }
    void SetCity(const ::std::uint32_t _city)
    {
        city_ = _city;
    }

    ::std::uint32_t GetCounty() const
    {
        return county_;
    }
    void SetCounty(const ::std::uint32_t _county)
    {
        county_ = _county;
    }

    const Geotype& GetGeotype() const
    {
        return geotype_;
    }
    void SetGeotype(const Geotype& _geotype)
    {
        geotype_ = _geotype;
    }

    const ::std::string& GetGeometry() const
    {
        return geometry_;
    }
    void SetGeometry(const ::std::string& _geometry)
    {
        geometry_ = _geometry;
    }

    ::std::uint32_t GetLevel() const
    {
        return level_;
    }
    void SetLevel(const ::std::uint32_t _level)
    {
        level_ = _level;
    }

    const ::std::vector<::std::uint64_t>* GetPtrTileIds() const
    {
        return &tile_ids_;
    }
    void SetTileIds(const ::std::vector<::std::uint64_t>& _tile_ids)
    {
        tile_ids_ = _tile_ids;
    }

    const FeatureType& GetFeatureType() const
    {
        return feature_type_;
    }
    void SetFeatureType(const FeatureType& _feature_type)
    {
        feature_type_ = _feature_type;
    }

    const ::std::vector<GeofenceFeatureInfo>* GetPtrFeatureInfos() const
    {
        return &feature_infos_;
    }
    void SetFeatureInfos(const ::std::vector<GeofenceFeatureInfo>& _feature_infos)
    {
        feature_infos_ = _feature_infos;
    }

    bool GetEnable() const
    {
        return enable_;
    }
    void SetEnable(const bool _enable)
    {
        enable_ = _enable;
    }

    const ValidType& GetValidType() const
    {
        return valid_type_;
    }
    void SetValidType(const ValidType& _valid_type)
    {
        valid_type_ = _valid_type;
    }

    const ::std::vector<IntervalUint64>* GetPtrValidTime() const
    {
        return &valid_time_;
    }
    void SetValidTime(const ::std::vector<IntervalUint64>& _valid_time)
    {
        valid_time_ = _valid_time;
    }

    ::std::uint64_t GetCreateTimestamp() const
    {
        return create_timestamp_;
    }
    void SetCreateTimestamp(const ::std::uint64_t _create_timestamp)
    {
        create_timestamp_ = _create_timestamp;
    }

    ::std::uint64_t GetUpdateTimestamp() const
    {
        return update_timestamp_;
    }
    void SetUpdateTimestamp(const ::std::uint64_t _update_timestamp)
    {
        update_timestamp_ = _update_timestamp;
    }


    void ClearTileIds()
    {
        tile_ids_.clear();
    }
    void AddTileIdsElement(const ::std::uint64_t& _value)
    {
        tile_ids_.push_back(_value);
    }
    void UniqueAddTileIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(tile_ids_, _value);
    }

    void ClearFeatureInfos()
    {
        feature_infos_.clear();
    }
    void AddFeatureInfosElement(const GeofenceFeatureInfo& _value)
    {
        feature_infos_.push_back(_value);
    }
    void UniqueAddFeatureInfosElements(const ::std::vector<GeofenceFeatureInfo>& _value)
    {
        UniqueAppend(feature_infos_, _value);
    }

    void ClearValidTime()
    {
        valid_time_.clear();
    }
    void AddValidTimeElement(const IntervalUint64& _value)
    {
        valid_time_.push_back(_value);
    }
    void UniqueAddValidTimeElements(const ::std::vector<IntervalUint64>& _value)
    {
        UniqueAppend(valid_time_, _value);
    }









};  // class Geofence

typedef ::std::shared_ptr<Geofence> PtrGeofence;
typedef const ::std::vector<Geofence>* ConstRawPtrVecGeofence;
typedef ::std::vector<Geofence>* RawPtrVecGeofence;
typedef ::std::shared_ptr<Geofence const> ConstPtrGeofence;
typedef ::std::shared_ptr<::std::vector<Geofence> const> ConstPtrVecGeofence;
typedef ::std::unordered_map<::std::uint64_t, PtrGeofence> HashmapGeofence;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_GEOFENCE_H_