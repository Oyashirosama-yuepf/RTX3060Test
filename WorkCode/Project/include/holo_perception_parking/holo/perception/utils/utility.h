/*!
 *  \brief
 *  \author huanglihong
 *  \date Aug 10, 2017
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#ifndef HOLO_PERCEPTION_UTILS_UTILITY_H_
#define HOLO_PERCEPTION_UTILS_UTILITY_H_

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/message.h>
#include <google/protobuf/text_format.h>
#include <holo/common/extrinsic.h>
#include <holo/core/types.h>
#include <holo/geometry/point3.h>
#include <holo/geometry/pose3.h>
#include <holo/geometry/rot3.h>
#include <holo/numerics/matrix.h>
#include <holo/utils/holo_root.h>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>
#include <boost/thread/shared_lock_guard.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <numeric>
#include <string>
#include <vector>

#include "holo/geometry/angle.h"
#include "holo/perception/utils/dg_port.h"
#include <holo/perception/common/box_object.h>

namespace holo
{
namespace perception
{
class ConstDefines
{
public:
    static const float32_t kMaxFloat;
    static const Point3f   kMaxPoint3f;
    static const uint8_t   kMaxClassScore;
    static const uint32_t  kMaxTrackId;
    static const uint8_t   kImagePixelMaxValue;
};

class PltIpmPoints_bk
{
public:
    cv::Mat canvas_data;
    int     width_, height_;
    float   w_scale;
    float   h_scale;
    /**
     * @brief Construct a new Plt Ipm Points object
     *
     * @param width
     * @param height
     * @param range first (x_min y_min) second (x_max y_max)  height(x) width(y)
     */
    cv::Point2f GetPixelLocation(cv::Point2f ground_point);
    PltIpmPoints_bk(int width, int height, std::pair<cv::Point2f, cv::Point2f> range);
    void plt_img_line(cv::Point2f pt1, cv::Point2f pt2, CvScalar color = CV_RGB(255, 255, 255));
    void plt_img_points(cv::Point2f pt1, CvScalar color );
    void plt_img_text(cv::Point2f pt, std::string str, double font_scale = 1,
                      CvScalar color = CV_RGB(255, 255, 255));
    void plt_psd(std::vector<cv::Point2f> psd, int psd_id, CvScalar color);
    void plt_box(holo::geometry::Box3f box, uint32_t track_id);
};
class ProtoHelpFun
{
public:
    typedef google::protobuf::Message                  Message;
    typedef google::protobuf::io::FileInputStream      FileInputStream;
    typedef google::protobuf::io::FileOutputStream     FileOutputStream;
    typedef google::protobuf::io::ZeroCopyInputStream  ZeroCopyInputStream;
    typedef google::protobuf::io::CodedInputStream     CodedInputStream;
    typedef google::protobuf::io::ZeroCopyOutputStream ZeroCopyOutputStream;
    typedef google::protobuf::io::CodedOutputStream    CodedOutputStream;

    static const uint32_t kProtoReadBytesLimit            = std::numeric_limits<uint32_t>::max();
    static const uint32_t kProtoReadBytesWarningThreshold = 536870912;  // 512MB

    static void ReadProtoFromTextFile(const std::string& filename, google::protobuf::Message* proto);
    static void ReadProtoFromBinaryFile(const std::string& filename, google::protobuf::Message* proto);
};

/**
 * @brief if the path is an absolute path
 *
 * @param path input path
 *
 * @return bool flag
 */
extern bool IsAbsolutePath(const std::string& path);

std::string GetPerLibConfigFileAbsolutePath(const std::string& path);

using READ_LOCK  = boost::shared_lock<boost::shared_mutex>;
using WRITE_LOCK = boost::unique_lock<boost::shared_mutex>;

/// Parse string in protobuf according to delimminator, and convert into a vector
template <typename T>
std::vector<T> ParseStringAsVec(const std::string& input, const std::string& delim)
{
    std::vector<T>           output;
    std::vector<std::string> dst;
    boost::split(dst, input, boost::is_any_of(delim), boost::token_compress_on);
    for (auto& it : dst)
    {
        output.push_back(boost::lexical_cast<T>(it));
    }
    return output;
}

}  // namespace perception
}  // namespace holo

#endif  /// HOLO_PERCEPTION_UTILS_UTILITY_H_
