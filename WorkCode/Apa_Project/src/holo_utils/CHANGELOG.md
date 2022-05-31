# Changelog

## [Unreleased]

## [0.8.0] - 2022-04-27
### Added
- stack trace callback to SignalHandler
- share memory block reader and writer
- Get()/Resize() tlv buffer size in pcapng module
### Changed
### Deprecated
### Removed
### Fixed
- share memory need rt library

## [0.7.0] - 2022-03-28
### Added
- SharedMemoryBlock
- SharedMemoryBlock test case
### Changed
### Deprecated
### Removed
### Fixed
- filesystem and os utils bug
- allocator.h include guard typo
- log level difference between glog and log4cplus
- hololog no terminal, no error message will be prompted

## [0.6.0] - 2022-03-01
### Added
- Configuration module
- Fixed element size allocator
- Runtime error exceptions
- OS get pid/tid/ppid API
### Changed
### Deprecated
### Removed
### Fixed
- hololog initialization and config
- serialization check_capacity bug
- pcapng epb block length errort
- hololog output pid/tid format

## [0.5.0] - 2022-01-07
### Added
- A new LockfreeQueue
- LockfreeStack
- ObjectPool
- internal FreeStack structure
### Changed
- Change the original LockfreeQueue to LockfreeCircularQueue
### Deprecated
### Removed
### Fixed
- exceptions.h compile error on qnx
- thread local object destruct problem on qnx
- Log can be written after main program exits
- Open pcapng file with mode, and write section length to file when destruct
- qac static test

## [0.4.0] - 2021-12-08
### Added
- SignalHandler
- ThreadPool
- SyncQueue
- LockfreeQueue
- cxxopt v3.0.0 header library
### Changed
### Deprecated
### Removed
### Fixed
- log pattern's time format
- qac static test
- log4cplus compile error on gcc5

## [0.3.0] - 2021-10-25
### Added
- Override glog/logging header file
- Holo log console color
- Holo log max level
- OStream and StreamBuf
- std::vector Serializer/Deserializer method
- Pcapng module
### Changed
### Deprecated
### Removed
### Fixed
- Global config did not work
- Memory leak when use null_stream
- Optimize holo log performance

## [0.2.0] - 2021-09-08
### Added
- hololog module
### Changed
### Deprecated
### Removed
### Fixed
- Deserializer Read() API type cast error
- Serializer/Deserializer void pointer and integer type arithmetic operation

## [0.1.0] - 2021-07-08
### Added
- Serialization module

### Changed

### Deprecated

### Removed

### Fixed

