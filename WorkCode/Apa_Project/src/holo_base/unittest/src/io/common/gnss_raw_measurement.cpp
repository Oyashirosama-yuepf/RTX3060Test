
#include <holo/common/gnss_raw_measurement.h>
#include <holo/io/common/gnss_raw_measurement.h>

template struct YAML::convert<holo::common::GnssRawMeasurement::RawMeasurementBlock>;
