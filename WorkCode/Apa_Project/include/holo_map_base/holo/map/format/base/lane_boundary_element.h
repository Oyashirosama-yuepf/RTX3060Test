/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_boundary_element.h
 * @brief Auto generated code for LaneBoundaryElement format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_BASE_LANE_BOUNDARY_ELEMENT_H_
#define HOLO_MAP_FORMAT_BASE_LANE_BOUNDARY_ELEMENT_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/base/lane_boundary_element.pb.h>


#include <holo/map/format/base/base.h>


#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  LaneBoundaryElement: public Base
{
public:

        
    enum BoundaryType
    {
        BOUNDARY_TYPE_UNKNOWN=  0,  
        BOUNDARY_TYPE_LONG_DASHED_LINE=  1,  
        BOUNDARY_TYPE_DOUBLE_SOLID_LINE=  2,  
        BOUNDARY_TYPE_SINGLE_SOLID_LINE=  3,  
        BOUNDARY_TYPE_SOLID_LINE_DASHED_LINE=  4,  
        BOUNDARY_TYPE_DASHED_LINE_SOLID_LINE=  5,  
        BOUNDARY_TYPE_SHORT_DASHED_LINE=  6,  
        BOUNDARY_TYPE_SHADED_AREA_MARKING=  7,  
        BOUNDARY_TYPE_DASHED_BLOCKS=  8,  
        BOUNDARY_TYPE_DOUBLE_DASHED_LINE=  9,  
        BOUNDARY_TYPE_CROSSING_ALERT=  10,  
        BOUNDARY_TYPE_CURB=  11,  
        BOUNDARY_TYPE_WALL_FLAT=  12,  
        BOUNDARY_TYPE_WALL_TUNNEL=  13,  
        BOUNDARY_TYPE_BARRIER_JERSEY=  14,  
        BOUNDARY_TYPE_BARRIER_SOUND=  15,  
        BOUNDARY_TYPE_BARRIER_CABLE=  16,  
        BOUNDARY_TYPE_GUARDRAIL=  17,  
        BOUNDARY_TYPE_FENCE=  18,  
        BOUNDARY_TYPE_CURB_TRAVERSABLE=  19,  
        BOUNDARY_TYPE_END_OF_ROAD=  20,  
        BOUNDARY_TYPE_CLIFF=  21,  
        BOUNDARY_TYPE_DITCH=  22,  
        BOUNDARY_TYPE_GORE=  23,  
        BOUNDARY_TYPE_WALKING_AREA=  24,  
        BOUNDARY_TYPE_OFFSET_SPACE=  25,  
        BOUNDARY_TYPE_NORMAL_FISH_BONE_LINE=  26,  
        BOUNDARY_TYPE_SINGLE_DASHED_LINE=  27,  
        BOUNDARY_TYPE_OTHER_BARRIER=  30,  
        BOUNDARY_TYPE_NO_MARKING=  31,  
        BOUNDARY_TYPE_RESERVED_1=  250,  
        BOUNDARY_TYPE_RESERVED_2=  251,  
        BOUNDARY_TYPE_RESERVED_3=  252,  
        BOUNDARY_TYPE_RESERVED_4=  253,  
        BOUNDARY_TYPE_RESERVED_5=  254,  
        BOUNDARY_TYPE_OTHERS=  255,  
    };

        
    enum BoundaryMaterial
    {
        BOUNDARY_MATERIAL_UNKNOWN=  0,  
        BOUNDARY_MATERIAL_METAL=  1,  
        BOUNDARY_MATERIAL_CONCRETE=  2,  
        BOUNDARY_MATERIAL_STONE=  3,  
        BOUNDARY_MATERIAL_WOOD=  4,  
        BOUNDARY_MATERIAL_PLASTIC=  5,  
        BOUNDARY_MATERIAL_TRANSPARENT=  6,  
        BOUNDARY_MATERIAL_VIBRATION_MARKINGS=  7,  
        BOUNDARY_MATERIAL_PAINTED_VIBRATION_DIVIDER=  8,  
        BOUNDARY_MATERIAL_RESERVED_1=  250,  
        BOUNDARY_MATERIAL_RESERVED_2=  251,  
        BOUNDARY_MATERIAL_RESERVED_3=  252,  
        BOUNDARY_MATERIAL_RESERVED_4=  253,  
        BOUNDARY_MATERIAL_RESERVED_5=  254,  
        BOUNDARY_MATERIAL_OTHERS=  255,  
    };

        
    enum BoundaryColor
    {
        BOUNDARY_COLOR_UNKNOWN=  0,  
        BOUNDARY_COLOR_LIGHT_GRAY=  1,  
        BOUNDARY_COLOR_GRAY=  2,  
        BOUNDARY_COLOR_DARK_GRAY=  3,  
        BOUNDARY_COLOR_BLACK=  4,  
        BOUNDARY_COLOR_RED=  5,  
        BOUNDARY_COLOR_YELLOW=  6,  
        BOUNDARY_COLOR_GREEN=  7,  
        BOUNDARY_COLOR_CYAN=  8,  
        BOUNDARY_COLOR_BLUE=  9,  
        BOUNDARY_COLOR_ORANGE=  10,  
        BOUNDARY_COLOR_WHITE=  11,  
        BOUNDARY_COLOR_RESERVED_1=  250,  
        BOUNDARY_COLOR_RESERVED_2=  251,  
        BOUNDARY_COLOR_RESERVED_3=  252,  
        BOUNDARY_COLOR_RESERVED_4=  253,  
        BOUNDARY_COLOR_RESERVED_5=  254,  
        BOUNDARY_COLOR_OTHERS=  255,  
    };

    static const ::std::map<::std::string, BoundaryType>& ENUMSTR_BOUNDARYTYPE() 
    { 
        static const ::std::map<::std::string, BoundaryType> data{
        { "UNKNOWN", BoundaryType::BOUNDARY_TYPE_UNKNOWN },
        { "LONG_DASHED_LINE", BoundaryType::BOUNDARY_TYPE_LONG_DASHED_LINE },
        { "DOUBLE_SOLID_LINE", BoundaryType::BOUNDARY_TYPE_DOUBLE_SOLID_LINE },
        { "SINGLE_SOLID_LINE", BoundaryType::BOUNDARY_TYPE_SINGLE_SOLID_LINE },
        { "SOLID_LINE_DASHED_LINE", BoundaryType::BOUNDARY_TYPE_SOLID_LINE_DASHED_LINE },
        { "DASHED_LINE_SOLID_LINE", BoundaryType::BOUNDARY_TYPE_DASHED_LINE_SOLID_LINE },
        { "SHORT_DASHED_LINE", BoundaryType::BOUNDARY_TYPE_SHORT_DASHED_LINE },
        { "SHADED_AREA_MARKING", BoundaryType::BOUNDARY_TYPE_SHADED_AREA_MARKING },
        { "DASHED_BLOCKS", BoundaryType::BOUNDARY_TYPE_DASHED_BLOCKS },
        { "DOUBLE_DASHED_LINE", BoundaryType::BOUNDARY_TYPE_DOUBLE_DASHED_LINE },
        { "CROSSING_ALERT", BoundaryType::BOUNDARY_TYPE_CROSSING_ALERT },
        { "CURB", BoundaryType::BOUNDARY_TYPE_CURB },
        { "WALL_FLAT", BoundaryType::BOUNDARY_TYPE_WALL_FLAT },
        { "WALL_TUNNEL", BoundaryType::BOUNDARY_TYPE_WALL_TUNNEL },
        { "BARRIER_JERSEY", BoundaryType::BOUNDARY_TYPE_BARRIER_JERSEY },
        { "BARRIER_SOUND", BoundaryType::BOUNDARY_TYPE_BARRIER_SOUND },
        { "BARRIER_CABLE", BoundaryType::BOUNDARY_TYPE_BARRIER_CABLE },
        { "GUARDRAIL", BoundaryType::BOUNDARY_TYPE_GUARDRAIL },
        { "FENCE", BoundaryType::BOUNDARY_TYPE_FENCE },
        { "CURB_TRAVERSABLE", BoundaryType::BOUNDARY_TYPE_CURB_TRAVERSABLE },
        { "END_OF_ROAD", BoundaryType::BOUNDARY_TYPE_END_OF_ROAD },
        { "CLIFF", BoundaryType::BOUNDARY_TYPE_CLIFF },
        { "DITCH", BoundaryType::BOUNDARY_TYPE_DITCH },
        { "GORE", BoundaryType::BOUNDARY_TYPE_GORE },
        { "WALKING_AREA", BoundaryType::BOUNDARY_TYPE_WALKING_AREA },
        { "OFFSET_SPACE", BoundaryType::BOUNDARY_TYPE_OFFSET_SPACE },
        { "NORMAL_FISH_BONE_LINE", BoundaryType::BOUNDARY_TYPE_NORMAL_FISH_BONE_LINE },
        { "SINGLE_DASHED_LINE", BoundaryType::BOUNDARY_TYPE_SINGLE_DASHED_LINE },
        { "OTHER_BARRIER", BoundaryType::BOUNDARY_TYPE_OTHER_BARRIER },
        { "NO_MARKING", BoundaryType::BOUNDARY_TYPE_NO_MARKING },
        { "RESERVED_1", BoundaryType::BOUNDARY_TYPE_RESERVED_1 },
        { "RESERVED_2", BoundaryType::BOUNDARY_TYPE_RESERVED_2 },
        { "RESERVED_3", BoundaryType::BOUNDARY_TYPE_RESERVED_3 },
        { "RESERVED_4", BoundaryType::BOUNDARY_TYPE_RESERVED_4 },
        { "RESERVED_5", BoundaryType::BOUNDARY_TYPE_RESERVED_5 },
        { "OTHERS", BoundaryType::BOUNDARY_TYPE_OTHERS }};
        return data;
    }

    static const ::std::map<::std::string, BoundaryMaterial>& ENUMSTR_BOUNDARYMATERIAL() 
    { 
        static const ::std::map<::std::string, BoundaryMaterial> data{
        { "UNKNOWN", BoundaryMaterial::BOUNDARY_MATERIAL_UNKNOWN },
        { "METAL", BoundaryMaterial::BOUNDARY_MATERIAL_METAL },
        { "CONCRETE", BoundaryMaterial::BOUNDARY_MATERIAL_CONCRETE },
        { "STONE", BoundaryMaterial::BOUNDARY_MATERIAL_STONE },
        { "WOOD", BoundaryMaterial::BOUNDARY_MATERIAL_WOOD },
        { "PLASTIC", BoundaryMaterial::BOUNDARY_MATERIAL_PLASTIC },
        { "TRANSPARENT", BoundaryMaterial::BOUNDARY_MATERIAL_TRANSPARENT },
        { "VIBRATION_MARKINGS", BoundaryMaterial::BOUNDARY_MATERIAL_VIBRATION_MARKINGS },
        { "PAINTED_VIBRATION_DIVIDER", BoundaryMaterial::BOUNDARY_MATERIAL_PAINTED_VIBRATION_DIVIDER },
        { "RESERVED_1", BoundaryMaterial::BOUNDARY_MATERIAL_RESERVED_1 },
        { "RESERVED_2", BoundaryMaterial::BOUNDARY_MATERIAL_RESERVED_2 },
        { "RESERVED_3", BoundaryMaterial::BOUNDARY_MATERIAL_RESERVED_3 },
        { "RESERVED_4", BoundaryMaterial::BOUNDARY_MATERIAL_RESERVED_4 },
        { "RESERVED_5", BoundaryMaterial::BOUNDARY_MATERIAL_RESERVED_5 },
        { "OTHERS", BoundaryMaterial::BOUNDARY_MATERIAL_OTHERS }};
        return data;
    }

    static const ::std::map<::std::string, BoundaryColor>& ENUMSTR_BOUNDARYCOLOR() 
    { 
        static const ::std::map<::std::string, BoundaryColor> data{
        { "UNKNOWN", BoundaryColor::BOUNDARY_COLOR_UNKNOWN },
        { "LIGHT_GRAY", BoundaryColor::BOUNDARY_COLOR_LIGHT_GRAY },
        { "GRAY", BoundaryColor::BOUNDARY_COLOR_GRAY },
        { "DARK_GRAY", BoundaryColor::BOUNDARY_COLOR_DARK_GRAY },
        { "BLACK", BoundaryColor::BOUNDARY_COLOR_BLACK },
        { "RED", BoundaryColor::BOUNDARY_COLOR_RED },
        { "YELLOW", BoundaryColor::BOUNDARY_COLOR_YELLOW },
        { "GREEN", BoundaryColor::BOUNDARY_COLOR_GREEN },
        { "CYAN", BoundaryColor::BOUNDARY_COLOR_CYAN },
        { "BLUE", BoundaryColor::BOUNDARY_COLOR_BLUE },
        { "ORANGE", BoundaryColor::BOUNDARY_COLOR_ORANGE },
        { "WHITE", BoundaryColor::BOUNDARY_COLOR_WHITE },
        { "RESERVED_1", BoundaryColor::BOUNDARY_COLOR_RESERVED_1 },
        { "RESERVED_2", BoundaryColor::BOUNDARY_COLOR_RESERVED_2 },
        { "RESERVED_3", BoundaryColor::BOUNDARY_COLOR_RESERVED_3 },
        { "RESERVED_4", BoundaryColor::BOUNDARY_COLOR_RESERVED_4 },
        { "RESERVED_5", BoundaryColor::BOUNDARY_COLOR_RESERVED_5 },
        { "OTHERS", BoundaryColor::BOUNDARY_COLOR_OTHERS }};
        return data;
    }


private:
    double start_pos_; 
    double end_pos_; 
    BoundaryType boundary_type_; 
    BoundaryMaterial boundary_material_; 
    BoundaryColor boundary_color_; 
    ::std::uint32_t width_cm_; 
    bool is_open_to_curb_side_; 
    bool is_open_to_middle_side_; 
    ::std::uint64_t lane_boundary_id_; 
    ::std::uint32_t boundary_info_index_; 
    ::std::uint32_t boundary_vertical_offset_cm_; 
    ::std::uint32_t length_cm_; 

private:
    void DecodeProto(const ::holo::map::proto::base::LaneBoundaryElement& _proto_handler);
    ::holo::map::proto::base::LaneBoundaryElement EncodeProto();

public:
    LaneBoundaryElement();
    explicit LaneBoundaryElement(const ::holo::map::proto::base::LaneBoundaryElement& _proto_handler);
    // init all format data
    LaneBoundaryElement(const double _start_pos,const double _end_pos,const BoundaryType& _boundary_type,const BoundaryMaterial& _boundary_material,const BoundaryColor& _boundary_color,const ::std::uint32_t _width_cm,const bool _is_open_to_curb_side,const bool _is_open_to_middle_side,const ::std::uint64_t _lane_boundary_id,const ::std::uint32_t _boundary_info_index,const ::std::uint32_t _boundary_vertical_offset_cm,const ::std::uint32_t _length_cm);
    ~LaneBoundaryElement();

    bool operator==(const ::holo::map::format::LaneBoundaryElement& _other) const;
    LaneBoundaryElement& operator=(const ::holo::map::proto::base::LaneBoundaryElement& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::base::LaneBoundaryElement GetProtoHandler()
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

    const BoundaryType& GetBoundaryType() const
    {
        return boundary_type_;
    }
    void SetBoundaryType(const BoundaryType& _boundary_type)
    {
        boundary_type_ = _boundary_type;
    }

    const BoundaryMaterial& GetBoundaryMaterial() const
    {
        return boundary_material_;
    }
    void SetBoundaryMaterial(const BoundaryMaterial& _boundary_material)
    {
        boundary_material_ = _boundary_material;
    }

    const BoundaryColor& GetBoundaryColor() const
    {
        return boundary_color_;
    }
    void SetBoundaryColor(const BoundaryColor& _boundary_color)
    {
        boundary_color_ = _boundary_color;
    }

    ::std::uint32_t GetWidthCm() const
    {
        return width_cm_;
    }
    void SetWidthCm(const ::std::uint32_t _width_cm)
    {
        width_cm_ = _width_cm;
    }

    bool GetIsOpenToCurbSide() const
    {
        return is_open_to_curb_side_;
    }
    void SetIsOpenToCurbSide(const bool _is_open_to_curb_side)
    {
        is_open_to_curb_side_ = _is_open_to_curb_side;
    }

    bool GetIsOpenToMiddleSide() const
    {
        return is_open_to_middle_side_;
    }
    void SetIsOpenToMiddleSide(const bool _is_open_to_middle_side)
    {
        is_open_to_middle_side_ = _is_open_to_middle_side;
    }

    ::std::uint64_t GetLaneBoundaryId() const
    {
        return lane_boundary_id_;
    }
    void SetLaneBoundaryId(const ::std::uint64_t _lane_boundary_id)
    {
        lane_boundary_id_ = _lane_boundary_id;
    }

    ::std::uint32_t GetBoundaryInfoIndex() const
    {
        return boundary_info_index_;
    }
    void SetBoundaryInfoIndex(const ::std::uint32_t _boundary_info_index)
    {
        boundary_info_index_ = _boundary_info_index;
    }

    ::std::uint32_t GetBoundaryVerticalOffsetCm() const
    {
        return boundary_vertical_offset_cm_;
    }
    void SetBoundaryVerticalOffsetCm(const ::std::uint32_t _boundary_vertical_offset_cm)
    {
        boundary_vertical_offset_cm_ = _boundary_vertical_offset_cm;
    }

    ::std::uint32_t GetLengthCm() const
    {
        return length_cm_;
    }
    void SetLengthCm(const ::std::uint32_t _length_cm)
    {
        length_cm_ = _length_cm;
    }











};  // class LaneBoundaryElement

typedef ::std::shared_ptr<LaneBoundaryElement> PtrLaneBoundaryElement;
typedef const ::std::vector<LaneBoundaryElement>* ConstRawPtrVecLaneBoundaryElement;
typedef ::std::vector<LaneBoundaryElement>* RawPtrVecLaneBoundaryElement;
typedef ::std::shared_ptr<LaneBoundaryElement const> ConstPtrLaneBoundaryElement;
typedef ::std::shared_ptr<::std::vector<LaneBoundaryElement> const> ConstPtrVecLaneBoundaryElement;
typedef ::std::unordered_map<::std::uint64_t, PtrLaneBoundaryElement> HashmapLaneBoundaryElement;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_LANE_BOUNDARY_ELEMENT_H_