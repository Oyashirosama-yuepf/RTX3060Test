# Changelog

## [Unreleased]
- high-performace camera drivers

## [0.9.0] - 2022-04-29
### Added
- lidar type description
- raw lidar packet struct

### Changed

### Deprecated

### Removed
- sys/io.h in libply.h

### Fixed
- reconnect when tcp socket closed
- some lidar bug
- image Optimize & support run on mdc610 v0228 
- +virtual before several base class destuctors

## [0.8.0] - 2022-04-02
### Added
- more lidars driver
- image driver for calibration
- sensors proxy node
- sen-yun cameras support

### Changed
- driver can resize output image

### Deprecated

### Removed

### Fixed
- small image driver/encoder/decoder bugs

## [0.7.0] - 2022-03-01
### Added
- me8 driver
- speed limit sign output with mpc2
- mdc610 V1130 & V1231 support
- rs bpearl lidar driver
- pandar128 lidar driver
- virtual camera
- option to choose time source of rsm1

### Changed

### Deprecated

### Removed

### Fixed
- some bugs in lidar scan
- some bugs in image encoders and decoders
- some bugs with qac check

## [0.6.0] - 2021-12-31
### Added
- cache in udp interface

### Changed

### Deprecated

### Removed

### Fixed
- some bugs in image encoders and decoders

## [0.5.0] - 2021-12-11
### Added
- rs ruby lidar driver
- mdc610 V830-T2 support
- sensor interface library
- mdc610 utils
- lidar scan structure

### Changed
- add more config parameters in tda4 image encoder
- use v4l2 timestamp in camera driver

### Deprecated

### Removed
- vehicle proxy module

### Fixed
- memory leakage in mdc610 decoder
- timestamp mismatch in mdc610 decoder

## [0.4.0] - 2021-10-28
### Added
- holo logger dependency
- livox hap lidar driver
- tian-zhun xavier machine supportted
- mdc610 v830 supported
- mdc610 timestamp management in sensor drivers
- lidar point cloud ipc
- judge compile options automatically

### Changed
- lidar drivers output scan at a group of fixed time points
- lidar converters filter out all-0s points
- adapt to new version control command struct

### Deprecated

### Removed
- google glog dependency

### Fixed
- robosense m1 lidar converter may drop some points
- mdc610 image encoder and decoder bugs

## [0.3.0] - 2021-09-14
### Added
- rsm1 lidar driver
- lz4 lib dependency
- google glog denpendecy
- a simple interface in lidar converters

### Changed
- image packet data add reasonable frame_type

### Deprecated

### Removed

### Fixed
- some depreacetd code


## [0.2.0] - 2021-08-03
### Added
- vlp lidar converter

### Changed
- image decoder base is no longer a templated class
- pandar40 driver supports single/dual return mode
- livox compress mode supported

### Deprecated

### Removed

### Fixed
- novatel driver reduces data packet loss

## [0.1.0] - 2021-07-08
### Added
- first release version

### Changed

### Deprecated

### Removed

### Fixed
