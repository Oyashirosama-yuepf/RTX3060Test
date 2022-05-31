/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file geo_collection.h
 * @brief Auto generated code for GeoCollection format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_COMMON_GEO_COLLECTION_H_
#define HOLO_MAP_FORMAT_COMMON_GEO_COLLECTION_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/common/geo_collection.pb.h>

#include <holo/map/proto/common/geo_point.pb.h>

#include <holo/map/proto/common/geo_line.pb.h>

#include <holo/map/proto/common/geo_polygon.pb.h>

#include <holo/map/proto/common/geo_box.pb.h>

#include <holo/map/proto/common/geo_circle.pb.h>

#include <holo/map/proto/common/geo_multi_point.pb.h>

#include <holo/map/proto/common/geo_multi_line.pb.h>

#include <holo/map/proto/common/geo_multi_polygon.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/geo_point.h>

#include <holo/map/format/common/geo_line.h>

#include <holo/map/format/common/geo_polygon.h>

#include <holo/map/format/common/geo_box.h>

#include <holo/map/format/common/geo_circle.h>

#include <holo/map/format/common/geo_multi_point.h>

#include <holo/map/format/common/geo_multi_line.h>

#include <holo/map/format/common/geo_multi_polygon.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  GeoCollection: public Base
{
public:




private:
    ::std::vector<GeoPoint> points_; 
    ::std::vector<GeoLine> lines_; 
    ::std::vector<GeoPolygon> polygons_; 
    ::std::vector<GeoBox> boxes_; 
    ::std::vector<GeoCircle> circles_; 
    ::std::vector<GeoMultiPoint> multi_points_; 
    ::std::vector<GeoMultiLine> multi_lines_; 
    ::std::vector<GeoMultiPolygon> multi_polygons_; 

private:
    void DecodeProto(const ::holo::map::proto::common::GeoCollection& _proto_handler);
    ::holo::map::proto::common::GeoCollection EncodeProto();

public:
    GeoCollection();
    explicit GeoCollection(const ::holo::map::proto::common::GeoCollection& _proto_handler);
    // init all format data
    GeoCollection(const ::std::vector<GeoPoint>& _points,const ::std::vector<GeoLine>& _lines,const ::std::vector<GeoPolygon>& _polygons,const ::std::vector<GeoBox>& _boxes,const ::std::vector<GeoCircle>& _circles,const ::std::vector<GeoMultiPoint>& _multi_points,const ::std::vector<GeoMultiLine>& _multi_lines,const ::std::vector<GeoMultiPolygon>& _multi_polygons);
    ~GeoCollection();

    bool operator==(const ::holo::map::format::GeoCollection& _other) const;
    GeoCollection& operator=(const ::holo::map::proto::common::GeoCollection& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::common::GeoCollection GetProtoHandler()
    {
        return EncodeProto();
    }

    


    const ::std::vector<GeoPoint>* GetPtrPoints() const
    {
        return &points_;
    }
    void SetPoints(const ::std::vector<GeoPoint>& _points)
    {
        points_ = _points;
    }

    const ::std::vector<GeoLine>* GetPtrLines() const
    {
        return &lines_;
    }
    void SetLines(const ::std::vector<GeoLine>& _lines)
    {
        lines_ = _lines;
    }

    const ::std::vector<GeoPolygon>* GetPtrPolygons() const
    {
        return &polygons_;
    }
    void SetPolygons(const ::std::vector<GeoPolygon>& _polygons)
    {
        polygons_ = _polygons;
    }

    const ::std::vector<GeoBox>* GetPtrBoxes() const
    {
        return &boxes_;
    }
    void SetBoxes(const ::std::vector<GeoBox>& _boxes)
    {
        boxes_ = _boxes;
    }

    const ::std::vector<GeoCircle>* GetPtrCircles() const
    {
        return &circles_;
    }
    void SetCircles(const ::std::vector<GeoCircle>& _circles)
    {
        circles_ = _circles;
    }

    const ::std::vector<GeoMultiPoint>* GetPtrMultiPoints() const
    {
        return &multi_points_;
    }
    void SetMultiPoints(const ::std::vector<GeoMultiPoint>& _multi_points)
    {
        multi_points_ = _multi_points;
    }

    const ::std::vector<GeoMultiLine>* GetPtrMultiLines() const
    {
        return &multi_lines_;
    }
    void SetMultiLines(const ::std::vector<GeoMultiLine>& _multi_lines)
    {
        multi_lines_ = _multi_lines;
    }

    const ::std::vector<GeoMultiPolygon>* GetPtrMultiPolygons() const
    {
        return &multi_polygons_;
    }
    void SetMultiPolygons(const ::std::vector<GeoMultiPolygon>& _multi_polygons)
    {
        multi_polygons_ = _multi_polygons;
    }


    void ClearPoints()
    {
        points_.clear();
    }
    void AddPointsElement(const GeoPoint& _value)
    {
        points_.push_back(_value);
    }
    void UniqueAddPointsElements(const ::std::vector<GeoPoint>& _value)
    {
        UniqueAppend(points_, _value);
    }

    void ClearLines()
    {
        lines_.clear();
    }
    void AddLinesElement(const GeoLine& _value)
    {
        lines_.push_back(_value);
    }
    void UniqueAddLinesElements(const ::std::vector<GeoLine>& _value)
    {
        UniqueAppend(lines_, _value);
    }

    void ClearPolygons()
    {
        polygons_.clear();
    }
    void AddPolygonsElement(const GeoPolygon& _value)
    {
        polygons_.push_back(_value);
    }
    void UniqueAddPolygonsElements(const ::std::vector<GeoPolygon>& _value)
    {
        UniqueAppend(polygons_, _value);
    }

    void ClearBoxes()
    {
        boxes_.clear();
    }
    void AddBoxesElement(const GeoBox& _value)
    {
        boxes_.push_back(_value);
    }
    void UniqueAddBoxesElements(const ::std::vector<GeoBox>& _value)
    {
        UniqueAppend(boxes_, _value);
    }

    void ClearCircles()
    {
        circles_.clear();
    }
    void AddCirclesElement(const GeoCircle& _value)
    {
        circles_.push_back(_value);
    }
    void UniqueAddCirclesElements(const ::std::vector<GeoCircle>& _value)
    {
        UniqueAppend(circles_, _value);
    }

    void ClearMultiPoints()
    {
        multi_points_.clear();
    }
    void AddMultiPointsElement(const GeoMultiPoint& _value)
    {
        multi_points_.push_back(_value);
    }
    void UniqueAddMultiPointsElements(const ::std::vector<GeoMultiPoint>& _value)
    {
        UniqueAppend(multi_points_, _value);
    }

    void ClearMultiLines()
    {
        multi_lines_.clear();
    }
    void AddMultiLinesElement(const GeoMultiLine& _value)
    {
        multi_lines_.push_back(_value);
    }
    void UniqueAddMultiLinesElements(const ::std::vector<GeoMultiLine>& _value)
    {
        UniqueAppend(multi_lines_, _value);
    }

    void ClearMultiPolygons()
    {
        multi_polygons_.clear();
    }
    void AddMultiPolygonsElement(const GeoMultiPolygon& _value)
    {
        multi_polygons_.push_back(_value);
    }
    void UniqueAddMultiPolygonsElements(const ::std::vector<GeoMultiPolygon>& _value)
    {
        UniqueAppend(multi_polygons_, _value);
    }









};  // class GeoCollection

typedef ::std::shared_ptr<GeoCollection> PtrGeoCollection;
typedef const ::std::vector<GeoCollection>* ConstRawPtrVecGeoCollection;
typedef ::std::vector<GeoCollection>* RawPtrVecGeoCollection;
typedef ::std::shared_ptr<GeoCollection const> ConstPtrGeoCollection;
typedef ::std::shared_ptr<::std::vector<GeoCollection> const> ConstPtrVecGeoCollection;
typedef ::std::unordered_map<::std::uint64_t, PtrGeoCollection> HashmapGeoCollection;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_COMMON_GEO_COLLECTION_H_