#include <holo/parking/vision/point_feature_list_smb.h>
namespace holo
{
namespace parking
{
namespace vision
{
/**
 * @brief define static value
 *
 */

static const uint32_t SERIALIZED_BUF_LEN = 300000U;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PointFeatureListSMBWriter::PointFeatureListSMBWriter(const std::string& smb_name, uint16_t block_size)
  : point_feature_list_smb_writer_(smb_name), write_msg_index_(0), block_size_(block_size)
{
    point_feature_list_smb_writer_.Init(SERIALIZED_BUF_LEN, block_size);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PointFeatureListSMBWriter::~PointFeatureListSMBWriter()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::pair<PointFeaturefList_ST*, uint16_t> PointFeatureListSMBWriter::GetSMBBlockPtrAndWriterIndexToSetData()
{
    if (write_msg_index_ == block_size_)
    {
        write_msg_index_ = 0;
    }
    write_msg_index_++;
    return std::make_pair((PointFeaturefList_ST*)point_feature_list_smb_writer_.GetBlockData(write_msg_index_ - 1),
                          write_msg_index_ - 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PointFeatureListSMBReader::PointFeatureListSMBReader(const std::string& smb_name)
  : point_feature_list_smb_reader_(smb_name)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PointFeatureListSMBReader::~PointFeatureListSMBReader()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PointFeaturefList_ST* PointFeatureListSMBReader::GetPointFeatureListDataPtr(uint16_t read_msg_index)
{
    return (PointFeaturefList_ST*)point_feature_list_smb_reader_.GetBlockData(read_msg_index);
}
}  // namespace vision
}  // namespace parking
}  // namespace holo