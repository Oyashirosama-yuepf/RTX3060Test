/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file weather_condition.h
 * @brief Auto generated code for WeatherCondition format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_HFL_WEATHER_CONDITION_H_
#define HOLO_MAP_FORMAT_HFL_WEATHER_CONDITION_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/hfl/weather_condition.pb.h>

#include <holo/map/proto/common/interval_float64.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/interval_float64.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  WeatherCondition: public Base
{
public:

        
    enum WeatherType
    {
        WEATHER_TYPE_UNDEFINED=  0,  
        WEATHER_TYPE_SUNNY=  1,  
        WEATHER_TYPE_CLOUD=  2,  
        WEATHER_TYPE_RAIN=  3,  
        WEATHER_TYPE_WIND=  4,  
        WEATHER_TYPE_SNOW=  5,  
        WEATHER_TYPE_FOGGY=  6,  
        WEATHER_TYPE_HAIL=  7,  
        WEATHER_TYPE_MIXED=  8,  
        WEATHER_TYPE_OTHER=  9,  
    };

        
    enum RiskLevel
    {
        RISK_LEVEL_UNDEFINED=  0,  
        RISK_LEVEL_NORMAL=  1,  
        RISK_LEVEL_MILD=  2,  
        RISK_LEVEL_MEDIUM=  3,  
        RISK_LEVEL_DANGER=  4,  
        RISK_LEVEL_OTHERS=  5,  
    };

    static const ::std::map<::std::string, WeatherType>& ENUMSTR_WEATHERTYPE() 
    { 
        static const ::std::map<::std::string, WeatherType> data{
        { "UNDEFINED", WeatherType::WEATHER_TYPE_UNDEFINED },
        { "SUNNY", WeatherType::WEATHER_TYPE_SUNNY },
        { "CLOUD", WeatherType::WEATHER_TYPE_CLOUD },
        { "RAIN", WeatherType::WEATHER_TYPE_RAIN },
        { "WIND", WeatherType::WEATHER_TYPE_WIND },
        { "SNOW", WeatherType::WEATHER_TYPE_SNOW },
        { "FOGGY", WeatherType::WEATHER_TYPE_FOGGY },
        { "HAIL", WeatherType::WEATHER_TYPE_HAIL },
        { "MIXED", WeatherType::WEATHER_TYPE_MIXED },
        { "OTHER", WeatherType::WEATHER_TYPE_OTHER }};
        return data;
    }

    static const ::std::map<::std::string, RiskLevel>& ENUMSTR_RISKLEVEL() 
    { 
        static const ::std::map<::std::string, RiskLevel> data{
        { "UNDEFINED", RiskLevel::RISK_LEVEL_UNDEFINED },
        { "NORMAL", RiskLevel::RISK_LEVEL_NORMAL },
        { "MILD", RiskLevel::RISK_LEVEL_MILD },
        { "MEDIUM", RiskLevel::RISK_LEVEL_MEDIUM },
        { "DANGER", RiskLevel::RISK_LEVEL_DANGER },
        { "OTHERS", RiskLevel::RISK_LEVEL_OTHERS }};
        return data;
    }


private:
    ::std::uint64_t weather_condition_id_; 
    WeatherType weather_type_; 
    RiskLevel risk_level_; 
    ::std::uint32_t province_; 
    ::std::uint32_t city_; 
    ::std::vector<IntervalFloat64> weather_timestamp_; 

private:
    void DecodeProto(const ::holo::map::proto::hfl::WeatherCondition& _proto_handler);
    ::holo::map::proto::hfl::WeatherCondition EncodeProto();

public:
    WeatherCondition();
    explicit WeatherCondition(const ::holo::map::proto::hfl::WeatherCondition& _proto_handler);
    // init all format data
    WeatherCondition(const ::std::uint64_t _weather_condition_id,const WeatherType& _weather_type,const RiskLevel& _risk_level,const ::std::uint32_t _province,const ::std::uint32_t _city,const ::std::vector<IntervalFloat64>& _weather_timestamp);
    ~WeatherCondition();

    bool operator==(const ::holo::map::format::WeatherCondition& _other) const;
    WeatherCondition& operator=(const ::holo::map::proto::hfl::WeatherCondition& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::hfl::WeatherCondition GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetWeatherConditionId() const
    {
        return weather_condition_id_;
    }
    void SetWeatherConditionId(const ::std::uint64_t _weather_condition_id)
    {
        weather_condition_id_ = _weather_condition_id;
    }

    const WeatherType& GetWeatherType() const
    {
        return weather_type_;
    }
    void SetWeatherType(const WeatherType& _weather_type)
    {
        weather_type_ = _weather_type;
    }

    const RiskLevel& GetRiskLevel() const
    {
        return risk_level_;
    }
    void SetRiskLevel(const RiskLevel& _risk_level)
    {
        risk_level_ = _risk_level;
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

    const ::std::vector<IntervalFloat64>* GetPtrWeatherTimestamp() const
    {
        return &weather_timestamp_;
    }
    void SetWeatherTimestamp(const ::std::vector<IntervalFloat64>& _weather_timestamp)
    {
        weather_timestamp_ = _weather_timestamp;
    }


    void ClearWeatherTimestamp()
    {
        weather_timestamp_.clear();
    }
    void AddWeatherTimestampElement(const IntervalFloat64& _value)
    {
        weather_timestamp_.push_back(_value);
    }
    void UniqueAddWeatherTimestampElements(const ::std::vector<IntervalFloat64>& _value)
    {
        UniqueAppend(weather_timestamp_, _value);
    }









};  // class WeatherCondition

typedef ::std::shared_ptr<WeatherCondition> PtrWeatherCondition;
typedef const ::std::vector<WeatherCondition>* ConstRawPtrVecWeatherCondition;
typedef ::std::vector<WeatherCondition>* RawPtrVecWeatherCondition;
typedef ::std::shared_ptr<WeatherCondition const> ConstPtrWeatherCondition;
typedef ::std::shared_ptr<::std::vector<WeatherCondition> const> ConstPtrVecWeatherCondition;
typedef ::std::unordered_map<::std::uint64_t, PtrWeatherCondition> HashmapWeatherCondition;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_HFL_WEATHER_CONDITION_H_