
#include <holo/sensors/lidar/livox/livox_driver.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <holo/sensors/utils/livox_crc.h>

namespace holo
{
namespace sensors
{
namespace livox
{
void LivoxDriverBase::generateHandshakePacket(uint16_t seq, uint8_t* data, uint32_t& len, const std::string& host_ip,
                                              uint16_t data_port, uint16_t cmd_port)
{
    data[0] = LIVOX_START_BYTE;
    data[1] = LIVOX_PROTOCOL_VERSION;

    data[4] = 0x00;
    (void)std::memcpy(data + 5, &seq, 2);

    data[9]  = 0x00;
    data[10] = 0x01;

    std::istringstream ss(host_ip);
    uint8_t            digit;
    for (uint8_t i = 0; i < 4; i++)
    {
        std::string sub_str;
        (void)std::getline(ss, sub_str, '.');
        digit        = std::stoi(sub_str);
        data[11 + i] = digit;
    }

    uint16_t tmp = 0;
    tmp          = data_port;
    (void)std::memcpy(data + 15, &tmp, 2);
    tmp = cmd_port;
    (void)std::memcpy(data + 17, &tmp, 2);

    // tmp = data_port + 1;  // imu data monitor port, not use
    // (void)std::memcpy(data + 19, &tmp, 2);

    len = 23;
    (void)std::memcpy(data + 2, &len, 2);

    uint16_t crc_16 = holo::sensors::CalcCRC16(data, 7, LIVOX_INIT_CRC16);
    (void)std::memcpy(data + 7, &crc_16, 2);

    uint32_t crc_32 = holo::sensors::CalcCRC32(data, 19, LIVOX_INIT_CRC32);
    (void)std::memcpy(data + 19, &crc_32, 4);
}

void LivoxDriverBase::generateHeartbeatPacket(uint16_t seq, uint8_t* data, uint32_t& len)
{
    data[0] = LIVOX_START_BYTE;
    data[1] = LIVOX_PROTOCOL_VERSION;

    data[4] = 0x00;
    (void)std::memcpy(data + 5, &seq, 2);

    data[9]  = 0x00;
    data[10] = 0x03;

    len = 15;
    (void)std::memcpy(data + 2, &len, 2);

    uint16_t crc_16 = holo::sensors::CalcCRC16(data, 7, LIVOX_INIT_CRC16);
    (void)std::memcpy(data + 7, &crc_16, 2);

    uint32_t crc_32 = holo::sensors::CalcCRC32(data, 11, LIVOX_INIT_CRC32);
    (void)std::memcpy(data + 11, &crc_32, 4);
}

void LivoxDriverBase::generateStartsamplingPacket(uint16_t seq, uint8_t* data, uint32_t& len)
{
    data[0] = LIVOX_START_BYTE;
    data[1] = LIVOX_PROTOCOL_VERSION;

    data[4] = 0x00;
    (void)std::memcpy(data + 5, &seq, 2);

    data[9]  = 0x00;
    data[10] = 0x04;
    data[11] = 0x01;

    len = 16;
    (void)std::memcpy(data + 2, &len, 2);

    uint16_t crc_16 = holo::sensors::CalcCRC16(data, 7, LIVOX_INIT_CRC16);
    (void)std::memcpy(data + 7, &crc_16, 2);

    uint32_t crc_32 = holo::sensors::CalcCRC32(data, 12, LIVOX_INIT_CRC32);
    (void)std::memcpy(data + 12, &crc_32, 4);
}

void LivoxDriverBase::generateUpdateUtcPacket(uint16_t seq, uint8_t* data, uint32_t& len, uint32_t s, uint32_t us)
{
    data[0] = LIVOX_START_BYTE;
    data[1] = LIVOX_PROTOCOL_VERSION;

    data[4] = 0x00;
    (void)std::memcpy(data + 5, &seq, 2);

    data[9]            = 0x01;  // cmd set: lidar
    data[10]           = 0x0A;  // cmd id: update utc sync time
    const time_t t     = s;
    struct tm*   ptime = gmtime(&t);
    data[11]           = ptime->tm_year + 1900 - 2000;  // year
    data[12]           = ptime->tm_mon + 1;             // month
    data[13]           = ptime->tm_mday;                // day
    data[14]           = ptime->tm_hour;                // hour
    us += (s % 3600) * 1e6;                             // us
    (void)std::memcpy(data + 15, &us, 4);               // us

    len = 23;
    (void)std::memcpy(data + 2, &len, 2);

    uint16_t crc_16 = holo::sensors::CalcCRC16(data, 7, LIVOX_INIT_CRC16);
    (void)std::memcpy(data + 7, &crc_16, 2);

    uint32_t crc_32 = holo::sensors::CalcCRC32(data, 19, LIVOX_INIT_CRC32);
    (void)std::memcpy(data + 19, &crc_32, 4);
}

template <typename LivoxPacketType>
LivoxDriver<LivoxPacketType>::LivoxDriver(uint32_t coord, uint32_t packet_rate, uint32_t scan_rate)
  : LivoxDriverBase()
  , packet_per_scan_(packet_rate / scan_rate)
  , duration_ns_per_scan_(holo::sensors::NSEC_PER_SEC / scan_rate)
  , time_temp_ns_(0)
  , time_temp_ns_is_useful_(false)
  , scan_callback_(nullptr)
{
    if (!LidarUtils::LidarScanRateIsValid(scan_rate))
    {
        std::ostringstream oss;
        oss << "Not supported scan rate!";
        LOG(ERROR) << oss.str();
        throw std::invalid_argument(oss.str());
    }

    scan_.SetCoordinate(coord);
    /* reserve space increased 1.5 times */
    scan_.Reserve(packet_per_scan_ * 1.5);
}

template <typename LivoxPacketType>
void LivoxDriver<LivoxPacketType>::PushPacket(const LivoxPacketType& data_packet)
{
    int64_t current_time_ns = data_packet.GetTimestamp().ToNsec();
    if (!time_temp_ns_is_useful_)
    {
        time_temp_ns_           = current_time_ns;
        time_temp_ns_is_useful_ = true;
    }

    if (scan_.Size() >= packet_per_scan_ * 1.5)
    {
        throw holo::exception::OutOfRangeException("Out of livox scan space!");
    }

    /* current time beyond the point in scan duration time */
    if ((current_time_ns / duration_ns_per_scan_) != (time_temp_ns_ / duration_ns_per_scan_))
    {
        if (scan_callback_)
        {
            scan_.SetTimestamp(scan_[0].GetTimestamp());
            scan_callback_(scan_);
        }
        scan_.Clear();
    }
    scan_.PushBack(data_packet);

    time_temp_ns_ = current_time_ns;
}

template class LivoxDriver<holo::sensors::format::LivoxPacket<48u>>;
template class LivoxDriver<holo::sensors::format::LivoxPacket<96u>>;
template class LivoxDriver<holo::sensors::format::LivoxPacket<100u>>;

}  // namespace livox
}  // namespace sensors
}  // namespace holo
