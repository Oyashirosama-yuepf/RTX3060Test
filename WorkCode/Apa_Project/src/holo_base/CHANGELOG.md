# Changelog

## [Unreleased]

## [0.13.0] - 2022-04-27
### Added
- Keypoint3 type to ObstacleVersion
- Attributes to LayerId type in RoutingSearchRequestT
- Add attributes to DrivingStatus and RegionStateInfo type in NavigationT
### Changed
### Deprecated
### Removed
### Fixed
- Qac warning
- ObstacleVision default size
- Move BoundaryColor and BoundaryStyle type from LaneBoundary2 to boundary_feature.h
- Utility ComputePolynomialRoots method
- Change c0,c1,c2,c3 to curve template and add GetCurve method in camera_lane_boundary.h
- Replace epsilon type with ScalarEqualT type 

## [0.12.0] - 2022-03-28
### Added
- Vcast test case
### Changed
### Deprecated
### Removed
- Invalid delimiter
- IntrinsicT coordinate attribute
### Fixed
- Navigation interface
- Metadata generator version
- Holo deque container
- Missing header in deque.h
- Deprecated symbols in path
- Freespace missing assert header
- Extrinsic yaml io quaternion precision
- Classification enum string convert map

## [0.11.0] - 2022-03-01
### Added
- Map navagation interface
- Ransac_plane3_fitting_problem
- Gridmap class
- Navigation class
- OdometryPrecision class
- Holo container with custom allocator type alias
- New classification types

### Changed
### Deprecated
### Removed
### Fixed
- Odometry metadata error

## [0.10.0] - 2022-01-07
### Added
- Holo base metadata generator and generate yaml file
- Apa control command type description
- Gnss position type description
- Lane scene type description
- Odm type description
- Parking slot type description
- Common object type description
- Current route info type description
- Geofence type description
- Lane info type description
- Lane mark info type description
- Lane path type description
- Link info type description
- Obstacle lidar type description 
- Navigation request type description
- Road ref point attributes type description
- Fused obstacle type description
- Intention type description
- Intentions type description
- Image objects type description
- Object type description
- Wh01 vehicle state to common module
- RoadCategory LaneCategory to common module
- Road category class, 
- Road category to io module
- Road category type description to metadata
### Changed
### Deprecated
- RoadType LaneType in road type
### Removed
### Fixed
- Replace RoadType LaneType with RoadCategory LaneCategory in lane2
- Replace RoadType LaneType with RoadCategory LaneCategory in lane path
- Replace RoadType LaneType with RoadCategory LaneCategory in road ref point attributes 
- Replace RoadType LaneType with RoadCategory LaneCategory in road frame type description 
- Qac warning in common
- Kalman filter.hpp has no include guard

## [0.9.0] - 2021-12-07
### Added
- Intrinsic cx cy c d e getter, project and unproject polynomial getter and setter
- Holo_root qnx impl
- ControlCommand lateral and longitudinal value getter and setter
### Changed
### Deprecated
### Removed
### Fixed
- Qac warning
- ALIGNMENT assignment error in point_type class
- Metadata const string qualifier
- Deserialize method

## [0.8.0] - 2021-10-25
### Added
- Fused obstacle class 
- LocalMapOdometry and Drodometry class
- Traffic light GetSerializeSize doxygen comment
- Holo base metadata into holo base
- V0.8 change log and version number
- Geographical transformation to holo/utils
- Undistorted point mothod in intrinsic

### Changed
- Control command class and type description
 
### Deprecated

### Removed
- Map module KeyValue symbol rename to KeyType

### Fixed
- Path and PathPoint type attribute
- Roadframe gcc5 vector type 
- Map deprecated symbols
- OmnidirectionalIntrinsic param mistake
- Roadframe2 sequence type 
- Bernstein polynomial degree template param
- Intrinsic io and test case 
- Intrinsic hpp delete logging header
- Replace glog with hololog
 
## [0.7.0] - 2021-09-08
### Added
- VehicleBodyState yaml io
- Alarm yaml io
- GnssPvt yaml io
- Imu yaml io
- ImuBias yaml io
- Weather yaml io
- ChassisState yaml io
- GnssRawMeasurement yaml io
- AppStatus yaml io
- RoadType yaml io
- LightSignalRequest yaml io
- Path yaml io
- LanePath LaneMark member and termination type
- LanePath start and end direction attribute
- MapNavigation request object
### Changed
### Deprecated
### Removed
### Fixed
- RoadFrame AddLaneToNext3 curve index error
- obstacle module namespace and deprecated warnings
- Extrinsic access function header

## [0.6.0] - 2021-07-08
### Added
- SpherePoint3T and Sphere3T object
- Plane3T object
- LineSegment3T object
- ApaControlCommand object
- Traffic sign classification subtypes
- PointXYZIRRgbSt object
- LaneAdvice(AdviceT) object

### Changed
- Remove PointCloudT object default SIZE template argument
- Use Serializer/Deserializer module defined in holo_utils project
- Check matrix dimention for dynamic size matrix

### Deprecated

### Removed

### Fixed
- CurveBase object Serialization/Deserialization method
- RoadFrame link error with gcc5 compiler
- Fix bugs in holo_base-config.cmake.in template
- ParkingSlot and LightSignalRequest compile error
- Deprecated warnings
- TlvSequence serialize/deserialize bug

## [0.5.0] - 2021-02-01
### Added
- Uss Raw object
- Serializer/Deserializer support bool type
- holo::utils::tlv object support string/char\* type
- PointClould module. Include point cloud object and point objects.
- Emergency lane type to LaneType object.
- Ddt/Ddts(Dynamic Driving Task) class
- Alarm class
- Precision flags to Odometry class
- holo::planning::State class
- Image class support UYUV, YUV422P, YU12, YV12, NV12, NV21 image encoding types
- holo::container::VectorT and holo::container::details::VectorBaseT object
- Freespace object
- Camera Intrinsic implementation
- Wheel pulse to ChassisState
- IO module for yaml/string input/output
- Sensor id to intrinsic

### Changed
- CMake build scripts: Move HoloProjectConfigurations.cmake into holo_cmake_scripts project
- CMake build scripts: Remove unused hardcoded compile flags
- RoadFrame: add iterator to replace GraphNode object
- Return type of Point2T::operator-() and Point3T::operator-() change from VectorType to PointType
- Drop pimpl pattern for Timestamp, Duration, Imu, ImuBias object
- Add "geometry" namespace to classes/functions defined in geometry module.
- Add "common" namespace to classes/functions defined in common module.
- ChassisState and VehicleBodyState implementation
- Serialize/Deserialize API for all modules
- Numerics Matrix/Vector object header file include template implementation. Explicit instanciation is not needed any more.

### Deprecated
- holo::RoadFrame object(road frame v1)
- holo::Lane object(lane v1)
- holo::LaneBoundary objct(lane boundary v1)
- holo::planning::PlanningState
- holo::planning::PilotState

### Removed

### Fixed
- Missing typename keyword and wrong template arguments in container module
- Get system time works improperly in QNX system
- AppStatus compile error with gcc5
- Lots of Deprecate warnings
- RoadFrame is not copyable


## [0.4.0] - 2020-08-07
### Added
- Vision object and ImageObjects class.
- Cast functions between uint32 and holo::classification
- Clear() method to holo::common::RoadFrame object.
- RoadType and LaneType class.
- Road and lane attributes to holo::common::Lane object.
- RoadRefPointAttribute object.

### Changed
- Project cmake script layout.
- Use GenerateDoxygen and GenerateCoverageReport command in cmake scripts.

### Deprecated

### Removed

### Fixed
- Find opencv script won't detect opencv libs in DDK.
- Wrong standard library include headers in some source files.


## [0.3.0] - 2020-08-02
### Added
- RoadFrame graph to MapAdvice.
- Serialize/Deserialize functions to RoadFrame
- APIs to set end conditions to lane boundary

### Changed
- AppStatus now contains a list of status code.

### Deprecated

### Removed

### Fixed
- LaneBoundary2 end index should point to past-the-end index.
- SFINAE tag error in LaneBoundary2


## [0.2.0] - 2020-06-30
### Added
- Math module.
- Factorial method to math module.
- Power of integer to math module.
- BernsteinPolynomial and general Polynomial object.
- LaneScene object.
- MapTraffic object.
- MapWeather object.
- Curve module.
- CurveParametric and CurveExplicit to curve module.
- Piecewise linear/cubic bezier algorithm to curve module.
- Piecewise linear/cubic polynomial algorithm to curve module.
- Serialize/Deserialize method to Intention(s) object.
- IsOnHDMap indicator to map::Advice
- PerceptionAbility attribute to ObstacleList
- New LaneBoundary implementation
- New Lane implementation
- New RoadFrame implementation
- Serialize/Deserialize to Geofence(s)
- New Tlv/TlvSequence implementation
- Single polynomial curve type LaneBoundary
- Single polynomial curve type RoadFrame

### Changed

### Deprecated

### Removed

### Fixed
- Unicode characters in doxygen comments.
- Some bugs in reference buffer constructor.
- Wrong Odometry::Source enumerate values.
- Incorrect intention string representation.
- All static_assert without comment string.
