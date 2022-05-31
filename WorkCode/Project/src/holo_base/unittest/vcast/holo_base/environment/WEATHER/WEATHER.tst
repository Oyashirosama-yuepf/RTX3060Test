-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : WEATHER
-- Unit(s) Under Test: weather
--
-- Script Features
TEST.SCRIPT_FEATURE:C_DIRECT_ARRAY_INDEXING
TEST.SCRIPT_FEATURE:CPP_CLASS_OBJECT_REVISION
TEST.SCRIPT_FEATURE:MULTIPLE_UUT_SUPPORT
TEST.SCRIPT_FEATURE:REMOVED_CL_PREFIX
TEST.SCRIPT_FEATURE:MIXED_CASE_NAMES
TEST.SCRIPT_FEATURE:STANDARD_SPACING_R2
TEST.SCRIPT_FEATURE:OVERLOADED_CONST_SUPPORT
TEST.SCRIPT_FEATURE:UNDERSCORE_NULLPTR
TEST.SCRIPT_FEATURE:FULL_PARAMETER_TYPES
TEST.SCRIPT_FEATURE:STRUCT_DTOR_ADDS_POINTER
TEST.SCRIPT_FEATURE:STRUCT_FIELD_CTOR_ADDS_POINTER
TEST.SCRIPT_FEATURE:STATIC_HEADER_FUNCS_IN_UUTS
TEST.SCRIPT_FEATURE:VCAST_MAIN_NOT_RENAMED
--

-- Unit: weather

-- Subprogram: holo::common::Weather::Deserialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::Deserialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.END

-- Subprogram: holo::common::Weather::GetAllWeather

-- Test Case: BASIS-PATH-001
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::GetAllWeather
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.cloudy_:1
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.rainfall_:0
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.snowfall_:1
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.foggy_vis_:0
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.sandy_vis_:1
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.reserved_:0
TEST.EXPECTED:weather.holo::common::Weather::GetAllWeather.return:65601
TEST.END

-- Subprogram: holo::common::Weather::GetFoggyVisibility

-- Test Case: BASIS-PATH-001
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::GetFoggyVisibility
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.foggy_vis_:5
TEST.EXPECTED:weather.holo::common::Weather::GetFoggyVisibility.return:175
TEST.END

-- Subprogram: holo::common::Weather::GetRainFall

-- Test Case: BASIS-PATH-001
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::GetRainFall
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.rainfall_:5
TEST.EXPECTED:weather.holo::common::Weather::GetRainFall.return:45
TEST.END

-- Subprogram: holo::common::Weather::GetSandyVisibility

-- Test Case: BASIS-PATH-001
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::GetSandyVisibility
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.sandy_vis_:5
TEST.EXPECTED:weather.holo::common::Weather::GetSandyVisibility.return:175
TEST.END

-- Subprogram: holo::common::Weather::GetSerializedSize

-- Test Case: BASIS-PATH-001
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::GetSerializedSize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.EXPECTED:weather.holo::common::Weather::GetSerializedSize.return:12
TEST.END

-- Subprogram: holo::common::Weather::GetSnowFall

-- Test Case: BASIS-PATH-001
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::GetSnowFall
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.snowfall_:5
TEST.EXPECTED:weather.holo::common::Weather::GetSnowFall.return:5
TEST.END

-- Subprogram: holo::common::Weather::GetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::GetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.timestamp_.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:weather.holo::common::Weather::GetTimestamp.return.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:weather.holo::common::Weather::GetTimestamp.return.holo::common::details::Timestamp.nsec_:2
TEST.END

-- Subprogram: holo::common::Weather::IsCloudy

-- Test Case: BASIS-PATH-001
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::IsCloudy
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.cloudy_:1
TEST.EXPECTED:weather.holo::common::Weather::IsCloudy.return:true
TEST.END

-- Subprogram: holo::common::Weather::IsFoggy

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::IsFoggy
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) ((weather_category_).foggy_vis_ * holo::common::Weather::VIS_MAPPED_PARAM < holo::common::Weather::VISBILITY_THRESHOLD) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 1
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.foggy_vis_:5
TEST.EXPECTED:weather.holo::common::Weather::IsFoggy.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::IsFoggy
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) ((weather_category_).foggy_vis_ * holo::common::Weather::VIS_MAPPED_PARAM < holo::common::Weather::VISBILITY_THRESHOLD) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 1
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.EXPECTED:weather.holo::common::Weather::IsFoggy.return:false
TEST.END

-- Subprogram: holo::common::Weather::IsRainy

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::IsRainy
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) ((weather_category_).rainfall_ > 0U) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (weather_category_).rainfall_ in branch 1
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.rainfall_:5
TEST.EXPECTED:weather.holo::common::Weather::IsRainy.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::IsRainy
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) ((weather_category_).rainfall_ > 0U) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (weather_category_).rainfall_ in branch 1
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.EXPECTED:weather.holo::common::Weather::IsRainy.return:false
TEST.END

-- Subprogram: holo::common::Weather::IsSandy

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::IsSandy
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) ((weather_category_).sandy_vis_ * holo::common::Weather::VIS_MAPPED_PARAM < holo::common::Weather::VISBILITY_THRESHOLD) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 1
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.foggy_vis_:5
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.sandy_vis_:5
TEST.EXPECTED:weather.holo::common::Weather::IsSandy.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::IsSandy
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) ((weather_category_).sandy_vis_ * holo::common::Weather::VIS_MAPPED_PARAM < holo::common::Weather::VISBILITY_THRESHOLD) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 1
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.EXPECTED:weather.holo::common::Weather::IsSandy.return:false
TEST.END

-- Subprogram: holo::common::Weather::IsSnowy

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::IsSnowy
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) ((weather_category_).snowfall_ > 0U) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (weather_category_).snowfall_ in branch 1
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.snowfall_:5
TEST.EXPECTED:weather.holo::common::Weather::IsSnowy.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::IsSnowy
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) ((weather_category_).snowfall_ > 0U) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (weather_category_).snowfall_ in branch 1
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.EXPECTED:weather.holo::common::Weather::IsSnowy.return:false
TEST.END

-- Subprogram: holo::common::Weather::Serialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::Serialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.END

-- Subprogram: holo::common::Weather::SetAllWeather

-- Test Case: BASIS-PATH-001
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::SetAllWeather
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.VALUE:weather.holo::common::Weather::SetAllWeather.value:65601
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.timestamp_.holo::common::details::Timestamp.sec_:0
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.timestamp_.holo::common::details::Timestamp.nsec_:0
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.cloudy_:1
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.rainfall_:0
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.snowfall_:1
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.foggy_vis_:0
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.sandy_vis_:1
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.reserved_:0
TEST.END

-- Subprogram: holo::common::Weather::SetCloudy

-- Test Case: BASIS-PATH-001
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::SetCloudy
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.VALUE:weather.holo::common::Weather::SetCloudy.flag:true
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.cloudy_:1
TEST.END

-- Subprogram: holo::common::Weather::SetFoggyVisibility

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::SetFoggyVisibility
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (value / holo::common::Weather::VIS_MAPPED_PARAM > (0x1f)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 1
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.VALUE:weather.holo::common::Weather::SetFoggyVisibility.value:1086
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.foggy_vis_:16#1F#
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::SetFoggyVisibility
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (value / holo::common::Weather::VIS_MAPPED_PARAM > (0x1f)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 1
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.VALUE:weather.holo::common::Weather::SetFoggyVisibility.value:16#3#
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.foggy_vis_:0
TEST.END

-- Subprogram: holo::common::Weather::SetRainFall

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::SetRainFall
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (value / holo::common::Weather::RAINY_MAPPED_PARAM > (0x1f)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 1
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.VALUE:weather.holo::common::Weather::SetRainFall.value:300
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.rainfall_:16#1F#
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::SetRainFall
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (value / holo::common::Weather::RAINY_MAPPED_PARAM > (0x1f)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 1
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.VALUE:weather.holo::common::Weather::SetRainFall.value:200
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.rainfall_:16#16#
TEST.END

-- Subprogram: holo::common::Weather::SetSandyVisibility

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::SetSandyVisibility
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (value / holo::common::Weather::VIS_MAPPED_PARAM > (0x1f)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 1
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.VALUE:weather.holo::common::Weather::SetSandyVisibility.value:1090
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.sandy_vis_:16#1F#
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::SetSandyVisibility
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (value / holo::common::Weather::VIS_MAPPED_PARAM > (0x1f)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 1
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.VALUE:weather.holo::common::Weather::SetSandyVisibility.value:16#3#
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.sandy_vis_:16#0#
TEST.END

-- Subprogram: holo::common::Weather::SetSnowFall

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::SetSnowFall
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (value > (0x1f)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.VALUE:weather.holo::common::Weather::SetSnowFall.value:16#2F#
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.snowfall_:16#1F#
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::SetSnowFall
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (value > (0x1f)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.VALUE:weather.holo::common::Weather::SetSnowFall.value:16#F#
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.snowfall_:16#F#
TEST.END

-- Subprogram: holo::common::Weather::SetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::SetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.VALUE:weather.holo::common::Weather::SetTimestamp.timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:weather.holo::common::Weather::SetTimestamp.timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:weather.holo::common::Weather::SetTimestamp.timestamp.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.timestamp_.holo::common::details::Timestamp.nsec_:2
TEST.END

-- Subprogram: holo::common::Weather::Weather()

-- Test Case: BASIS-PATH-001
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::Weather()
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.timestamp_.holo::common::details::Timestamp.sec_:0
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.timestamp_.holo::common::details::Timestamp.nsec_:0
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.cloudy_:0
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.rainfall_:0
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.snowfall_:0
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.foggy_vis_:16#1F#
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.sandy_vis_:16#1F#
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.reserved_:0
TEST.END

-- Subprogram: holo::common::Weather::Weather(holo::uint32_t)

-- Test Case: BASIS-PATH-001
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::Weather(holo::uint32_t)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:weather.holo::common::Weather::Weather(holo::uint32_t).value:16#1CF8F1#
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.timestamp_.holo::common::details::Timestamp.sec_:0
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.timestamp_.holo::common::details::Timestamp.nsec_:0
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.cloudy_:1
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.rainfall_:24
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.snowfall_:3
TEST.EXPECTED:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.reserved_:0
TEST.END

-- Subprogram: holo::common::Weather::operator holo::uint32_t

-- Test Case: BASIS-PATH-001
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::operator holo::uint32_t
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.timestamp_.holo::common::details::Timestamp.sec_:0
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.timestamp_.holo::common::details::Timestamp.nsec_:0
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.cloudy_:1
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.rainfall_:0
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.snowfall_:1
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.foggy_vis_:0
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.sandy_vis_:1
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.weather_category_.reserved_:0
TEST.EXPECTED:weather.holo::common::Weather::operator holo::uint32_t.return:65601
TEST.END

-- Subprogram: holo::common::Weather::operator=

-- Test Case: BASIS-PATH-001
TEST.UNIT:weather
TEST.SUBPROGRAM:holo::common::Weather::operator=
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:weather.<<GLOBAL>>.(cl).holo::common::Weather.holo::common::Weather.<<constructor>>.Weather().<<call>>:0
TEST.VALUE:weather.holo::common::Weather::operator=.value:65601
TEST.EXPECTED:weather.holo::common::Weather::operator=.return.holo::common::Weather.timestamp_.holo::common::details::Timestamp.sec_:0
TEST.EXPECTED:weather.holo::common::Weather::operator=.return.holo::common::Weather.timestamp_.holo::common::details::Timestamp.nsec_:0
TEST.EXPECTED:weather.holo::common::Weather::operator=.return.holo::common::Weather.weather_category_.cloudy_:1
TEST.EXPECTED:weather.holo::common::Weather::operator=.return.holo::common::Weather.weather_category_.rainfall_:0
TEST.EXPECTED:weather.holo::common::Weather::operator=.return.holo::common::Weather.weather_category_.snowfall_:1
TEST.EXPECTED:weather.holo::common::Weather::operator=.return.holo::common::Weather.weather_category_.foggy_vis_:0
TEST.EXPECTED:weather.holo::common::Weather::operator=.return.holo::common::Weather.weather_category_.sandy_vis_:1
TEST.EXPECTED:weather.holo::common::Weather::operator=.return.holo::common::Weather.weather_category_.reserved_:0
TEST.END
