/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file geometry.h
 * @brief geometry.h
 * @author wanghaiyang@holomatic.com
 * @date "2020-10-08"
 */

#ifndef HOLO_MAP_SERVICE_CLIENT_COMMON_GEOMETRY_H_
#define HOLO_MAP_SERVICE_CLIENT_COMMON_GEOMETRY_H_

#include <vector>

#include <holo/geometry/point3.h>

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

class GeoBase
{
public:
    enum class Type : holo::uint8_t
    {
        kUNKNOWN = 0,
        kGEOPOINT,
        kGEOMULTIPOINT,
        kGEOLINE,
        kGEOMULTILINE,
        kGEOPOLYGON,
        kGEOMULTIPOLYGON,
        kGEOCOLLECTION,
        kGEO_BOUNDING_BOX,
        kMAX
    };

    GeoBase();
    virtual ~GeoBase();
    
    explicit GeoBase(Type const t);

    static std::string const& Name();

    virtual std::string const& GetName() const;

    virtual void Clear();

    Type GetType() const;

protected:
    Type type_ = Type::kUNKNOWN;
};


template <typename Point>
class GeoPoint : public GeoBase
{
public:
    using PointType = Point;

    GeoPoint();
    virtual ~GeoPoint();

    PointType& operator () ();
    
    PointType const& operator () () const;

    static std::string const& Name();

    std::string const& GetName() const;

    void Clear();
private:
    PointType point_;
};


template <typename Point, typename Container = std::vector<Point>>
class GeoMultiPoint : public GeoBase
{
public:
    using SizeType          = std::size_t;
    using ElementType       = Point;
    using ContainerType     = Container;

    GeoMultiPoint();
    virtual ~GeoMultiPoint();

    ContainerType& operator () ();

    ContainerType const& operator () () const;

    ElementType& operator [] (SizeType const i);
    ElementType const& operator [] (SizeType const i) const;

    void Clear();

    SizeType Size() const;

private:
    ContainerType points_;
};

template <typename Point, typename Container = std::vector<Point>>
class GeoLine : public GeoBase
{
public:
    using SizeType      = std::size_t;
    using ElementType   = Point;
    using ContainerType = Container;

    GeoLine();

    virtual ~GeoLine();

    ContainerType& operator () ();

    ContainerType const& operator () () const;

    ElementType& operator [] (SizeType const i);
    ElementType const& operator [] (SizeType const i) const;

    void Clear();

    holo::bool_t Empty() const;

    SizeType Size() const;
private:
    ContainerType line_;
};

template <typename Line, typename Container = std::vector<Line>>
class GeoMultiLine : public GeoBase
{
public:
    using SizeType          = std::size_t;
    using ElementType       = Line;
    using ContainerType     = Container;

    GeoMultiLine();
    virtual ~GeoMultiLine();

    ContainerType const& GetLines() const noexcept;
    void SetLines(ContainerType const& lines);
    void SetLines(ContainerType && lines);

    void AddLine(ElementType const& line);
    void AddLine(ElementType && line);

    void Clear();

    SizeType Size() const;
    ElementType& operator [] (SizeType const i);
    ElementType const& operator [] (SizeType const i) const;

private:
    ContainerType lines_;
};

template <typename Line, typename Container = std::vector<Line>>
class GeoPolygon : public GeoBase
{
public:
    using SizeType          = std::size_t;
    using ElementType       = Line;
    using ContainerType     = Container;

    GeoPolygon();
    virtual ~GeoPolygon();

    ElementType const& GetExteriorRing();
    void SetExteriorRing(ElementType const& ring);
    void SetExteriorRing(ElementType&& ring);

    ContainerType const& GetInternalRings();
    void SetInternalRings(ContainerType const& rings);
    void SetInternalRings(ContainerType && rings);

    void Clear();

private:
    ElementType     exterior_ring_;
    ContainerType   internal_rings_;
};

template <typename Polygon, typename Container = std::vector<Polygon>>
class GeoMultiPolygon : public GeoBase
{
public:
    using SizeType      = std::size_t;
    using ElementType   = Polygon;
    using ContainerType = Container;

    GeoMultiPolygon();
    virtual ~GeoMultiPolygon();

    ContainerType const& GetPolygons() const noexcept;
    void SetPolygons(ContainerType const& poltygons);
    void SetPolygons(ContainerType && polygons);

    void AddPolygon(ElementType const& line);
    void AddPolygon(ElementType && line);

    void Clear();

    SizeType Size() const;
    ElementType& operator [] (SizeType const i);
    ElementType const& operator [] (SizeType const i) const;

private:
    ContainerType polygons_;
};

template <typename Point, typename Container>
class GeoCollection
{
public:
    using SizeType = std::size_t;

    using PointType                     = GeoPoint<Point>;
    using MultiPointType                = GeoMultiPoint<Point>;
    using LineType                      = GeoLine<Point>;
    using MultiLineType                 = GeoMultiLine<LineType>;
    using PolygonType                   = GeoPolygon<LineType>;
    using MultiPolygonType              = GeoMultiPolygon<PolygonType>;

    using PointVectorType            = std::vector<PointType>;
    using MultiPointVectorType       = std::vector<MultiPointType>;
    using LineVectorType             = std::vector<LineType>;
    using MultiLineVectorType        = std::vector<MultiLineType>;
    using PolygonVectorType          = std::vector<PolygonType>;
    using MultiPolygonVectorType     = std::vector<MultiPolygonType>;

    GeoCollection();
    virtual ~GeoCollection();

    SizeType GetPointsSize() const;
    PointVectorType const& GetPoints() const;
    PointType const& GetPoints(std::size_t const i) const;

    SizeType GetMultiPointsSize() const;
    MultiPointVectorType const& GetMultiPoints() const;
    MultiPointType const& GetMultiPoint(std::size_t const i) const;

    SizeType GetLinesSize() const;
    LineVectorType const& GetLines() const;
    LineType const& GetLine(std::size_t i) const;

    SizeType GetMultiLinesSize() const;
    MultiLineVectorType const& GetMultiLines() const;
    MultiLineType const& GetMultiLine(std::size_t const i) const;

    SizeType GetPolygonsSize() const;
    PolygonVectorType const& GetPolygons() const;
    PolygonType const& GetPolygon(std::size_t const i) const;

    SizeType GetMultiPolygonsSize() const;
    MultiPolygonVectorType const& GetMultiPolygons() const;
    MultiPolygonType const& GetMultiPolygon(std::size_t const i) const;

    void Clear();

private:
    PointVectorType          points_;
    MultiPointVectorType     multi_points_;
    LineVectorType           lines_;
    MultiLineVectorType      multi_lines_;
    PolygonVectorType        polygons_;
    MultiPolygonVectorType   multi_polygons_;
}; ///< End of class GeoCollection.

} ///< namespace geometry.
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#include "./impl/geometry.hpp"

#endif /* HOLO_MAP_SERVICE_CLIENT_COMMON_GEOMETRY_H_ */