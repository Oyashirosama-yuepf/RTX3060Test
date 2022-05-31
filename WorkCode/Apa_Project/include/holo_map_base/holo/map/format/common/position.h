/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file position.h
 * @brief Auto generated code for Position format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_COMMON_POSITION_H_
#define HOLO_MAP_FORMAT_COMMON_POSITION_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/common/position.pb.h>


#include <holo/map/format/base/base.h>


#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  Position: public Base
{
public:

        
    enum SuperElevation
    {
        SUPER_ELEVATION_UNDEFINED=  0,  
        SUPER_ELEVATION_FLAT=  1,  
        SUPER_ELEVATION_MORE_THAN_4_TOWARDS_CURB=  2,  
        SUPER_ELEVATION_MORE_THAN_6_TOWARDS_CURB=  3,  
        SUPER_ELEVATION_MORE_THAN_8_TOWARDS_CURB=  4,  
        SUPER_ELEVATION_MORE_THAN_4_TOWARDS_MIDDLE=  5,  
        SUPER_ELEVATION_MORE_THAN_6_TOWARDS_MIDDLE=  6,  
        SUPER_ELEVATION_MORE_THAN_8_TOWARDS_MIDDLE=  7,  
    };

    static const ::std::map<::std::string, SuperElevation>& ENUMSTR_SUPERELEVATION() 
    { 
        static const ::std::map<::std::string, SuperElevation> data{
        { "UNDEFINED", SuperElevation::SUPER_ELEVATION_UNDEFINED },
        { "FLAT", SuperElevation::SUPER_ELEVATION_FLAT },
        { "MORE_THAN_4_TOWARDS_CURB", SuperElevation::SUPER_ELEVATION_MORE_THAN_4_TOWARDS_CURB },
        { "MORE_THAN_6_TOWARDS_CURB", SuperElevation::SUPER_ELEVATION_MORE_THAN_6_TOWARDS_CURB },
        { "MORE_THAN_8_TOWARDS_CURB", SuperElevation::SUPER_ELEVATION_MORE_THAN_8_TOWARDS_CURB },
        { "MORE_THAN_4_TOWARDS_MIDDLE", SuperElevation::SUPER_ELEVATION_MORE_THAN_4_TOWARDS_MIDDLE },
        { "MORE_THAN_6_TOWARDS_MIDDLE", SuperElevation::SUPER_ELEVATION_MORE_THAN_6_TOWARDS_MIDDLE },
        { "MORE_THAN_8_TOWARDS_MIDDLE", SuperElevation::SUPER_ELEVATION_MORE_THAN_8_TOWARDS_MIDDLE }};
        return data;
    }


private:
    ::std::uint64_t road_id_; 
    ::std::int64_t height_cm_; 
    ::std::int64_t slope_; 
    ::std::int64_t curvature_; 
    double x_; 
    double y_; 
    SuperElevation super_elevation_; 

private:
    void DecodeProto(const ::holo::map::proto::common::Position& _proto_handler);
    ::holo::map::proto::common::Position EncodeProto();

public:
    Position();
    explicit Position(const ::holo::map::proto::common::Position& _proto_handler);
    // init all format data
    Position(const ::std::uint64_t _road_id,const ::std::int64_t _height_cm,const ::std::int64_t _slope,const ::std::int64_t _curvature,const double _x,const double _y,const SuperElevation& _super_elevation);
    ~Position();

    bool operator==(const ::holo::map::format::Position& _other) const;
    Position& operator=(const ::holo::map::proto::common::Position& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::common::Position GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetRoadId() const
    {
        return road_id_;
    }
    void SetRoadId(const ::std::uint64_t _road_id)
    {
        road_id_ = _road_id;
    }

    ::std::int64_t GetHeightCm() const
    {
        return height_cm_;
    }
    void SetHeightCm(const ::std::int64_t _height_cm)
    {
        height_cm_ = _height_cm;
    }

    ::std::int64_t GetSlope() const
    {
        return slope_;
    }
    void SetSlope(const ::std::int64_t _slope)
    {
        slope_ = _slope;
    }

    ::std::int64_t GetCurvature() const
    {
        return curvature_;
    }
    void SetCurvature(const ::std::int64_t _curvature)
    {
        curvature_ = _curvature;
    }

    double GetX() const
    {
        return x_;
    }
    void SetX(const double _x)
    {
        x_ = _x;
    }

    double GetY() const
    {
        return y_;
    }
    void SetY(const double _y)
    {
        y_ = _y;
    }

    const SuperElevation& GetSuperElevation() const
    {
        return super_elevation_;
    }
    void SetSuperElevation(const SuperElevation& _super_elevation)
    {
        super_elevation_ = _super_elevation;
    }











};  // class Position

typedef ::std::shared_ptr<Position> PtrPosition;
typedef const ::std::vector<Position>* ConstRawPtrVecPosition;
typedef ::std::vector<Position>* RawPtrVecPosition;
typedef ::std::shared_ptr<Position const> ConstPtrPosition;
typedef ::std::shared_ptr<::std::vector<Position> const> ConstPtrVecPosition;
typedef ::std::unordered_map<::std::uint64_t, PtrPosition> HashmapPosition;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_COMMON_POSITION_H_