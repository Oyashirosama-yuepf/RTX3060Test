#include <holo/sensors/lidar/livox/livox_hap_driver.h>
#include <holo/sensors/utils/lidar_utils.h>
#include <holo/sensors/utils/livox_crc.h>

namespace holo
{
namespace sensors
{
namespace livox
{
void LivoxHapDriverBase::generateBroadcastDiscoveryPacket(uint16_t seq, uint8_t* data, uint32_t& len)
{
    /* data buffer too short */
    if (len < 21)
    {
        len = 0;
        return;
    }
    /* build packet */
    len = 21;
    /* sof */
    data[0] = LIVOX_HAP_START_BYTE;
    /* version */
    data[1] = LIVOX_HAP_PROTOCOL_VERSION;
    /* length */
    (void)std::memcpy(data + 2, &len, 2);
    /* cmd_type */
    (void)std::memcpy(data + 4, &LIVOX_HAP_CMD_TYPE_CMD, 2);
    /* cmd id */
    (void)std::memcpy(data + 6, &LIVOX_HAP_CMD_BROADCAST_DISCOVERY, 2);
    /* send_seq */
    (void)std::memcpy(data + 8, &seq, 2);
    /* send id */
    (void)std::memcpy(data + 10, &LIVOX_HAP_SEND_ID_CTRL0, 2);
    /* resv */
    (void)std::memcpy(data + 12, &LIVOX_HAP_RESV_DEFAULT, 2);
    /* data = NULL*/
    data[16] = 0;
    /* crc16 */
    uint16_t crc_16 = holo::sensors::CalcCRC16(data, 14, LIVOX_INIT_CRC16); /* LIVOX_INIT_CRC16 : init crc code */
    (void)std::memcpy(data + 14, &crc_16, 2);
    /* crc32 */
    uint32_t crc_32 = holo::sensors::CalcCRC32(data, 17, LIVOX_INIT_CRC32);
    (void)std::memcpy(data + 17, &crc_32, 4);
}

void LivoxHapDriverBase::generateWorkControlPacket(uint16_t seq, uint8_t* data, uint32_t& len,
                                                   const LivoxHapControlInfo& info)
{
    /* data buffer too short */
    if (len < 41)
    {
        len = 0;
        return;
    }
    /* build packet */
    len              = 41;
    uint16_t req_len = 0;
    /* sof */
    data[0] = LIVOX_HAP_START_BYTE;
    /* version */
    data[1] = LIVOX_HAP_PROTOCOL_VERSION;
    /* cmd_type */
    (void)std::memcpy(data + 4, &LIVOX_HAP_CMD_TYPE_CMD, 2);
    /* cmd id */
    (void)std::memcpy(data + 6, &LIVOX_HAP_CMD_WORK_CONTROL, 2);
    /* send_seq */
    (void)std::memcpy(data + 8, &seq, 2);
    /* send id */
    (void)std::memcpy(data + 10, &LIVOX_HAP_SEND_ID_CTRL0, 2);
    /* resv */
    (void)std::memcpy(data + 12, &LIVOX_HAP_RESV_DEFAULT, 2);

    /* data */
    /* work mode */
    LivoxHapKeyValueParam<uint8_t>* kv8 = reinterpret_cast<LivoxHapKeyValueParam<uint8_t>*>(&data[16]);
    kv8->SetValue(KEY_WORK_MODE, info.WorkMode());
    req_len += sizeof(LivoxHapKeyValueParam<uint8_t>);

    /* vehicle speed */
    LivoxHapKeyValueParam<uint32_t>* kv32 = reinterpret_cast<LivoxHapKeyValueParam<uint32_t>*>(&data[16 + req_len]);
    kv32->SetValue(KEY_VEHICLE_SPEED, info.VehicleSpeed());
    req_len += sizeof(LivoxHapKeyValueParam<uint32_t>);

    /* ev temp */
    kv32 = reinterpret_cast<LivoxHapKeyValueParam<uint32_t>*>(&data[16 + req_len]);
    kv32->SetValue(KEY_ENVIRONMENT_TEMP, info.EvTemp());

    /* length */
    (void)std::memcpy(data + 2, &len, 2);

    /* crc16 */
    uint16_t crc_16 = holo::sensors::CalcCRC16(data, 14, LIVOX_INIT_CRC16); /* LIVOX_INIT_CRC16 : init crc code */
    (void)std::memcpy(data + 14, &crc_16, 2);
    /* crc32 */
    uint32_t crc_32 = holo::sensors::CalcCRC32(data, 37, LIVOX_INIT_CRC32);
    (void)std::memcpy(data + 37, &crc_32, 4);
}

template <typename LivoxPacketType>
LivoxHapDriver<LivoxPacketType>::LivoxHapDriver(uint32_t coord, uint32_t packet_rate, uint32_t scan_rate)
  : LivoxHapDriverBase()
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
void LivoxHapDriver<LivoxPacketType>::PushPacket(const LivoxPacketType& data_packet)
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

template class LivoxHapDriver<holo::sensors::format::LivoxHapPacket<1440u>>;

}  // namespace livox
}  // namespace sensors
}  // namespace holo
