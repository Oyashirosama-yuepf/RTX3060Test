/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file geometry.hpp
 * @brief geometry.hpp
 * @author wanghaiyang@holomatic.com
 * @date "2020-10-08"
 */

#ifndef HOLO_MAP_SERVICE_CLIENT_COMMON_GEOMETRY_HPP_
#define HOLO_MAP_SERVICE_CLIENT_COMMON_GEOMETRY_HPP_

#include <string>

#include <holo/map/service/client/common/geometry.h>

namespace holo
{
namespace map
{
namespace service
{
namespace client
{
namespace geometry
{

template <typename C, typename T, typename I>
static T& GetDataFromContainer(C& container, I const i)
{
    if (i >= container.size())
    {
        throw std::out_of_range(std::to_string(i));
    }

    return container[i];
}

template <typename C, typename T, typename I>
static T const& GetDataFromContainerV2(C const& container, I const i)
{
    if (i >= container.size())
    {
        throw std::out_of_range(std::to_string(i));
    }

    return container[i];
}

template <typename Point>
GeoPoint<Point>::GeoPoint() : GeoBase(GeoBase::Type::kGEOPOINT)
{
}

template <typename Point>
GeoPoint<Point>::~GeoPoint()
{
}

template <typename Point>
typename GeoPoint<Point>::PointType& GeoPoint<Point>::operator () ()
{
    return this->point_;
}

template <typename Point>
typename GeoPoint<Point>::PointType const& GeoPoint<Point>::operator () () const
{
    return this->point_;
}

template <typename Point>
std::string const& GeoPoint<Point>::Name()
{
    static std::string const name("Point");
    return name;
}

template <typename Point>
std::string const& GeoPoint<Point>::GetName() const
{
    return GeoPoint<Point>::Name();
}

template <typename Point>
void GeoPoint<Point>::Clear()
{
    this->point_ = PointType();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename Point, typename Container>
GeoMultiPoint<Point, Container>::GeoMultiPoint() : GeoBase(GeoBase::Type::kGEOMULTIPOINT)
{
}

template <typename Point, typename Container>
GeoMultiPoint<Point, Container>::~GeoMultiPoint()
{
}

template <typename Point, typename Container>
typename GeoMultiPoint<Point, Container>::ContainerType& GeoMultiPoint<Point, Container>::operator () ()
{
    return this->points_;
}

template <typename Point, typename Container>
typename GeoMultiPoint<Point, Container>::ContainerType const& GeoMultiPoint<Point, Container>::operator () () const
{
    return this->points_;
}

template <typename Point, typename Container>
typename GeoMultiPoint<Point, Container>::ElementType& GeoMultiPoint<Point, Container>::operator [] (
    GeoMultiPoint<Point, Container>::SizeType const i)
{
    return GetDataFromContainer(this->points_, i);
}
    
template <typename Point, typename Container>
typename GeoMultiPoint<Point, Container>::ElementType const& GeoMultiPoint<Point, Container>::operator [] (
    GeoMultiPoint<Point, Container>::SizeType const i) const
{
    return GetDataFromContainer(this->points_, i);
}

template <typename Point, typename Container>
void GeoMultiPoint<Point, Container>::Clear()
{
    this->points_.clear();
}

template <typename Point, typename Container>
typename GeoMultiPoint<Point, Container>::SizeType GeoMultiPoint<Point, Container>::Size() const
{
    return this->points_.size();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename Point, typename Container>
GeoLine<Point, Container>::GeoLine() : GeoBase(GeoBase::Type::kGEOLINE)
{
}

template <typename Point, typename Container>
GeoLine<Point, Container>::~GeoLine()
{
}

template <typename Point, typename Container>
typename GeoLine<Point, Container>::ContainerType& GeoLine<Point, Container>::operator () ()
{
    return this->line_;
}

template <typename Point, typename Container>
typename GeoLine<Point, Container>::ContainerType const& GeoLine<Point, Container>::operator () () const
{
    return this->line_;
}

template <typename Point, typename Container>
typename GeoLine<Point, Container>::ElementType& GeoLine<Point, Container>::operator [] (GeoLine<Point, Container>::SizeType const i)
{
    return GetDataFromContainer(this->line_, i);
}

template <typename Point, typename Container>
typename GeoLine<Point, Container>::ElementType const& GeoLine<Point, Container>::operator [] (GeoLine<Point, Container>::SizeType const i) const
{
    return GetDataFromContainerV2<Container, Point>(this->line_, i);
}

template <typename Point, typename Container>
void GeoLine<Point, Container>::Clear()
{
    this->line_.clear();
}

template <typename Point, typename Container>
holo::bool_t GeoLine<Point, Container>::Empty() const
{
    return this->line_.empty();
}

template <typename Point, typename Container>
typename GeoLine<Point, Container>::SizeType GeoLine<Point, Container>::Size() const
{
    return this->line_.size();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename Line, typename Container>
GeoMultiLine<Line, Container>::GeoMultiLine() : GeoBase(GeoBase::Type::kGEOMULTILINE)
{
}

template <typename Line, typename Container>
GeoMultiLine<Line, Container>::~GeoMultiLine()
{
}

template <typename Line, typename Container>
typename GeoMultiLine<Line, Container>::ContainerType const& GeoMultiLine<Line, Container>::GetLines() const noexcept
{
    return this->lines_;
}

template <typename Line, typename Container>
void GeoMultiLine<Line, Container>::SetLines(typename GeoMultiLine<Line, Container>::ContainerType const& lines)
{
    this->lines_ = lines;
}

template <typename Line, typename Container>
void GeoMultiLine<Line, Container>::SetLines(typename GeoMultiLine<Line, Container>::ContainerType && lines)
{
    this->lines_ = std::move(lines);
}

template <typename Point, typename Container>
void GeoMultiLine<Point, Container>::AddLine(typename GeoMultiLine<Point, Container>::ElementType const& line)
{
    this->lines_.push_back(line);
}

template <typename Line, typename Container>
void GeoMultiLine<Line, Container>::AddLine(typename GeoMultiLine<Line, Container>::ElementType && line)
{
    this->lines_.emplace_back(std::move(line));
}

template <typename Line, typename Container>
void GeoMultiLine<Line, Container>::Clear()
{
    this->lines_.clear();
}

template <typename Line, typename Container>
typename GeoMultiLine<Line, Container>::SizeType GeoMultiLine<Line, Container>::Size() const
{
    return this->lines_.size();
}

template <typename Line, typename Container>
typename GeoMultiLine<Line, Container>::ElementType& GeoMultiLine<Line, Container>::operator [] (GeoMultiLine<Line, Container>::SizeType const i)
{
    return GetDataFromContainer(this->lines_, i);
}

template <typename Line, typename Container>
typename GeoMultiLine<Line, Container>::ElementType const& GeoMultiLine<Line, Container>::operator [] (GeoMultiLine<Line, Container>::SizeType const i) const
{
    return GetDataFromContainer(this->lines_, i);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename Line, typename Container>
GeoPolygon<Line, Container>::GeoPolygon() : GeoBase(GeoBase::Type::kGEOPOLYGON)
{
}

template <typename Line, typename Container>
GeoPolygon<Line, Container>::~GeoPolygon()
{
}

template <typename Line, typename Container>
typename GeoPolygon<Line, Container>::ElementType const& GeoPolygon<Line, Container>::GetExteriorRing()
{
    return this->exterior_ring_;
}

template <typename Line, typename Container>
void GeoPolygon<Line, Container>::SetExteriorRing(typename GeoPolygon<Line, Container>::ElementType const& ring)
{
    this->exterior_ring_ = ring;
}

template <typename Line, typename Container>
void GeoPolygon<Line, Container>::SetExteriorRing(typename GeoPolygon<Line, Container>::ElementType && ring)
{
    this->exterior_ring_ = std::move(ring);
}

template <typename Line, typename Container>
typename GeoPolygon<Line, Container>::ContainerType const& GeoPolygon<Line, Container>::GetInternalRings()
{
    return this->internal_rings_;
}

template <typename Line, typename Container>
void GeoPolygon<Line, Container>::SetInternalRings(typename GeoPolygon<Line, Container>::ContainerType const& rings)
{
    this->internal_rings_ = rings;
}

template <typename Line, typename Container>
void GeoPolygon<Line, Container>::SetInternalRings(typename GeoPolygon<Line, Container>::ContainerType && rings)
{
    this->internal_rings_ = std::move(rings);
}

template <typename Line, typename Container>
void GeoPolygon<Line, Container>::Clear()
{
    this->exterior_ring_.Clear();
    this->internal_rings_.clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename Polygon, typename Container>
GeoMultiPolygon<Polygon, Container>::GeoMultiPolygon() : GeoBase(GeoBase::Type::kGEOMULTIPOLYGON)
{
}

template <typename Polygon, typename Container>
GeoMultiPolygon<Polygon, Container>::~GeoMultiPolygon()
{
}

template <typename Polygon, typename Container>
typename GeoMultiPolygon<Polygon, Container>::ContainerType const& GeoMultiPolygon<Polygon, Container>::GetPolygons() const noexcept
{
    return this->polygons_;
}

template <typename Polygon, typename Container>
void GeoMultiPolygon<Polygon, Container>::SetPolygons(ContainerType const& polygons)
{
    this->polygons_ = polygons;
}

template <typename Polygon, typename Container>
void GeoMultiPolygon<Polygon, Container>::SetPolygons(ContainerType && polygons)
{
    this->polygons_ = std::move(polygons);
}

template <typename Polygon, typename Container>
void GeoMultiPolygon<Polygon, Container>::AddPolygon(ElementType const& polygon)
{
    this->polygons_.push_back(polygon);
}

template <typename Polygon, typename Container>
void GeoMultiPolygon<Polygon, Container>::AddPolygon(ElementType && polygon)
{
    this->polygons_.emplace_back(std::move(polygon));
}

template <typename Polygon, typename Container>
void GeoMultiPolygon<Polygon, Container>::Clear()
{
    this->polygons_.clear();
}

template <typename Polygon, typename Container>
typename GeoMultiPolygon<Polygon, Container>::SizeType GeoMultiPolygon<Polygon, Container>::Size() const
{
    return this->polygons_.size();
}

template <typename Polygon, typename Container>
typename GeoMultiPolygon<Polygon, Container>::ElementType& GeoMultiPolygon<Polygon, Container>::operator [] (SizeType const i)
{
}

template <typename Polygon, typename Container>
typename GeoMultiPolygon<Polygon, Container>::ElementType const& GeoMultiPolygon<Polygon, Container>::operator [] (SizeType const i) const
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename Point, typename Container>
GeoCollection<Point, Container>::GeoCollection()
{
}

template <typename Point, typename Container>
GeoCollection<Point, Container>::~GeoCollection()
{
}

template <typename Point, typename Container>
typename GeoCollection<Point, Container>::SizeType GeoCollection<Point, Container>::GetPointsSize() const
{
    return this->points_.size();
}

template <typename Point, typename Container>
typename GeoCollection<Point, Container>::PointVectorType const& GeoCollection<Point, Container>::GetPoints() const
{
    return this->points_;
}

template <typename Point, typename Container>
typename GeoCollection<Point, Container>::PointType const& GeoCollection<Point, Container>::GetPoints(GeoCollection<Point, Container>::SizeType const i) const
{
    return GetDataFromContainer(this->points_, i);
}

template <typename Point, typename Container>
typename GeoCollection<Point, Container>::SizeType GeoCollection<Point, Container>::GetMultiPointsSize() const
{
    return this->multi_points_.size();
}

template <typename Point, typename Container>
typename GeoCollection<Point, Container>::MultiPointVectorType const& GeoCollection<Point, Container>::GetMultiPoints() const
{
    return this->multi_points_;
}

template <typename Point, typename Container>
typename GeoCollection<Point, Container>::MultiPointType const& GeoCollection<Point, Container>::GetMultiPoint(GeoCollection<Point, Container>::SizeType const i) const
{
    return GetDataFromContainer(this->multi_points_, i);
}

template <typename Point, typename Container>
typename GeoCollection<Point, Container>::SizeType GeoCollection<Point, Container>::GetLinesSize() const
{
    return this->lines_.size();
}

template <typename Point, typename Container>
typename GeoCollection<Point, Container>::LineVectorType const& GeoCollection<Point, Container>::GetLines() const
{
    return this->lines_;
}

template <typename Point, typename Container>
typename GeoCollection<Point, Container>::LineType const& GeoCollection<Point, Container>::GetLine(GeoCollection<Point, Container>::SizeType const i) const
{
    return GetDataFromContainer(this->lines_, i);
}

template <typename Point, typename Container>
typename GeoCollection<Point, Container>::SizeType GeoCollection<Point, Container>::GetMultiLinesSize() const
{
    return this->multi_lines_.size();
}

template <typename Point, typename Container>
typename GeoCollection<Point, Container>::MultiLineVectorType const& GeoCollection<Point, Container>::GetMultiLines() const
{
    return this->multi_lines_;
}

template <typename Point, typename Container>
typename GeoCollection<Point, Container>::MultiLineType const& GeoCollection<Point, Container>::GetMultiLine(GeoCollection<Point, Container>::SizeType const i) const
{
    return GetDataFromContainer(this->multi_lines_, i);
}

template <typename Point, typename Container>
typename GeoCollection<Point, Container>::SizeType GeoCollection<Point, Container>::GetPolygonsSize() const
{
    return this->polygons_.size();
}

template <typename Point, typename Container>
typename GeoCollection<Point, Container>::PolygonVectorType const& GeoCollection<Point, Container>::GetPolygons() const
{
    return this->polygons_;
}

template <typename Point, typename Container>
typename GeoCollection<Point, Container>::PolygonType const& GeoCollection<Point, Container>::GetPolygon(GeoCollection<Point, Container>::SizeType const i) const
{
    return GetDataFromContainer(this->polygons_, i);
}

template <typename Point, typename Container>
typename GeoCollection<Point, Container>::SizeType GeoCollection<Point, Container>::GetMultiPolygonsSize() const
{
    return this->multi_polygons_.size();
}

template <typename Point, typename Container>
typename GeoCollection<Point, Container>::MultiPolygonVectorType const& GeoCollection<Point, Container>::GetMultiPolygons() const
{
    return this->multi_polygons_;
}

template <typename Point, typename Container>
typename GeoCollection<Point, Container>::MultiPolygonType const& GeoCollection<Point, Container>::GetMultiPolygon(std::size_t const i) const
{
    return GetDataFromContainer(this->multi_polygons_, i);
}

template <typename Point, typename Container>
void GeoCollection<Point, Container>::Clear()
{
    this->points_.clear();
    this->multi_points_.clear();
    this->lines_.clear();
    this->multi_lines_.clear();
    this->polygons_.clear();
    this->multi_polygons_.clear();
}

} ///< namespace geometry.
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_COMMON_GEOMETRY_HPP_ */