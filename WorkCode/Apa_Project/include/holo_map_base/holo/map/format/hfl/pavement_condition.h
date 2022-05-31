/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pavement_condition.h
 * @brief Auto generated code for PavementCondition format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_HFL_PAVEMENT_CONDITION_H_
#define HOLO_MAP_FORMAT_HFL_PAVEMENT_CONDITION_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/hfl/pavement_condition.pb.h>

#include <holo/map/proto/common/interval_float64.pb.h>

#include <holo/map/proto/common/interval_type.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/interval_float64.h>

#include <holo/map/format/common/interval_type.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  PavementCondition: public Base
{
public:

        
    enum PavementType
    {
        PAVEMENT_TYPE_UNDEFINED=  0,  
        PAVEMENT_TYPE_ROAD_CONSTRUCTION=  1,  
        PAVEMENT_TYPE_PAVEMENT_ABNORMALITY=  2,  
        PAVEMENT_TYPE_ROAD_CLOSED=  3,  
        PAVEMENT_TYPE_ROAD_CHANGED=  4,  
        PAVEMENT_TYPE_FACILITY_MAINTENANCE=  5,  
        PAVEMENT_TYPE_OTHER=  6,  
    };

        
    enum PavementAbnormalityType
    {
        PAVEMENT_ABNORMALITY_TYPE_UNDEFINED=  0,  
        PAVEMENT_ABNORMALITY_TYPE_ICE=  1,  
        PAVEMENT_ABNORMALITY_TYPE_WATER=  2,  
        PAVEMENT_ABNORMALITY_TYPE_PAVEMENT_UP=  3,  
        PAVEMENT_ABNORMALITY_TYPE_PAVEMENT_DOWN=  4,  
        PAVEMENT_ABNORMALITY_TYPE_CRACK=  5,  
        PAVEMENT_ABNORMALITY_TYPE_OTHER=  6,  
    };

        
    enum FacilityMaintenanceType
    {
        FACILITY_MAINTENANCE_TYPE_UNDEFINED=  0,  
        FACILITY_MAINTENANCE_TYPE_TRAFFIC_LIGHT=  1,  
        FACILITY_MAINTENANCE_TYPE_WELL=  2,  
        FACILITY_MAINTENANCE_TYPE_MARKING_PAINTED=  3,  
        FACILITY_MAINTENANCE_TYPE_LANE_BOUNDARY=  4,  
        FACILITY_MAINTENANCE_TYPE_OTHER=  5,  
    };

    static const ::std::map<::std::string, PavementType>& ENUMSTR_PAVEMENTTYPE() 
    { 
        static const ::std::map<::std::string, PavementType> data{
        { "UNDEFINED", PavementType::PAVEMENT_TYPE_UNDEFINED },
        { "ROAD_CONSTRUCTION", PavementType::PAVEMENT_TYPE_ROAD_CONSTRUCTION },
        { "PAVEMENT_ABNORMALITY", PavementType::PAVEMENT_TYPE_PAVEMENT_ABNORMALITY },
        { "ROAD_CLOSED", PavementType::PAVEMENT_TYPE_ROAD_CLOSED },
        { "ROAD_CHANGED", PavementType::PAVEMENT_TYPE_ROAD_CHANGED },
        { "FACILITY_MAINTENANCE", PavementType::PAVEMENT_TYPE_FACILITY_MAINTENANCE },
        { "OTHER", PavementType::PAVEMENT_TYPE_OTHER }};
        return data;
    }

    static const ::std::map<::std::string, PavementAbnormalityType>& ENUMSTR_PAVEMENTABNORMALITYTYPE() 
    { 
        static const ::std::map<::std::string, PavementAbnormalityType> data{
        { "UNDEFINED", PavementAbnormalityType::PAVEMENT_ABNORMALITY_TYPE_UNDEFINED },
        { "ICE", PavementAbnormalityType::PAVEMENT_ABNORMALITY_TYPE_ICE },
        { "WATER", PavementAbnormalityType::PAVEMENT_ABNORMALITY_TYPE_WATER },
        { "PAVEMENT_UP", PavementAbnormalityType::PAVEMENT_ABNORMALITY_TYPE_PAVEMENT_UP },
        { "PAVEMENT_DOWN", PavementAbnormalityType::PAVEMENT_ABNORMALITY_TYPE_PAVEMENT_DOWN },
        { "CRACK", PavementAbnormalityType::PAVEMENT_ABNORMALITY_TYPE_CRACK },
        { "OTHER", PavementAbnormalityType::PAVEMENT_ABNORMALITY_TYPE_OTHER }};
        return data;
    }

    static const ::std::map<::std::string, FacilityMaintenanceType>& ENUMSTR_FACILITYMAINTENANCETYPE() 
    { 
        static const ::std::map<::std::string, FacilityMaintenanceType> data{
        { "UNDEFINED", FacilityMaintenanceType::FACILITY_MAINTENANCE_TYPE_UNDEFINED },
        { "TRAFFIC_LIGHT", FacilityMaintenanceType::FACILITY_MAINTENANCE_TYPE_TRAFFIC_LIGHT },
        { "WELL", FacilityMaintenanceType::FACILITY_MAINTENANCE_TYPE_WELL },
        { "MARKING_PAINTED", FacilityMaintenanceType::FACILITY_MAINTENANCE_TYPE_MARKING_PAINTED },
        { "LANE_BOUNDARY", FacilityMaintenanceType::FACILITY_MAINTENANCE_TYPE_LANE_BOUNDARY },
        { "OTHER", FacilityMaintenanceType::FACILITY_MAINTENANCE_TYPE_OTHER }};
        return data;
    }


private:
    ::std::uint64_t pavement_condition_id_; 
    PavementType pavement_type_; 
    PavementAbnormalityType pavement_abnormality_type_; 
    FacilityMaintenanceType facility_maintenance_type_; 
    ::std::vector<IntervalFloat64> pavement_pos_; 
    IntervalType pavement_pos_type_; 
    ::std::uint32_t width_cm_; 
    ::std::vector<IntervalFloat64> exist_timestamp_; 
    ::std::uint64_t create_timestamp_; 
    ::std::uint64_t update_timestamp_; 

private:
    void DecodeProto(const ::holo::map::proto::hfl::PavementCondition& _proto_handler);
    ::holo::map::proto::hfl::PavementCondition EncodeProto();

public:
    PavementCondition();
    explicit PavementCondition(const ::holo::map::proto::hfl::PavementCondition& _proto_handler);
    // init all format data
    PavementCondition(const ::std::uint64_t _pavement_condition_id,const PavementType& _pavement_type,const PavementAbnormalityType& _pavement_abnormality_type,const FacilityMaintenanceType& _facility_maintenance_type,const ::std::vector<IntervalFloat64>& _pavement_pos,const IntervalType& _pavement_pos_type,const ::std::uint32_t _width_cm,const ::std::vector<IntervalFloat64>& _exist_timestamp,const ::std::uint64_t _create_timestamp,const ::std::uint64_t _update_timestamp);
    ~PavementCondition();

    bool operator==(const ::holo::map::format::PavementCondition& _other) const;
    PavementCondition& operator=(const ::holo::map::proto::hfl::PavementCondition& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::hfl::PavementCondition GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetPavementConditionId() const
    {
        return pavement_condition_id_;
    }
    void SetPavementConditionId(const ::std::uint64_t _pavement_condition_id)
    {
        pavement_condition_id_ = _pavement_condition_id;
    }

    const PavementType& GetPavementType() const
    {
        return pavement_type_;
    }
    void SetPavementType(const PavementType& _pavement_type)
    {
        pavement_type_ = _pavement_type;
    }

    const PavementAbnormalityType& GetPavementAbnormalityType() const
    {
        return pavement_abnormality_type_;
    }
    void SetPavementAbnormalityType(const PavementAbnormalityType& _pavement_abnormality_type)
    {
        pavement_abnormality_type_ = _pavement_abnormality_type;
    }

    const FacilityMaintenanceType& GetFacilityMaintenanceType() const
    {
        return facility_maintenance_type_;
    }
    void SetFacilityMaintenanceType(const FacilityMaintenanceType& _facility_maintenance_type)
    {
        facility_maintenance_type_ = _facility_maintenance_type;
    }

    const ::std::vector<IntervalFloat64>* GetPtrPavementPos() const
    {
        return &pavement_pos_;
    }
    void SetPavementPos(const ::std::vector<IntervalFloat64>& _pavement_pos)
    {
        pavement_pos_ = _pavement_pos;
    }

    const IntervalType& GetPavementPosType() const
    {
        return pavement_pos_type_;
    }
    void SetPavementPosType(const IntervalType& _pavement_pos_type)
    {
        pavement_pos_type_ = _pavement_pos_type;
    }

    ::std::uint32_t GetWidthCm() const
    {
        return width_cm_;
    }
    void SetWidthCm(const ::std::uint32_t _width_cm)
    {
        width_cm_ = _width_cm;
    }

    const ::std::vector<IntervalFloat64>* GetPtrExistTimestamp() const
    {
        return &exist_timestamp_;
    }
    void SetExistTimestamp(const ::std::vector<IntervalFloat64>& _exist_timestamp)
    {
        exist_timestamp_ = _exist_timestamp;
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


    void ClearPavementPos()
    {
        pavement_pos_.clear();
    }
    void AddPavementPosElement(const IntervalFloat64& _value)
    {
        pavement_pos_.push_back(_value);
    }
    void UniqueAddPavementPosElements(const ::std::vector<IntervalFloat64>& _value)
    {
        UniqueAppend(pavement_pos_, _value);
    }

    void ClearExistTimestamp()
    {
        exist_timestamp_.clear();
    }
    void AddExistTimestampElement(const IntervalFloat64& _value)
    {
        exist_timestamp_.push_back(_value);
    }
    void UniqueAddExistTimestampElements(const ::std::vector<IntervalFloat64>& _value)
    {
        UniqueAppend(exist_timestamp_, _value);
    }









};  // class PavementCondition

typedef ::std::shared_ptr<PavementCondition> PtrPavementCondition;
typedef const ::std::vector<PavementCondition>* ConstRawPtrVecPavementCondition;
typedef ::std::vector<PavementCondition>* RawPtrVecPavementCondition;
typedef ::std::shared_ptr<PavementCondition const> ConstPtrPavementCondition;
typedef ::std::shared_ptr<::std::vector<PavementCondition> const> ConstPtrVecPavementCondition;
typedef ::std::unordered_map<::std::uint64_t, PtrPavementCondition> HashmapPavementCondition;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_HFL_PAVEMENT_CONDITION_H_