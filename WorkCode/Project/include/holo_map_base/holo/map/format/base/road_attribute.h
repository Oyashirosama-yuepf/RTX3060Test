/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file road_attribute.h
 * @brief Auto generated code for RoadAttribute format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_BASE_ROAD_ATTRIBUTE_H_
#define HOLO_MAP_FORMAT_BASE_ROAD_ATTRIBUTE_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/base/road_attribute.pb.h>


#include <holo/map/format/base/base.h>


#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  RoadAttribute: public Base
{
public:

        
    enum TollDir
    {
        TOLL_DIR_UNDEFINED=  0,  
        TOLL_DIR_POSITIVE_DIRECTION=  1,  
        TOLL_DIR_NEGATIVE_DIRECTION=  2,  
        TOLL_DIR_BI_DIRECTION=  3,  
        TOLL_DIR_NON_TOOL_BOOTH=  4,  
    };

    static const ::std::map<::std::string, TollDir>& ENUMSTR_TOLLDIR() 
    { 
        static const ::std::map<::std::string, TollDir> data{
        { "UNDEFINED", TollDir::TOLL_DIR_UNDEFINED },
        { "POSITIVE_DIRECTION", TollDir::TOLL_DIR_POSITIVE_DIRECTION },
        { "NEGATIVE_DIRECTION", TollDir::TOLL_DIR_NEGATIVE_DIRECTION },
        { "BI_DIRECTION", TollDir::TOLL_DIR_BI_DIRECTION },
        { "NON_TOOL_BOOTH", TollDir::TOLL_DIR_NON_TOOL_BOOTH }};
        return data;
    }


private:
    ::std::uint64_t start_pos_; 
    ::std::uint64_t end_pos_; 
    bool bridge_flag_; 
    bool tunnel_flag_; 
    bool urban_flag_; 
    bool motorway_flag_; 
    bool servicearea_flag_; 
    bool ferry_flag_; 
    ::std::uint64_t road_id_; 
    TollDir toll_dir_; 
    bool controlled_access_flag_; 
    bool complex_intersection_flag_; 
    ::std::uint32_t high_limit_cm_; 

private:
    void DecodeProto(const ::holo::map::proto::base::RoadAttribute& _proto_handler);
    ::holo::map::proto::base::RoadAttribute EncodeProto();

public:
    RoadAttribute();
    explicit RoadAttribute(const ::holo::map::proto::base::RoadAttribute& _proto_handler);
    // init all format data
    RoadAttribute(const ::std::uint64_t _start_pos,const ::std::uint64_t _end_pos,const bool _bridge_flag,const bool _tunnel_flag,const bool _urban_flag,const bool _motorway_flag,const bool _servicearea_flag,const bool _ferry_flag,const ::std::uint64_t _road_id,const TollDir& _toll_dir,const bool _controlled_access_flag,const bool _complex_intersection_flag,const ::std::uint32_t _high_limit_cm);
    ~RoadAttribute();

    bool operator==(const ::holo::map::format::RoadAttribute& _other) const;
    RoadAttribute& operator=(const ::holo::map::proto::base::RoadAttribute& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::base::RoadAttribute GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetStartPos() const
    {
        return start_pos_;
    }
    void SetStartPos(const ::std::uint64_t _start_pos)
    {
        start_pos_ = _start_pos;
    }

    ::std::uint64_t GetEndPos() const
    {
        return end_pos_;
    }
    void SetEndPos(const ::std::uint64_t _end_pos)
    {
        end_pos_ = _end_pos;
    }

    bool GetBridgeFlag() const
    {
        return bridge_flag_;
    }
    void SetBridgeFlag(const bool _bridge_flag)
    {
        bridge_flag_ = _bridge_flag;
    }

    bool GetTunnelFlag() const
    {
        return tunnel_flag_;
    }
    void SetTunnelFlag(const bool _tunnel_flag)
    {
        tunnel_flag_ = _tunnel_flag;
    }

    bool GetUrbanFlag() const
    {
        return urban_flag_;
    }
    void SetUrbanFlag(const bool _urban_flag)
    {
        urban_flag_ = _urban_flag;
    }

    bool GetMotorwayFlag() const
    {
        return motorway_flag_;
    }
    void SetMotorwayFlag(const bool _motorway_flag)
    {
        motorway_flag_ = _motorway_flag;
    }

    bool GetServiceareaFlag() const
    {
        return servicearea_flag_;
    }
    void SetServiceareaFlag(const bool _servicearea_flag)
    {
        servicearea_flag_ = _servicearea_flag;
    }

    bool GetFerryFlag() const
    {
        return ferry_flag_;
    }
    void SetFerryFlag(const bool _ferry_flag)
    {
        ferry_flag_ = _ferry_flag;
    }

    ::std::uint64_t GetRoadId() const
    {
        return road_id_;
    }
    void SetRoadId(const ::std::uint64_t _road_id)
    {
        road_id_ = _road_id;
    }

    const TollDir& GetTollDir() const
    {
        return toll_dir_;
    }
    void SetTollDir(const TollDir& _toll_dir)
    {
        toll_dir_ = _toll_dir;
    }

    bool GetControlledAccessFlag() const
    {
        return controlled_access_flag_;
    }
    void SetControlledAccessFlag(const bool _controlled_access_flag)
    {
        controlled_access_flag_ = _controlled_access_flag;
    }

    bool GetComplexIntersectionFlag() const
    {
        return complex_intersection_flag_;
    }
    void SetComplexIntersectionFlag(const bool _complex_intersection_flag)
    {
        complex_intersection_flag_ = _complex_intersection_flag;
    }

    ::std::uint32_t GetHighLimitCm() const
    {
        return high_limit_cm_;
    }
    void SetHighLimitCm(const ::std::uint32_t _high_limit_cm)
    {
        high_limit_cm_ = _high_limit_cm;
    }











};  // class RoadAttribute

typedef ::std::shared_ptr<RoadAttribute> PtrRoadAttribute;
typedef const ::std::vector<RoadAttribute>* ConstRawPtrVecRoadAttribute;
typedef ::std::vector<RoadAttribute>* RawPtrVecRoadAttribute;
typedef ::std::shared_ptr<RoadAttribute const> ConstPtrRoadAttribute;
typedef ::std::shared_ptr<::std::vector<RoadAttribute> const> ConstPtrVecRoadAttribute;
typedef ::std::unordered_map<::std::uint64_t, PtrRoadAttribute> HashmapRoadAttribute;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_ROAD_ATTRIBUTE_H_