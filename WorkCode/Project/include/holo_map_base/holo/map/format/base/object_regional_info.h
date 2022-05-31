/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file object_regional_info.h
 * @brief Auto generated code for ObjectRegionalInfo format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_BASE_OBJECT_REGIONAL_INFO_H_
#define HOLO_MAP_FORMAT_BASE_OBJECT_REGIONAL_INFO_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/base/object_regional_info.pb.h>

#include <holo/map/proto/common/coordinate.pb.h>

#include <holo/map/proto/common/geo_box4.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/coordinate.h>

#include <holo/map/format/common/geo_box4.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  ObjectRegionalInfo: public Base
{
public:

        
    enum ObjectType
    {
        OBJECT_TYPE_UNDEFINED=  0,  
        OBJECT_TYPE_MARKING=  1,  
    };

        
    enum ObjectContent
    {
        OBJECT_CONTENT_UNDEFINED=  0,  
        OBJECT_CONTENT_ARROW=  1,  
        OBJECT_CONTENT_STRIPE=  2,  
        OBJECT_CONTENT_CHARACTERS=  3,  
        OBJECT_CONTENT_OTHERS=  4,  
    };

        
    enum ObjectArrowType
    {
        OBJECT_ARROW_TYPE_UNDEFINED=  0,  
        OBJECT_ARROW_TYPE_STRAIGHT=  1,  
        OBJECT_ARROW_TYPE_STRAIGHT_LEFT=  2,  
        OBJECT_ARROW_TYPE_STRAIGHT_RIGHT=  3,  
        OBJECT_ARROW_TYPE_LEFT=  4,  
        OBJECT_ARROW_TYPE_RIGHT=  5,  
        OBJECT_ARROW_TYPE_LEFT_RIGHT=  6,  
        OBJECT_ARROW_TYPE_STRAIGHT_LEFT_RIGHT=  7,  
        OBJECT_ARROW_TYPE_U_TURN=  8,  
        OBJECT_ARROW_TYPE_U_TURN_LEFT=  9,  
        OBJECT_ARROW_TYPE_U_TURN_RIGHT=  10,  
        OBJECT_ARROW_TYPE_U_TURN_STRAIGHT=  11,  
        OBJECT_ARROW_TYPE_U_TURN_STRAIGHT_LEFT=  12,  
        OBJECT_ARROW_TYPE_U_TURN_STRAIGHT_RIGHT=  13,  
    };

    static const ::std::map<::std::string, ObjectType>& ENUMSTR_OBJECTTYPE() 
    { 
        static const ::std::map<::std::string, ObjectType> data{
        { "UNDEFINED", ObjectType::OBJECT_TYPE_UNDEFINED },
        { "MARKING", ObjectType::OBJECT_TYPE_MARKING }};
        return data;
    }

    static const ::std::map<::std::string, ObjectContent>& ENUMSTR_OBJECTCONTENT() 
    { 
        static const ::std::map<::std::string, ObjectContent> data{
        { "UNDEFINED", ObjectContent::OBJECT_CONTENT_UNDEFINED },
        { "ARROW", ObjectContent::OBJECT_CONTENT_ARROW },
        { "STRIPE", ObjectContent::OBJECT_CONTENT_STRIPE },
        { "CHARACTERS", ObjectContent::OBJECT_CONTENT_CHARACTERS },
        { "OTHERS", ObjectContent::OBJECT_CONTENT_OTHERS }};
        return data;
    }

    static const ::std::map<::std::string, ObjectArrowType>& ENUMSTR_OBJECTARROWTYPE() 
    { 
        static const ::std::map<::std::string, ObjectArrowType> data{
        { "UNDEFINED", ObjectArrowType::OBJECT_ARROW_TYPE_UNDEFINED },
        { "STRAIGHT", ObjectArrowType::OBJECT_ARROW_TYPE_STRAIGHT },
        { "STRAIGHT_LEFT", ObjectArrowType::OBJECT_ARROW_TYPE_STRAIGHT_LEFT },
        { "STRAIGHT_RIGHT", ObjectArrowType::OBJECT_ARROW_TYPE_STRAIGHT_RIGHT },
        { "LEFT", ObjectArrowType::OBJECT_ARROW_TYPE_LEFT },
        { "RIGHT", ObjectArrowType::OBJECT_ARROW_TYPE_RIGHT },
        { "LEFT_RIGHT", ObjectArrowType::OBJECT_ARROW_TYPE_LEFT_RIGHT },
        { "STRAIGHT_LEFT_RIGHT", ObjectArrowType::OBJECT_ARROW_TYPE_STRAIGHT_LEFT_RIGHT },
        { "U_TURN", ObjectArrowType::OBJECT_ARROW_TYPE_U_TURN },
        { "U_TURN_LEFT", ObjectArrowType::OBJECT_ARROW_TYPE_U_TURN_LEFT },
        { "U_TURN_RIGHT", ObjectArrowType::OBJECT_ARROW_TYPE_U_TURN_RIGHT },
        { "U_TURN_STRAIGHT", ObjectArrowType::OBJECT_ARROW_TYPE_U_TURN_STRAIGHT },
        { "U_TURN_STRAIGHT_LEFT", ObjectArrowType::OBJECT_ARROW_TYPE_U_TURN_STRAIGHT_LEFT },
        { "U_TURN_STRAIGHT_RIGHT", ObjectArrowType::OBJECT_ARROW_TYPE_U_TURN_STRAIGHT_RIGHT }};
        return data;
    }


private:
    ::std::uint64_t object_regional_info_id_; 
    ObjectType object_type_; 
    ObjectContent object_content_; 
    ObjectArrowType object_arrow_type_; 
    ::std::string object_characters_data_; 
    ::std::vector<::std::uint64_t> tile_ids_; 
    ::std::vector<::std::uint64_t> associated_lane_ids_; 
    ::std::vector<::std::uint64_t> associated_lane_group_ids_; 
    ::std::uint32_t zone_id_; 
    ::std::uint32_t extra_zone_id_; 
    bool south_flag_; 
    GeoBox4 geometry_; 
    ::std::map<::std::uint32_t, GeoBox4> extra_geometry_; 
    Coordinate coordinate_; 

private:
    void DecodeProto(const ::holo::map::proto::base::ObjectRegionalInfo& _proto_handler);
    ::holo::map::proto::base::ObjectRegionalInfo EncodeProto();

public:
    ObjectRegionalInfo();
    explicit ObjectRegionalInfo(const ::holo::map::proto::base::ObjectRegionalInfo& _proto_handler);
    // init all format data
    ObjectRegionalInfo(const ::std::uint64_t _object_regional_info_id,const ObjectType& _object_type,const ObjectContent& _object_content,const ObjectArrowType& _object_arrow_type,const ::std::string& _object_characters_data,const ::std::vector<::std::uint64_t>& _tile_ids,const ::std::vector<::std::uint64_t>& _associated_lane_ids,const ::std::vector<::std::uint64_t>& _associated_lane_group_ids,const ::std::uint32_t _zone_id,const ::std::uint32_t _extra_zone_id,const bool _south_flag,const GeoBox4& _geometry,const ::std::map<::std::uint32_t, GeoBox4>& _extra_geometry,const Coordinate& _coordinate);
    ~ObjectRegionalInfo();

    bool operator==(const ::holo::map::format::ObjectRegionalInfo& _other) const;
    ObjectRegionalInfo& operator=(const ::holo::map::proto::base::ObjectRegionalInfo& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::base::ObjectRegionalInfo GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetObjectRegionalInfoId() const
    {
        return object_regional_info_id_;
    }
    void SetObjectRegionalInfoId(const ::std::uint64_t _object_regional_info_id)
    {
        object_regional_info_id_ = _object_regional_info_id;
    }

    const ObjectType& GetObjectType() const
    {
        return object_type_;
    }
    void SetObjectType(const ObjectType& _object_type)
    {
        object_type_ = _object_type;
    }

    const ObjectContent& GetObjectContent() const
    {
        return object_content_;
    }
    void SetObjectContent(const ObjectContent& _object_content)
    {
        object_content_ = _object_content;
    }

    const ObjectArrowType& GetObjectArrowType() const
    {
        return object_arrow_type_;
    }
    void SetObjectArrowType(const ObjectArrowType& _object_arrow_type)
    {
        object_arrow_type_ = _object_arrow_type;
    }

    const ::std::string& GetObjectCharactersData() const
    {
        return object_characters_data_;
    }
    void SetObjectCharactersData(const ::std::string& _object_characters_data)
    {
        object_characters_data_ = _object_characters_data;
    }

    const ::std::vector<::std::uint64_t>* GetPtrTileIds() const
    {
        return &tile_ids_;
    }
    void SetTileIds(const ::std::vector<::std::uint64_t>& _tile_ids)
    {
        tile_ids_ = _tile_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrAssociatedLaneIds() const
    {
        return &associated_lane_ids_;
    }
    void SetAssociatedLaneIds(const ::std::vector<::std::uint64_t>& _associated_lane_ids)
    {
        associated_lane_ids_ = _associated_lane_ids;
    }

    const ::std::vector<::std::uint64_t>* GetPtrAssociatedLaneGroupIds() const
    {
        return &associated_lane_group_ids_;
    }
    void SetAssociatedLaneGroupIds(const ::std::vector<::std::uint64_t>& _associated_lane_group_ids)
    {
        associated_lane_group_ids_ = _associated_lane_group_ids;
    }

    ::std::uint32_t GetZoneId() const
    {
        return zone_id_;
    }
    void SetZoneId(const ::std::uint32_t _zone_id)
    {
        zone_id_ = _zone_id;
    }

    ::std::uint32_t GetExtraZoneId() const
    {
        return extra_zone_id_;
    }
    void SetExtraZoneId(const ::std::uint32_t _extra_zone_id)
    {
        extra_zone_id_ = _extra_zone_id;
    }

    bool GetSouthFlag() const
    {
        return south_flag_;
    }
    void SetSouthFlag(const bool _south_flag)
    {
        south_flag_ = _south_flag;
    }

    const ::std::map<::std::uint32_t, GeoBox4>* GetPtrExtraGeometry() const
    {
        return &extra_geometry_;
    }
    void SetExtraGeometry(const ::std::map<::std::uint32_t, GeoBox4>& _extra_geometry)
    {
        extra_geometry_ = _extra_geometry;
    }

    const Coordinate& GetCoordinate() const
    {
        return coordinate_;
    }
    void SetCoordinate(const Coordinate& _coordinate)
    {
        coordinate_ = _coordinate;
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

    void ClearAssociatedLaneIds()
    {
        associated_lane_ids_.clear();
    }
    void AddAssociatedLaneIdsElement(const ::std::uint64_t& _value)
    {
        associated_lane_ids_.push_back(_value);
    }
    void UniqueAddAssociatedLaneIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(associated_lane_ids_, _value);
    }

    void ClearAssociatedLaneGroupIds()
    {
        associated_lane_group_ids_.clear();
    }
    void AddAssociatedLaneGroupIdsElement(const ::std::uint64_t& _value)
    {
        associated_lane_group_ids_.push_back(_value);
    }
    void UniqueAddAssociatedLaneGroupIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(associated_lane_group_ids_, _value);
    }


    const GeoBox4& GetGeometry() const;
    void SetGeometry(const GeoBox4& _geometry)
    {
        this->geometry_ = _geometry;
    }







};  // class ObjectRegionalInfo

typedef ::std::shared_ptr<ObjectRegionalInfo> PtrObjectRegionalInfo;
typedef const ::std::vector<ObjectRegionalInfo>* ConstRawPtrVecObjectRegionalInfo;
typedef ::std::vector<ObjectRegionalInfo>* RawPtrVecObjectRegionalInfo;
typedef ::std::shared_ptr<ObjectRegionalInfo const> ConstPtrObjectRegionalInfo;
typedef ::std::shared_ptr<::std::vector<ObjectRegionalInfo> const> ConstPtrVecObjectRegionalInfo;
typedef ::std::unordered_map<::std::uint64_t, PtrObjectRegionalInfo> HashmapObjectRegionalInfo;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_OBJECT_REGIONAL_INFO_H_