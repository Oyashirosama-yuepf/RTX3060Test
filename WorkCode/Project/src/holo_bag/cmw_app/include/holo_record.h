/**
 * @file holo_record.h
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file is the header of the holo record app
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLO_CMW_APPS_HOLO_RECORD_H_
#define _HOLO_CMW_APPS_HOLO_RECORD_H_

#include <cmw_wrapper/cmw_bus.h>
#include <holo/bag/base/serialized_bag_message.h>
#include <holo/bag/base/sys_version_metadata.h>
#include <holo/bag/base/topic_metadata.h>
#include <holo/bag/interface/writer.h>
#include <holo/common/image.h>
#include <holo/sensors/camera/encoder/image_encoder.h>
#include <holo/sensors/camera/image_structure.h>
#include <holo/serialization/serialization.h>
#include <holo_thread_pool.h>

namespace holo_cmw
{
#if !(!defined(CMW_WRAPPER_ENABLE_ROS) && !defined(CMW_WRAPPER_ENABLE_OPENDDS) && defined(CMW_WRAPPER_ENABLE_UMB))
#define _MESSAGE_TYPE_ROS_AND_OPENDDS_
#endif
class HoloRecord
{
    using CmwBus            = cmw_wrapper::BusType;
    using BusType           = CmwBus;
    using TopicMapManager   = std::map<std::string, holo::bag::TopicMetadata>;
    using SerializedDataPtr = std::shared_ptr<holo::bag::SerializedBagMessage>;

    using SensorID  = ::holo::common::SensorId;
    using IpcType   = holo::sensors::camera::ImageIpc;
    using TencBase  = ::holo::sensors::camera::ImageEncoderBase;
    using EnCodeMap = std::map<std::string, std::pair<std::shared_ptr<IpcType>, std::shared_ptr<TencBase>>>;

public:
    HoloRecord(int argc, char** argv, const std::string& name, holo::uint64_t domain_id = 0, bool encode = false,
               holo::uint16_t extract_frame = 3, const std::string& encode_type = "RGB",
               const std::string& image_type  = "H264");
    ~HoloRecord();
    bool SetUp(const ::holo::uint64_t split_size, const ::holo::uint64_t split_time, const std::string& file_name = "", bool is_split = false);
    void Record();

private:
    enum TencType{RgbToH264 ,RgbToH265, Nv12ToH264, Nv12ToH265, BgrToH264, BgrToH265};

private:
    bool splitBag();
    bool createSplitBag();
    bool loadConfigFile(const std::string& config_file, const ::holo::uint64_t split_size, const ::holo::uint64_t split_time);
    bool initSubscriber();
    bool createTopics();
    bool initWriter(const std::string& file_name, bool is_split = false);
    bool storeRunningParams(const std::string& path);
    bool collectRunningParams(const std::string& path, std::vector<std::shared_ptr<holo::bag::ParamMetadata>>& params);
    bool storeDataVersion();
    bool storeSoftwareVersion();
    bool storeHardwareVersion();
    bool collectLibraryVersion(std::vector<std::shared_ptr<holo::bag::SysVersionMetadata>>& sys_version);
    bool createSerializedBagMessage(const std::string& topic_name, SerializedDataPtr msg);

    void onMessage(holo::uint8_t const* buffer, size_t size, const holo::bag::TopicMetadata& tmd);
    void showSubInfo();
    void imageEncoderHandler(const holo::sensors::camera::ImagePacket& encoded_data, std::string topic_name);

    bool initEncodeMap(std::string topic_name, ::holo::uint32_t sensor_id_data);
    void encodeImage();
    std::pair<::holo::uint32_t, ::holo::uint32_t> analyInfo(holo::uint8_t const* buffer, size_t size);
    void setTencType(const std::string encode_type, const std::string image_type);
    std::shared_ptr<HoloRecord::TencBase> getTencObject(HoloRecord::TencType tenc_type, ::holo::uint32_t cols, 
                                                        ::holo::uint32_t rows, uint32_t fps);

    bool isUmbMessage();
    std::string createEncodeTopicByInfo(std::string info_topic_name);

    void recodeReset(std::shared_ptr<holo::bag::Writer>& sub_record);

private:

    std::shared_ptr<BusType> bus_ptr_;

    holo::bool_t          active_record_;
    holo::bool_t          encode_;
    volatile holo::bool_t spliting_;
    std::string           bag_base_name_;
    holo::uint16_t        bag_base_counter_;
    TopicMapManager       topic_map_{};

    std::shared_ptr<holo::bag::Writer> record_ptr_;
    std::shared_ptr<holo::bag::Writer> record_ptr_feature_;
    holo::bag::StorageOptions          options_;

    EnCodeMap                       encode_map_{};
    std::shared_ptr<HoloThreadPool> encode_thread_pool_;
    std::queue<std::string>         encode_topic_queue_;
    holo::uint16_t                  extract_frame_frequency_;
    TencType                        tenc_type_;
};

}  // namespace holo_cmw

#endif  //_HOLO_CMW_APPS_HOLO_RECORD_H_
