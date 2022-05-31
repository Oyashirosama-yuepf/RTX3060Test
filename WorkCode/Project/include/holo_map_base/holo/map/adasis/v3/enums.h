/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file Enumerations.h
 * @brief This header file defines the adasis v3 enuerations.
 * @author zhengshulei@holomatic.com
 * @date 2021-09-28
 */
#ifndef HOLO_MAP_ADASIS_V3_ENUMERATIONS_H_
#define HOLO_MAP_ADASIS_V3_ENUMERATIONS_H_

#include <holo/core/types.h>

namespace holo
{
namespace map
{
namespace adasis
{
namespace v3_1_1
{
enum class Availability : holo::uint8_t
{
    NotAvailable,
    Valid
};

enum class ChangeMode : holo::uint8_t
{
    Create,
    Update,
    Delete
};

enum class ConditionType : holo::uint8_t
{
    conditionTypeUnknown,
    conditionTypeVehicle,
    conditionTypeLoad,
    conditionTypeTimeOfDay,
    conditionTypeDaysOfWeek,
    conditionTypeWeight,
    conditionTypeTurnDirection,
    conditionTypeWeather,
    conditionTypeFuzzyTime
};

enum class CurveType : holo::uint8_t
{
    NotPresent,
    Polyline,
    BezierSpline
};

enum class DrivingSide : holo::uint8_t
{
    RightHandDriving = 0,
    LeftHandDriving  = 1
};

enum class EffectiveSpeedLimitType : holo::uint8_t
{
    Unknown,
    Implicit,
    ExplicitOnTrafficSign,
    ExplicitNight,
    ExplicitDay,
    ExplicitTimeOrDay,
    ExplicitRain,
    ExplicitSnow,
    ExplicitFog
};

enum class FormOfWay : holo::uint8_t
{
    Unknown                   = 0,
    ControlledAccess          = 1,
    MultipleCarriageWay       = 2,
    SingleCarriageWay         = 3,
    RoundaboutCircle          = 4,
    SpecialTrafficFigure      = 5,
    ReservedA                 = 6,
    ReservedB                 = 7,
    ParallelRoad              = 8,
    RampOnControlledAccess    = 9,
    RampNotOnControlledAccess = 10,
    FrontageRoad              = 11,
    CarPark                   = 12,
    Service                   = 13,
    PedestrianZone            = 14,
    NotAvailable              = 15
};

enum class FuzzyTime : holo::uint8_t
{
    Unknown,
    Day,
    Night
};

enum class GuidanceMode : holo::uint8_t
{
    guidanceInactive,
    guidanceForUser,
    guidanceAutomatic
};

enum class LaneArrowMarking : int32_t
{
    None        = 0,
    Straight    = 1,
    SlightRight = 2,
    Right       = 4,
    HardRight   = 8,
    UTurn       = 16,
    HardLeft    = 32,
    Left        = 64,
    SlightLeft  = 128,
    NA          = -1
};

enum class LaneTransition : holo::uint8_t
{
    None,
    Opening,
    Closing,
    Merging,
    Splitting
};

enum class LaneTypeFlags : uint32_t
{
    Unknown             = 0,
    Normal              = 1,
    Exit                = 2,
    Entry               = 4,
    Auxiliary           = 8,
    Emergency           = 16,
    RestrictedForbidden = 32,
    RestrictedUsable    = 64,
    HOV                 = 128,
    Express             = 256,
    Reversible          = 512,
    Slow                = 1024,
    DrivableShoulder    = 2048,
    TurnOrSuicide       = 4096
};

enum class LateralPosition : holo::uint8_t
{
    Unknown = 0,
    Right   = 1,
    Left    = 2,
    Above   = 4,
    Surface = 8
};

enum class LineMarking : holo::uint8_t
{
    Unknown,
    None,
    SolidLine,
    DashedLine,
    DoubleSolidLine,
    DoubleDashedLine,
    LeftSolidRightDashed,
    RightSolidLeftDashed,
    DashedBlocks,
    ShadedArea,
    PhysicalDivider
};

enum class LineMarkingColour : holo::uint8_t
{
    None,
    Other,
    White,
    Yellow,
    Orange,
    Red,
    Blue
};

enum class LinearObjectType : holo::uint8_t
{
    Centerline,
    LaneMarking,
    Guardrail,
    Fence,
    Kerb,
    Wall
};

enum class Load : holo::uint8_t
{
    loadWaterPolluting,
    loadExplosive,
    loadOtherDangerous,
    loadEmpty,
    loadSpecial,
    loadGasses,
    loadFlammableLiquids,
    loadFlammableSolids,
    loadOxidizing,
    loadToxicInfectious,
    loadRadioactive,
    loadCorrosive
};

enum class LocationObjectType : holo::uint8_t
{
    GuidePost
};

enum class MapProvider : holo::uint8_t
{
    provider_Unknown,
    provider_AND,
    provider_AutoNavi,
    provider_HERE,
    provider_Hyundai,
    provider_Navinfo,
    provider_TomTom,
    provider_Zenrin,
    provider_Baidu // for a13  requirement
};

enum class MapStatus : holo::uint8_t
{
    mapNotAvailable,
    mapLoading,
    mapAvailable
};

enum class Quality : holo::uint8_t
{
    Unknown,
    NotAvailable,
    Value1,
    Value2,
    Value3,
    Value4,
    Value5
};

enum class RelativeDirection : holo::uint8_t
{
    None,
    Both,
    AlongPathDirection,
    AgainstPathDirection
};

enum class RightOfWay : holo::uint8_t
{
    Unknown,
    MustYield,
    HasRightOfWay
};

enum class RoadAccessFlags : holo::uint8_t
{
    PassengerCars  = 1,
    Pedestrians    = 2,
    Bus            = 4,
    Delivery       = 8,
    Emergency      = 16,
    Taxi           = 32,
    ThroughTraffic = 64,
    Trucks         = 128
};

enum class RoadCondition : holo::uint8_t
{
    Unknown,
    Clear,
    Wet,
    Snowy,
    Icy,
    Slippery,
    Dirt
};

enum class SignType : holo::uint8_t
{
    Unknown                                      = 255,
    LeftBend                                     = 10,
    RightBend                                    = 9,
    DoubleBendLeftFirst                          = 14,
    DoubleBendRightFirst                         = 13,
    CurvyRoad                                    = 17,
    SteepDescent                                 = 68,
    SteepAscent                                  = 67,
    CarriageWayNarrows                           = 40,
    CarriageWayNarrowsLeft                       = 42,
    CarriageWayNarrowsRight                      = 41,
    SwingBridge                                  = 89,
    RiverBank                                    = 29,
    RiverBankLeft                                = 30,
    UnevenRoad                                   = 69,
    Hump                                         = 70,
    Dip                                          = 71,
    SlipperyRoad                                 = 66,
    FallingRocksRight                            = 62,
    FallingRocksLeft                             = 61,
    Pedestrians                                  = 50,
    PedestrianCrossing                           = 51,
    Children                                     = 52,
    SchoolZone                                   = 53,
    Cyclists                                     = 54,
    DomesticAnimalsCrossing                      = 4,
    WildAnimalsCrossing                          = 5,
    RoadWorks                                    = 6,
    LightSignals                                 = 31,
    DangerousIntersection                        = 22,
    Intersection                                 = 35,
    IntersectionWithPriorityToTheRight           = 37,
    IntersectionWithMinorRoad                    = 36,
    TwoWayTraffic                                = 55,
    TafficCongestion                             = 75,
    RailwayCrossingWithGates                     = 56,
    RailwayCrossingWithoutGates                  = 57,
    TramWay                                      = 59,
    RailwayCrossing                              = 58,
    Danger                                       = 0,
    GiveWay                                      = 32,
    Stop                                         = 33,
    PriorityRoad                                 = 34,
    PriorityForOncomingTraffic                   = 82,
    PriorityOverOncomingTraffic                  = 81,
    OvertakingProhibited                         = 46,
    OvertakingByGoodsVehiclesProhibited          = 20,
    SpeedLimit                                   = 87,
    EndOfAllProhibitions                         = 79,
    EndOfSpeedLimit                              = 88,
    EndOfProhibitionOnOvertaking                 = 47,
    EndOfProhibitionOnOvertakingForGoodsVehicles = 21,
    DirectionToTheRight                          = 38,
    DirectionToTheLeft                           = 39,
    PassRightSide                                = 3,
    PassLeftOrRightSide                          = 1,
    PassLeftSide                                 = 2,
    BeginningOfBuiltUpArea                       = 77,
    EndOfBuiltUpArea                             = 83,
    Tunnel                                       = 24,
    ResidentialArea                              = 7,
    EndOfResidentialArea                         = 8,
    LaneMergeRight                               = 44,
    LaneMergeLeft                                = 43,
    ProtectedPassingEnd                          = 48,
    HumpbackBridge                               = 28,
    VariableSignMechanicElements                 = 65,
    VariableSignLightElements                    = 80,
    FerryTerminal                                = 25,
    NarrowBridge                                 = 26,
    IcyRoad                                      = 73,
    SteepDropLeft                                = 63,
    SteepDropRight                               = 64,
    RoadFloods                                   = 72,
    SideWinds                                    = 74,
    LaneMergeCenter                              = 45,
    HighAccidentArea                             = 76,
    AudibleWarning                               = 78
};

enum class SpecialSituationType : holo::uint8_t
{
    DeadEnd            = 248,
    FerryTerminal      = 249,
    TollBooth          = 250,
    RailroadCrossing   = 251,
    PedestrianCrossing = 252,
    SpeedBump          = 253
};

enum class SpeedLimitSource : holo::uint8_t
{
    Unknown,
    Implicit,
    Explicit
};

enum class SurfaceCondition : holo::uint8_t
{
    Unknown,
    PavedRigid,
    PavedFlexible,
    Blocks,
    Gravel,
    Dirt
};

enum class TrafficLightLongitudinalPosition : holo::uint8_t
{
    Unknown,
    BeforeIntersection,
    AfterIntersection
};

enum class TrafficLightState : holo::uint8_t
{
    Unknown,
    Invalid,
    Off,
    Green,
    Yellow,
    Red
};

enum class UnitOfSpeed : holo::uint8_t
{
    KpH,
    MpH
};

enum class Weather : holo::uint8_t
{
    Unknown,
    NoSpecial,
    Sunshine,
    Rain,
    Fog,
    Snow,
    Ice,
    StrongWind,
};

enum class YesNoUnknown : holo::uint8_t
{
    Unknown,
    Yes,
    No
};

enum class ProfileType : holo::uint8_t
{
    Node = 0,
    Probability,
    HeadingChange,
    LaneModel,
    LaneConnectivity,
    LinearObjects,
    LanesGeometry,
    LaneWidth,
    RoadGeometry,
    NumberOfLanesPerDirection,
    ComplexIntersection,
    LinkIdentifier,
    FunctionalRoadClass,
    RouteNumberTypes,
    FormOfWay,
    RoadAccessibility,
    AccessRestriction,
    OvertakingRestriction,
    Tunnel,
    Bridge,
    DividedRoad,
    Curvature,
    Slope,
    BuiltUpArea,
    InTown,
    Surface,
    TrafficSign,
    TrafficLight,
    SpecialSituation,
    EffectiveSpeedLimit,
    ExtendedSpeedLimit,
    AverageSpeed,
    FlowSpeed,
    RoadCondition,
    Weather,
    LocationObject,
    PartOfCalculatedRoute,
    CountryCode,
    RegionCode,
    DrivingSide,
    UnitSystem,
    VersionProtocol,
    VersionHardware,
    VersionMap,
    MapAge,
    MapProvider,
    MapStatus,
    SystemStatus,
    TimeZoneOffset,
    AbsoluteVehiclePosition
};

enum class MessageType : holo::uint8_t
{
    Position = 0,
    Profile = 1,
    GlobalData = 2,
    ProfileControl = 3,
    PathControl = 4
};

} // namespace v3_1_1
} // namespace adasis
} // namespace map
} // namespace holo

#endif /* HOLO_MAP_ADASIS_V3_ENUMERATIONS_H_ */