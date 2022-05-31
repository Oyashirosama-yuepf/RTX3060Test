/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ProfileValue.h
 * @brief This header file defines the base profilevalue structure.
 * @author zhengshulei@holomatic.com
 * @date 2021-09-28
 */
#ifndef HOLO_MAP_ADASIS_V3_PROFILEVALUE_H_
#define HOLO_MAP_ADASIS_V3_PROFILEVALUE_H_

#include <holo/map/adasis/serialization/serialization.h>
#include <holo/map/adasis/v3/enums.h>
#include <holo/map/adasis/v3/types.h>

using Serializer   = holo::map::adasis::serialization::Serializer;
using Deserializer = holo::map::adasis::serialization::Deserializer;

namespace holo
{
namespace map
{
namespace adasis
{
namespace v3_1_1
{
class Vector
{
public:
    Vector()
    {
    }
    ~Vector()
    {
    }

public:
    void Serialize(Serializer& s) const
    {
        s << x << y << z;
    }
    void Deserialize(Deserializer& s)
    {
        s >> x >> y >> z;
    }

public:
    holo::float32_t x = 0;
    holo::float32_t y = 0;
    holo::float32_t z = 0;
};

class WGS84Point
{
public:
    WGS84Point()
    {
    }
    ~WGS84Point()
    {
    }

public:
    void Serialize(Serializer& s) const
    {
        s << latitude << longitude << altitude;
    }
    void Deserialize(Deserializer& s)
    {
        s >> latitude >> longitude >> altitude;
    }

public:
    void PrintDebugINfo()
    {
        holo::float32_t unit = 360.0f / (1L << 32);
        LOG(INFO) << "WGS84Point info, " << std::to_string(longitude * unit)
                  << "," << std::to_string(latitude * unit);
                  // << "," << altitude;
    }

public:
    holo::int32_t latitude  = 0;
    holo::int32_t longitude = 0;
    holo::int32_t altitude  = 0;
};

class ProfileValue
{
};

class UInt32ProfileValue : public ProfileValue
{
public:
    void Serialize(Serializer& s) const
    {
        s << value;
    }
    void Deserialize(Deserializer& s)
    {
        s >> value;
    }

public:
    holo::uint32_t value = 0;
};

using NumberOfLanesPerDirectionProfileValue = UInt32ProfileValue;
using FunctionalRoadClassProfileValue       = UInt32ProfileValue;
using RouteNumberTypesProfileValue          = UInt32ProfileValue;
using CountryCodeProfileValue               = UInt32ProfileValue;
using VersionProtocolProfileValue           = UInt32ProfileValue;
using VersionHardwareProfileValue           = UInt32ProfileValue;
using VersionMapProfileValue                = UInt32ProfileValue;
using MapAgeProfileValue                    = UInt32ProfileValue;

class Int32ProfileValue : public ProfileValue
{
public:
    void Serialize(Serializer& s) const
    {
        s << value;
    }
    void Deserialize(Deserializer& s)
    {
        s >> value;
    }

public:
    holo::int32_t value = 0;
};

using RoadAccessibilityProfileValue = Int32ProfileValue;
using TimeZoneOffsetProfileValue    = Int32ProfileValue;

class UInt64ProfileValue : public ProfileValue
{
public:
    void Serialize(Serializer& s) const
    {
        s << value;
    }
    void Deserialize(Deserializer& s)
    {
        s >> value;
    }

public:
    holo::uint64_t value = 0;
};

using LinkIdentifierProfileValue = UInt64ProfileValue;

class FloatProfileValue : public ProfileValue
{
public:
    void Serialize(Serializer& s) const
    {
        s << value;
    }
    void Deserialize(Deserializer& s)
    {
        s >> value;
    }

public:
    holo::float32_t value = 0;
};

using ProbabilityProfileValue   = FloatProfileValue;
using HeadingChangeProfileValue = FloatProfileValue;

class BooleanProfileValue : public ProfileValue
{
public:
    void Serialize(Serializer& s) const
    {
        s << value;
    }
    void Deserialize(Deserializer& s)
    {
        s >> value;
    }

public:
    holo::bool_t value = false;
};

using ComplexIntersectionProfileValue   = BooleanProfileValue;
using TunnelProfileValue                = BooleanProfileValue;
using BridgeProfileValue                = BooleanProfileValue;
using DividedRoadProfileValue           = BooleanProfileValue;
using BuiltUpAreaProfileValue           = BooleanProfileValue;
using InTownProfileValue                = BooleanProfileValue;
using PartOfCalculatedRouteProfileValue = BooleanProfileValue;

class YesNoUnknownProfileValue : public ProfileValue
{
public:
    void Serialize(Serializer& s) const
    {
        s << static_cast<holo::uint8_t>(value);
    }
    void Deserialize(Deserializer& s)
    {
        holo::uint8_t v;
        s >> v;
        value = static_cast<YesNoUnknown>(v);
    }

public:
    YesNoUnknown value = YesNoUnknown::Unknown;
};

class FormOfWayProfileValue : public ProfileValue
{
public:
    void Serialize(Serializer& s) const
    {
        s << static_cast<holo::uint8_t>(value);
    }
    void Deserialize(Deserializer& s)
    {
        holo::uint8_t v;
        s >> v;
        value = static_cast<FormOfWay>(v);
    }
public:
    void PrintDebugInfo()
    {
        LOG(INFO) << "FormOfWayProfileValue info, FormOfWay=" << static_cast<holo::uint16_t>(value);
    }

public:
    FormOfWay value = FormOfWay::Unknown;
};

class DrivingSideProfileValue : public ProfileValue
{
public:
    void Serialize(Serializer& s) const
    {
        s << static_cast<holo::uint8_t>(value);
    }
    void Deserialize(Deserializer& s)
    {
        holo::uint8_t v;
        s >> v;
        value = static_cast<DrivingSide>(v);
    }

public:
    DrivingSide value = DrivingSide::RightHandDriving;
};

class UnitSystemProfileValue : public ProfileValue
{
public:
    void Serialize(Serializer& s) const
    {
        s << static_cast<holo::uint8_t>(value);
    }
    void Deserialize(Deserializer& s)
    {
        holo::uint8_t v;
        s >> v;
        value = static_cast<UnitOfSpeed>(v);
    }

public:
    UnitOfSpeed value = UnitOfSpeed::KpH;
};

class SpecialSituationProfileValue : public ProfileValue
{
public:
    void Serialize(Serializer& s) const
    {
        s << static_cast<holo::uint8_t>(value);
    }
    void Deserialize(Deserializer& s)
    {
        holo::uint8_t v;
        s >> v;
        value = static_cast<SpecialSituationType>(v);
    }

public:
    SpecialSituationType value = SpecialSituationType::DeadEnd;
};

class RoadConditionProfileValue : public ProfileValue
{
public:
    void Serialize(Serializer& s) const
    {
        s << static_cast<holo::uint8_t>(value);
    }
    void Deserialize(Deserializer& s)
    {
        holo::uint8_t v;
        s >> v;
        value = static_cast<RoadCondition>(v);
    }

public:
    RoadCondition value = RoadCondition::Unknown;
};

class WeatherProfileValue : public ProfileValue
{
public:
    void Serialize(Serializer& s) const
    {
        s << static_cast<holo::uint8_t>(value);
    }
    void Deserialize(Deserializer& s)
    {
        holo::uint8_t v;
        s >> v;
        value = static_cast<Weather>(v);
    }

public:
    Weather value = Weather::Unknown;
};

class MapProviderProfileValue : public ProfileValue
{
public:
    void Serialize(Serializer& s) const
    {
        s << static_cast<holo::uint8_t>(value);
    }
    void Deserialize(Deserializer& s)
    {
        holo::uint8_t v;
        s >> v;
        value = static_cast<MapProvider>(v);
    }

public:
    MapProvider value = MapProvider::provider_Unknown;
};

class MapStatusProfileValue : public ProfileValue
{
public:
    void Serialize(Serializer& s) const
    {
        s << static_cast<holo::uint8_t>(value);
    }
    void Deserialize(Deserializer& s)
    {
        holo::uint8_t v;
        s >> v;
        value = static_cast<MapStatus>(v);
    }

public:
    MapStatus value = MapStatus::mapNotAvailable;
};

class SystemStatusProfileValue : public ProfileValue
{
public:
    void Serialize(Serializer& s) const
    {
        s << static_cast<holo::uint8_t>(guidance) << simulating;
    }
    void Deserialize(Deserializer& s)
    {
        holo::uint8_t v;
        s >> v >> simulating;
        guidance = static_cast<GuidanceMode>(v);
    }

public:
    GuidanceMode guidance   = GuidanceMode::guidanceInactive;
    holo::bool_t simulating = false;
};

class RegionCodeValue : public ProfileValue
{
public:
    void Serialize(Serializer& s) const
    {
        s.WriteArray(3, value);
    }
    void Deserialize(Deserializer& s)
    {
        s.ReadArray(3, value);
    }

public:
    holo::uint8_t value[3] = {0, 0, 0};
};

class LaneWidthProfileValue : public ProfileValue
{
public:
    void Serialize(Serializer& s) const
    {
        s << minwidth << maxwidth;
    }
    void Deserialize(Deserializer& s)
    {
        s >> minwidth >> maxwidth;
    }

public:
    void PrintDebugInfo()
    {
        LOG(INFO) << "LaneWidthProfileValue info, minwidth=" << minwidth
                  << " maxwidth=" << maxwidth;
    }

public:
    holo::uint16_t minwidth = 0;
    holo::uint16_t maxwidth = 0;
};

class Condition
{
public:
    Condition()
    {
    }
    virtual ~Condition()
    {
    }

public:
    void Serialize(Serializer& s) const
    {
        s << static_cast<holo::uint8_t>(type) << static_cast<holo::uint8_t>(appliesToEgoVehicle);
    }
    void Deserialize(Deserializer& s)
    {
        holo::uint8_t v1;
        holo::uint8_t v2;
        s >> v1 >> v2;
        type                = static_cast<ConditionType>(v1);
        appliesToEgoVehicle = static_cast<YesNoUnknown>(v2);
    }

public:
    ConditionType type               = ConditionType::conditionTypeUnknown;
    YesNoUnknown appliesToEgoVehicle = YesNoUnknown::Unknown;
};

class ConditionNumeric : public Condition
{
public:
    using super_t = Condition;

public:
    void Serialize(Serializer& s) const
    {
        super_t::Serialize(s);
        s << value;
    }
    void Deserialize(Deserializer& s)
    {
        super_t::Deserialize(s);
        s >> value;
    }

public:
    holo::uint32_t value = 0;
};

class ConditionVehicleType : public Condition
{
public:
    using super_t = Condition;

public:
    void Serialize(Serializer& s) const
    {
        super_t::Serialize(s);
        s << vehicleTypeMask;
    }
    void Deserialize(Deserializer& s)
    {
        super_t::Deserialize(s);
        s >> vehicleTypeMask;
    }

public:
    holo::uint32_t vehicleTypeMask = 0;
};

class ConditionLoad : public Condition
{
public:
    using super_t = Condition;

public:
    void Serialize(Serializer& s) const
    {
        super_t::Serialize(s);
        s << static_cast<holo::uint8_t>(value);
    }
    void Deserialize(Deserializer& s)
    {
        super_t::Deserialize(s);
        holo::uint8_t v;
        s >> v;
        value = static_cast<Load>(v);
    }

public:
    Load value = Load::loadEmpty;
};

class ConditionTimeOfDay : public Condition
{
public:
    using super_t = Condition;

public:
    void Serialize(Serializer& s) const
    {
        super_t::Serialize(s);
        s << startMinutes << endMinutes;
    }
    void Deserialize(Deserializer& s)
    {
        super_t::Deserialize(s);
        s >> startMinutes >> endMinutes;
    }

public:
    holo::uint16_t startMinutes = 0;
    holo::uint16_t endMinutes   = 0;
};

class ConditionWeather : public Condition
{
public:
    using super_t = Condition;

public:
    void Serialize(Serializer& s) const
    {
        super_t::Serialize(s);
        s << static_cast<holo::uint8_t>(weather);
    }
    void Deserialize(Deserializer& s)
    {
        super_t::Deserialize(s);
        holo::uint8_t v;
        s >> v;
        weather = static_cast<Weather>(v);
    }

public:
    Weather weather = Weather::Unknown;
};

class ConditionFuzzyTime : public Condition
{
public:
    using super_t = Condition;

public:
    void Serialize(Serializer& s) const
    {
        super_t::Serialize(s);
        s << static_cast<holo::uint8_t>(fuzzyTime);
    }
    void Deserialize(Deserializer& s)
    {
        super_t::Deserialize(s);
        holo::uint8_t v;
        s >> v;
        fuzzyTime = static_cast<FuzzyTime>(v);
    }

public:
    FuzzyTime fuzzyTime = FuzzyTime::Unknown;
};

class ConditionTurnDirection : public Condition
{
public:
    using super_t = Condition;

public:
    void Serialize(Serializer& s) const
    {
        super_t::Serialize(s);
        s << static_cast<holo::uint8_t>(direction);
    }
    void Deserialize(Deserializer& s)
    {
        super_t::Deserialize(s);
        holo::uint8_t v;
        s >> v;
        direction = static_cast<LaneArrowMarking>(v);
    }

public:
    LaneArrowMarking direction = LaneArrowMarking::None;
};

class ConditionVecType
{
public:
    void Serialize(Serializer& s) const
    {
        s << static_cast<holo::uint8_t>(conditions.size());
        for (std::shared_ptr<Condition> con : conditions)
        {
            switch (con->type)
            {
            case ConditionType::conditionTypeDaysOfWeek:
            {
                s << *(std::dynamic_pointer_cast<ConditionNumeric>(con));
                break;
            }
            case ConditionType::conditionTypeFuzzyTime:
            {
                s << *(std::dynamic_pointer_cast<ConditionFuzzyTime>(con));
                break;
            }
            case ConditionType::conditionTypeLoad:
            {
                s << *(std::dynamic_pointer_cast<ConditionLoad>(con));
                break;
            }
            case ConditionType::conditionTypeTimeOfDay:
            {
                s << *(std::dynamic_pointer_cast<ConditionTimeOfDay>(con));
                break;
            }
            case ConditionType::conditionTypeTurnDirection:
            {
                s << *(std::dynamic_pointer_cast<ConditionTurnDirection>(con));
                break;
            }
            case ConditionType::conditionTypeVehicle:
            {
                s << *(std::dynamic_pointer_cast<ConditionVehicleType>(con));
                break;
            }
            case ConditionType::conditionTypeWeather:
            {
                s << *(std::dynamic_pointer_cast<ConditionWeather>(con));
                break;
            }
            case ConditionType::conditionTypeWeight:
            {
                s << *(std::dynamic_pointer_cast<ConditionNumeric>(con));
                break;
            }
            case ConditionType::conditionTypeUnknown:
            {
                LOG(WARNING) << "ConditionalRestrictionProfileValue::Serialize failed,"
                             << "    Condition.type=" << static_cast<holo::uint8_t>(con->type);
                break;
            }
            }
        }
    }
    void Deserialize(Deserializer& s)
    {
        holo::uint8_t count = 0;
        s >> count;
        for (holo::uint8_t i = 0; i < count; i++)
        {
            Condition cond;
            s >> cond;
            switch (cond.type)
            {
            case ConditionType::conditionTypeDaysOfWeek:
            {
                std::shared_ptr<ConditionNumeric> cond_ptr = std::make_shared<ConditionNumeric>();
                cond_ptr->type                             = cond.type;
                cond_ptr->appliesToEgoVehicle              = cond.appliesToEgoVehicle;
                s >> cond_ptr->value;
                this->conditions.push_back(cond_ptr);
                break;
            }
            case ConditionType::conditionTypeFuzzyTime:
            {
                std::shared_ptr<ConditionFuzzyTime> cond_ptr = std::make_shared<ConditionFuzzyTime>();
                cond_ptr->type                               = cond.type;
                cond_ptr->appliesToEgoVehicle                = cond.appliesToEgoVehicle;
                holo::uint8_t v;
                s >> v;
                cond_ptr->fuzzyTime = static_cast<FuzzyTime>(v);
                this->conditions.push_back(cond_ptr);
                break;
            }
            case ConditionType::conditionTypeLoad:
            {
                std::shared_ptr<ConditionLoad> cond_ptr = std::make_shared<ConditionLoad>();
                cond_ptr->type                          = cond.type;
                cond_ptr->appliesToEgoVehicle           = cond.appliesToEgoVehicle;
                holo::uint8_t v;
                s >> v;
                cond_ptr->value = static_cast<Load>(v);
                this->conditions.push_back(cond_ptr);
                break;
            }
            case ConditionType::conditionTypeTimeOfDay:
            {
                std::shared_ptr<ConditionTimeOfDay> cond_ptr = std::make_shared<ConditionTimeOfDay>();
                cond_ptr->type                               = cond.type;
                cond_ptr->appliesToEgoVehicle                = cond.appliesToEgoVehicle;
                s >> cond_ptr->startMinutes >> cond_ptr->endMinutes;
                this->conditions.push_back(cond_ptr);
                break;
            }
            case ConditionType::conditionTypeTurnDirection:
            {
                std::shared_ptr<ConditionTurnDirection> cond_ptr = std::make_shared<ConditionTurnDirection>();
                cond_ptr->type                                   = cond.type;
                cond_ptr->appliesToEgoVehicle                    = cond.appliesToEgoVehicle;
                holo::uint8_t v;
                s >> v;
                cond_ptr->direction = static_cast<LaneArrowMarking>(v);
                this->conditions.push_back(cond_ptr);
                break;
            }
            case ConditionType::conditionTypeVehicle:
            {
                std::shared_ptr<ConditionVehicleType> cond_ptr = std::make_shared<ConditionVehicleType>();
                cond_ptr->type                                 = cond.type;
                cond_ptr->appliesToEgoVehicle                  = cond.appliesToEgoVehicle;
                s >> cond_ptr->vehicleTypeMask;
                this->conditions.push_back(cond_ptr);
                break;
            }
            case ConditionType::conditionTypeWeather:
            {
                std::shared_ptr<ConditionWeather> cond_ptr = std::make_shared<ConditionWeather>();
                cond_ptr->type                             = cond.type;
                cond_ptr->appliesToEgoVehicle              = cond.appliesToEgoVehicle;
                holo::uint8_t v;
                s >> v;
                cond_ptr->weather = static_cast<Weather>(v);
                this->conditions.push_back(cond_ptr);
                break;
            }
            case ConditionType::conditionTypeWeight:
            {
                std::shared_ptr<ConditionNumeric> cond_ptr = std::make_shared<ConditionNumeric>();
                cond_ptr->type                             = cond.type;
                cond_ptr->appliesToEgoVehicle              = cond.appliesToEgoVehicle;
                s >> cond_ptr->value;
                this->conditions.push_back(cond_ptr);
                break;
            }
            case ConditionType::conditionTypeUnknown:
            {
                LOG(WARNING) << "ConditionalRestrictionProfileValue::Serialize failed,"
                             << "    Condition.type=" << static_cast<holo::uint8_t>(cond.type);
                break;
            }
            }
        }
    }

public:
    std::vector<std::shared_ptr<Condition>> conditions;
};

class ConditionalRestrictionProfileValue : public ProfileValue
{
public:
    void Serialize(Serializer& s) const
    {
        ConditionVecType vec;
        vec.conditions.insert(vec.conditions.begin(), conditions.begin(), conditions.end());
        s << allowed << vec;
    }
    void Deserialize(Deserializer& s)
    {
        ConditionVecType vec;
        s >> allowed >> vec;
        conditions.insert(conditions.begin(), vec.conditions.begin(), vec.conditions.end());
    }

public:
    holo::bool_t allowed = false;
    std::vector<std::shared_ptr<Condition>> conditions;
};

using AccessRestrictionProfileValue     = ConditionalRestrictionProfileValue;
using OvertakingRestrictionProfileValue = ConditionalRestrictionProfileValue;

class SurfaceConditionProfileValue : public ProfileValue
{
public:
    void Serialize(Serializer& s) const
    {
        s << static_cast<holo::uint8_t>(general) << static_cast<holo::uint8_t>(surface);
    }
    void Deserialize(Deserializer& s)
    {
        holo::uint8_t v1;
        holo::uint8_t v2;
        s >> v1 >> v2;
        general = static_cast<Quality>(v1);
        surface = static_cast<SurfaceCondition>(v2);
    }

public:
    Quality general          = Quality::Unknown;
    SurfaceCondition surface = SurfaceCondition::Unknown;
};

class TrafficSignValue : public ProfileValue
{
public:
    void Serialize(Serializer& s) const
    {
        ConditionVecType vec;
        vec.conditions.insert(vec.conditions.begin(), panels.begin(), panels.end());
        s << static_cast<holo::uint8_t>(type) << value << location << shift << distance << length
          << static_cast<holo::uint8_t>(vms) << vec;
    }
    void Deserialize(Deserializer& s)
    {
        holo::uint8_t v1;
        holo::uint8_t v2;
        ConditionVecType vec;
        s >> v1 >> value >> location >> shift >> distance >> length >> v2;
        type = static_cast<SignType>(v1);
        vms  = static_cast<YesNoUnknown>(v2);
        panels.insert(panels.begin(), vec.conditions.begin(), vec.conditions.end());
    }

public:
    SignType type             = SignType::Unknown;
    holo::uint32_t value      = 0;
    SignLocationMask location = 0;
    holo::int32_t shift       = 0;
    Distance distance         = 0;
    Distance length           = 0;
    YesNoUnknown vms          = YesNoUnknown::Unknown;
    std::vector<std::shared_ptr<Condition>> panels;
};

class TrafficLightProfileValue : public ProfileValue
{
public:
    void Serialize(Serializer& s) const
    {
        s << static_cast<holo::uint8_t>(longitudinalPosition) << static_cast<holo::uint8_t>(lateralPosition)
          << cycleTime << static_cast<holo::uint8_t>(currentState) << static_cast<holo::uint8_t>(turnOnRedAllowed)
          << position << boundingBox;
    }
    void Deserialize(Deserializer& s)
    {
        holo::uint8_t v1;
        holo::uint8_t v2;
        holo::uint8_t v3;
        holo::uint8_t v4;
        s >> v1 >> v2 >> cycleTime >> v3 >> v4 >> position >> boundingBox;
        longitudinalPosition = static_cast<TrafficLightLongitudinalPosition>(v1);
        lateralPosition      = static_cast<LateralPosition>(v2);
        currentState         = static_cast<TrafficLightState>(v3);
        turnOnRedAllowed     = static_cast<YesNoUnknown>(v4);
    }

public:
    TrafficLightLongitudinalPosition longitudinalPosition = TrafficLightLongitudinalPosition::Unknown;
    LateralPosition lateralPosition                       = LateralPosition::Unknown;
    holo::float64_t cycleTime                             = 0;
    TrafficLightState currentState                        = TrafficLightState::Unknown;
    YesNoUnknown turnOnRedAllowed                         = YesNoUnknown::Unknown;
    Vector position;
    Vector boundingBox;
};

class Speed
{
public:
    Speed()
    {
    }
    ~Speed()
    {
    }

public:
    void Serialize(Serializer& s) const
    {
        s << static_cast<holo::uint8_t>(value) << static_cast<holo::uint8_t>(unit);
    }
    void Deserialize(Deserializer& s)
    {
        holo::uint8_t v;
        s >> value >> v;
        unit = static_cast<UnitOfSpeed>(v);
    }

public:
    void PrintDebugInfo()
    {
        LOG(INFO) << "Speed info, value=" << static_cast<holo::uint16_t>(value)
                  << " unit=" << (unit == v3_1_1::UnitOfSpeed::KpH ? "Kph" : "Mph");
    }
    
public:
    holo::uint8_t value = 0;
    UnitOfSpeed unit    = UnitOfSpeed::KpH;
};

class SpeedProfileValue : public ProfileValue
{
public:
    SpeedProfileValue()
    {
    }
    ~SpeedProfileValue()
    {
    }

public:
    void Serialize(Serializer& s) const
    {
        s << value;
    }
    void Deserialize(Deserializer& s)
    {
        s >> value;
    }

public:
    Speed value;
};

using AverageSpeedProfileValue = SpeedProfileValue;
using FlowSpeedProfileValue    = SpeedProfileValue;

class EffectiveSpeedLimitValue : public ProfileValue
{
public:
    void Serialize(Serializer& s) const
    {
        s << value << static_cast<holo::uint8_t>(type);
    }
    void Deserialize(Deserializer& s)
    {
        holo::uint8_t v;
        s >> value >> v;
        type = static_cast<EffectiveSpeedLimitType>(v);
    }

public:
    Speed value;
    EffectiveSpeedLimitType type = EffectiveSpeedLimitType::Unknown;
};

class ExtendedSpeedLimitValue : public ProfileValue
{
public:
    void Serialize(Serializer& s) const
    {
        ConditionVecType vec;
        vec.conditions.insert(vec.conditions.begin(), conditions.begin(), conditions.end());
        s << value << static_cast<holo::uint8_t>(source) << vec;
    }
    void Deserialize(Deserializer& s)
    {
        holo::uint8_t v;
        ConditionVecType vec;
        s >> value >> v >> vec;
        source = static_cast<SpeedLimitSource>(v);
        conditions.insert(conditions.begin(), vec.conditions.begin(), vec.conditions.end());
    }

public:
    Speed value;
    SpeedLimitSource source = SpeedLimitSource::Unknown;
    std::vector<std::shared_ptr<Condition>> conditions;
};

class LocationObjectValue : public ProfileValue
{
public:
    void Serialize(Serializer& s) const
    {
        s << static_cast<holo::uint8_t>(type) << lateralOffset << absolutePosition;
    }
    void Deserialize(Deserializer& s)
    {
        holo::uint8_t v;
        s >> v >> lateralOffset >> absolutePosition;
        type = static_cast<LocationObjectType>(v);
    }

public:
    LocationObjectType type     = LocationObjectType::GuidePost;
    holo::int32_t lateralOffset = 0;
    WGS84Point absolutePosition;
};

class OffsetFloatEntry
{
public:
    OffsetFloatEntry()
    {
    }
    ~OffsetFloatEntry()
    {
    }

public:
    void Serialize(Serializer& s) const
    {
        s << offset << value;
    }
    void Deserialize(Deserializer& s)
    {
        s >> offset >> value;
    }

public:
    void PrintDebugInfo(std::size_t index = 0)
    {
        LOG(INFO) << "OffsetFloatEntry info, index=" << index + 1 
                  << " offset=" << offset
                  << " value=" << value * 1e-5;
    }

public:
    Offset offset         = 0;
    holo::float32_t value = 0;
};

class OffsetFloatProfileValue : public ProfileValue
{
public:
    OffsetFloatProfileValue()
    {
    }
    ~OffsetFloatProfileValue()
    {
    }

public:
    void Serialize(Serializer& s) const
    {
        s << entries;
    }
    void Deserialize(Deserializer& s)
    {
        s >> entries;
    }

public:
    std::vector<OffsetFloatEntry> entries;
};

using CurvatureProfileValue = OffsetFloatProfileValue;
using SlopeProfileValue     = OffsetFloatProfileValue;

class VehiclePosition : public WGS84Point
{
public:
    using super_t = WGS84Point;

public:
    VehiclePosition()
    {
    }
    ~VehiclePosition()
    {
    }

public:
    void Serialize(Serializer& s) const
    {
        super_t::Serialize(s);
        s << timestamp << heading;
    }
    void Deserialize(Deserializer& s)
    {
        super_t::Deserialize(s);
        s >> timestamp >> heading;
    }

public:
    Timestamp timestamp     = 0;
    holo::float32_t heading = 0;
};

class AbsoluteVehiclePositionProfileValue : public ProfileValue
{
public:
    AbsoluteVehiclePositionProfileValue()
    {
    }
    ~AbsoluteVehiclePositionProfileValue()
    {
    }

public:
    void Serialize(Serializer& s) const
    {
        s << position;
    }
    void Deserialize(Deserializer& s)
    {
        s >> position;
    }

public:
    VehiclePosition position;
};

class NodeArm
{
public:
    void Serialize(Serializer& s) const
    {
        s << static_cast<holo::uint32_t>(subPath) << static_cast<holo::float32_t>(probability)
          << static_cast<holo::float32_t>(turnAngle) << static_cast<holo::bool_t>(isComplexIntersection)
          << static_cast<holo::uint8_t>(rightOfWay);
    }
    void Deserialize(Deserializer& s)
    {
        holo::uint8_t right_of_way;
        s >> subPath >> probability >> turnAngle >> isComplexIntersection >> right_of_way;
        rightOfWay = static_cast<RightOfWay>(right_of_way);
    }
public:
    void PrintDebugInfo(std::size_t index = 0)
    {
        LOG(INFO) << "NodeArm info, index=" << index + 1 << " subpath=" <<subPath
                  << " turnAngle=" << turnAngle << " probability=" << probability
                  << " rightOfWay=" << static_cast<holo::uint16_t>(rightOfWay)
                  << " isComplexIntersection=" << isComplexIntersection;
    }

public:
    PathId subPath                     = 0;
    Probability probability            = 0;
    Angle turnAngle                    = 0;
    holo::bool_t isComplexIntersection = false;
    RightOfWay rightOfWay              = RightOfWay::Unknown;
};

class NodeProfileValue : public ProfileValue
{
public:
    NodeProfileValue()
    {
    }
    ~NodeProfileValue()
    {
    }

public:
    void Serialize(Serializer& s) const
    {
        s << arms;
    }
    void Deserialize(Deserializer& s)
    {
        s >> arms;
    }

public:
    std::vector<NodeArm> arms;
};

class LaneInfo
{
public:
    void Serialize(Serializer& s) const
    {
        s << laneNumber 
          << static_cast<holo::uint8_t>(direction) 
          << static_cast<holo::uint8_t>(transition) 
          << types
          << centerline 
          << leftBoundary 
          << rightBoundary;
    }
    void Deserialize(Deserializer& s)
    {
        holo::uint8_t v1;
        holo::uint8_t v2;
        s >> laneNumber 
          >> v1 
          >> v2 
          >> types 
          >> centerline 
          >> leftBoundary 
          >> rightBoundary;
        direction  = static_cast<RelativeDirection>(v1);
        transition = static_cast<LaneTransition>(v2);
    }

public:
    void PrintDebugInfo(std::size_t index = 0)
    {
        LOG(INFO) << "LaneInfo info, index=" << index + 1
                  << " laneNumber=" << static_cast<holo::uint16_t>(laneNumber)
                  << " types=" << types
                  << " direction=" << static_cast<holo::uint16_t>(direction)
                  << " transition=" << static_cast<holo::uint16_t>(transition)
                  << " centerline=" << centerline
                  << " left_bound=" << leftBoundary
                  << " right_bound=" << rightBoundary;
    }

public:
    holo::uint8_t laneNumber    = 0;
    RelativeDirection direction = RelativeDirection::None;
    LaneTransition transition   = LaneTransition::None;
    holo::uint32_t types        = 0;
    LinearObjId centerline      = 0;
    LinearObjId leftBoundary    = 0;
    LinearObjId rightBoundary   = 0;
};

class LaneModelValue : public ProfileValue
{
public:
    LaneModelValue()
    {
    }
    ~LaneModelValue()
    {
    }

public:
    void Serialize(Serializer& s) const
    {
        s << laneInfos;
    }
    void Deserialize(Deserializer& s)
    {
        s >> laneInfos;
        totalNumberOfLanes = laneInfos.size();
    }

public:
    holo::uint8_t totalNumberOfLanes = 0;
    std::vector<LaneInfo> laneInfos;
};

class LaneConnectivityPair
{
public:
    LaneConnectivityPair()
    {
    }
    ~LaneConnectivityPair()
    {
    }

public:
    void Serialize(Serializer& s) const
    {
        s << initialLaneNumber << initialPath << newLaneNumber << newPath;
    }
    void Deserialize(Deserializer& s)
    {
        s >> initialLaneNumber >> initialPath >> newLaneNumber >> newPath;
    }

public:
    void PrintDebugInfo(std::size_t index = 0)
    {
        LOG(INFO) << "LaneConnectivity info, index=" << index + 1 
                    << " init_path=" << initialPath
                    << " init_lane=" << static_cast<holo::uint16_t>(initialLaneNumber)
                    << " new_path=" << newPath
                    << " new_lane=" << static_cast<holo::uint16_t>(newLaneNumber);
    }

public:
    holo::uint8_t initialLaneNumber = 0;
    PathId initialPath              = 0;
    holo::uint8_t newLaneNumber     = 0;
    PathId newPath                  = 0;
};

class LaneConnectivityValue : public ProfileValue
{
public:
    LaneConnectivityValue()
    {
    }
    ~LaneConnectivityValue()
    {
    }

public:
    void Serialize(Serializer& s) const
    {
        s << connectivityPairs;
    }
    void Deserialize(Deserializer& s)
    {
        s >> connectivityPairs;
    }

public:
    std::vector<LaneConnectivityPair> connectivityPairs;
};

class LinearObject
{
public:
    LinearObject()
    {
    }
    ~LinearObject()
    {
    }

public:
    void Serialize(Serializer& s) const
    {
        s << static_cast<uint32_t>(id) << static_cast<holo::uint8_t>(type) << static_cast<holo::uint8_t>(marking)
          << static_cast<holo::uint8_t>(colour);
    }
    void Deserialize(Deserializer& s)
    {
        holo::uint8_t v1;
        holo::uint8_t v2;
        holo::uint8_t v3;
        s >> id >> v1 >> v2 >> v3;
        type    = static_cast<LinearObjectType>(v1);
        marking = static_cast<LineMarking>(v2);
        colour  = static_cast<LineMarkingColour>(v3);
    }

public:
    void PrintDebugInfo(std::size_t index = 0)
    {
        LOG(INFO) << "LinearObj info, index=" << index + 1 << " id=" << id
                  << " type=" << static_cast<holo::uint16_t>(type)
                  << " marking=" << static_cast<holo::uint16_t>(marking)
                  << " color=" << static_cast<holo::uint16_t>(colour);
    }
public:
    LinearObjId id           = 0;
    LinearObjectType type    = LinearObjectType::LaneMarking;
    LineMarking marking      = LineMarking::None;
    LineMarkingColour colour = LineMarkingColour::None;
};

class LinearObjectDefinitionValue : public ProfileValue
{
public:
    LinearObjectDefinitionValue()
    {
    }
    ~LinearObjectDefinitionValue()
    {
    }

public:
    void Serialize(Serializer& s) const
    {
        s << linearObjects;
    }
    void Deserialize(Deserializer& s)
    {
        s >> linearObjects;
    }

public:
    std::vector<LinearObject> linearObjects;
};

class Curve
{
public:
    void Serialize(Serializer& s) const
    {
        s << static_cast<holo::uint8_t>(type) << points;
    }
    void Deserialize(Deserializer& s)
    {
        holo::uint8_t v;
        s >> v >> points;
        type = static_cast<CurveType>(v);
    }

public:
    void PrintDebugInfo()
    {
        LOG(INFO) << "Curve info, type=" << static_cast<holo::uint16_t>(type);
        for(std::size_t j = 0;j<points.size();j++)
        {
            LOG(INFO) << "Point info, index=" << j + 1 << " point_count=" << points.size();
            points[j].PrintDebugINfo();
        }
    }

public:
    CurveType type = CurveType::NotPresent;
    std::vector<WGS84Point> points;
};

class LineGeometry
{
public:
    LineGeometry()
    {
    }
    ~LineGeometry()
    {
    }

public:
    void Serialize(Serializer& s) const
    {
        s << static_cast<uint32_t>(idLine) << geometry;
    }
    void Deserialize(Deserializer& s)
    {
        s >> idLine >> geometry;
    }

public:
    void PrintDebugInfo(std::size_t index = 0)
    {
        LOG(INFO) << "LaneGeometry info, index=" << index + 1 << " id=" << idLine;
        geometry.PrintDebugInfo();
    }

public:
    LinearObjId idLine = 0;
    Curve geometry;
};

class LanesGeometryProfileValue : public ProfileValue
{
public:
    LanesGeometryProfileValue()
    {
    }
    ~LanesGeometryProfileValue()
    {
    }

public:
    void Serialize(Serializer& s) const
    {
        s << geometries;
    }
    void Deserialize(Deserializer& s)
    {
        s >> geometries;
    }

public:
    std::vector<LineGeometry> geometries;
};

class RoadGeometryProfileValue : public ProfileValue
{
public:
    RoadGeometryProfileValue()
    {
    }
    ~RoadGeometryProfileValue()
    {
    }

public:
    void Serialize(Serializer& s) const
    {
        s << roadCenterline;
    }
    void Deserialize(Deserializer& s)
    {
        s >> roadCenterline;
    }

public:
    Curve roadCenterline;
};

} // namespace v3_1_1
} // namespace adasis
} // namespace map
} // namespace holo

#endif /* HOLO_MAP_ADASIS_V3_PROFILEVALUE_H_ */