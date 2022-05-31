# Changelog

## [Unreleased]

## [0.8.0] - 2022-04-27
### Added
- built in holo bag in pps_wrapper
- GH02 AppMgr for mdc_cm_wrapper
### Changed
- pps default config template 
- topic_id to topicid in PPS_CFG_EX_STRU struct
### Deprecated
### Removed
### Fixed
- pps error info for debuging
- support for EM in mdc_cm_wrapper
- support cm reader to modify buffer size
- support x86-ubuntu1804 platform for mdc_cm_wrapper
- identify cm reader and  cm writer
- scripts for launch CM node
- support parse mdc instanceSpecifiers

## [0.7.0] - 2022-03-28
### Added
- memcpy triats to pps wrapper
- default traits to pps wrappter
### Changed
- pps default config template 
### Deprecated
### Removed
### Fixed
- ros bus default message traits member type
- opendds default message traits member type
- ros wrapper topic name error

## [0.6.2] - 2022-03-01
### Added
### Changed
- pps default config template 
### Deprecated
### Removed
### Fixed

## [0.6.1] - 2022-01-07
### Added
### Changed
### Deprecated
### Removed
### Fixed
- opendds and dds micro lambda function capture reader and waitset when set callback
- pps add/delete reader function
- pps bus callback memory access error at exit 

## [0.6.0] - 2021-12-10

### Added
- dds_micro reader/writer qos config
- pps wrapper
- Enable API to all bus types
- dds micro wrapper waitset mode
- opendds wrapper waitset mode
### Changed
### Deprecated
### Removed
### Fixed

## [0.5.1] - 2021-10-25

### Added
### Changed
### Deprecated
### Removed
- mdc cm config files
### Fixed
- dds micro default datareader/datawriter qos

## [0.5.0] - 2021-09-08

### Added
- dds micro config file loader
- shmem support for dds_micro
- assertion to serialization traits
- HMIRouteIndex serviceinterface for MDC610 config

### Changed

### Deprecated

### Removed

### Fixed
- adjust microdds buffer size from 300000 to 8192
- change default max participant id
- dds micro delete writer/reader coredump

## [0.4.0] - 2021-07-08

### Added
- cmw v2.1. Change Reader/Writer second template parameter to Traits type
- Opendds wrapper throws exception with human readable string on error.
- dds_micro wrapper
- MDC610 CM wrapper for gh02 project

### Changed
- Enable opendds BuiltInTopic by default
- Use udp ros by default
- Use Opendds 3.16 as default version

### Deprecated

### Removed
- opendds/ros add reader/writer with renamed typename api

### Fixed
- ros wrapper memory leak
- opendds idl generation cmake function
- Bus namespace insertion error
- Ros wrapper delete reader/writer error
- CMW wrapper add brideg executable bug

## [0.3.0] - 2021-02-02

### Added
- UMB wrapper
- KeypointObject and ImaeObjects
- 

### Changed
- Change project layout.
- Disable holo_cmw v1 by default

### Deprecated
- holo_cmw v1

### Removed
- Ibeo message

### Fixed
- Lots of conversion bugs
- Ros wrapper reader/writer point to invlid address bug


## [0.2.0] - 2020-08-02

### Added
- PerceptionAbility attribute to obstacle list
- Winterfell opendds idl messages
- Lane scene opendds idl message
- Weather opendds idl message
- Conversion functions for road frame2
- AppStatus opendds idl message
- Opendds wrapper project
- Ros wrapper project

### Changed
- Opendds configure file default opendds udp buffer size changed to 10MB
- holo_cmw use node_name argument as opendds domain_id.


### Deprecated

### Removed

### Fixed
- MessageType/ValueType conversion for PlanningParam
