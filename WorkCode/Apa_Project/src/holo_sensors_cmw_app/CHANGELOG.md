# Changelog

## [Unreleased]
- high-performace camera drivers

## [0.9.0] - 2022-04-29
### Added

### Changed
- manage mdc versions by number

### Deprecated

### Removed

### Fixed
- image Optimize & support run on mdc610 v0228
- timediff util bug
- some lidar bugs
- +virtual before several base class destuctors
- add a delay in novatel to fix bad timestamp

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
- mdc610 V1231 support
- me8 driver
- speed limit sign output with mpc2
- rs bpearl lidar driver
- pandar128 lidar driver
- virtual camera
- option to choose time source of rsm1
- lidar converter app support rtfbag
- rsm1 support lidarscan

### Changed
- lidar converter app support assign extrinsic

### Deprecated

### Removed

### Fixed

## [0.6.0] - 2021-12-31
### Added
- image decoder cli

### Changed
- mdc610 camera driver impl

### Deprecated

### Removed

### Fixed
- bugs in image encoders and decoders

## [0.5.0] - 2021-12-11
### Added
- cache in image decoder
- use v4l2 timestamp in camera driver

### Changed
- shm-base lidar driver
- mdc610 camera driver impl

### Deprecated

### Removed
- vehicle proxy app

### Fixed

## [0.4.0] - 2021-09-14
### Added
- holo logger dependency
- livox hap lidar driver
- mdc610 v830 supported
- mdc610 timestamp management in sensor drivers
- judge compile options automatically

### Changed
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
- mdc610 dvpp encoder (not so good for now)
- lz4 lib dependency
- google glog denpendecy

### Changed
- cuda-based encoder and encoder
- image packet data add reasonable frame_type

### Deprecated
### Removed
### Fixed
- some depreacetd code
- livox timesync data construction

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
