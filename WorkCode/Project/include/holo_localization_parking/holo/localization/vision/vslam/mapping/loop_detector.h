/*!
 * \brief loop detector class header file in vslam
 * \author Feng. Li, lifeng@holomatic.com
 * \date Mar-02-2020
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_MAPPING_LOOP_DETECTOR_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_MAPPING_LOOP_DETECTOR_H_

#ifdef HOLO_LOOP_WITH_NETVLAD
#include <holo/localization/deep/netvlad.h>
#include <holo/localization/deep/pytorch/pt_netvlad.h>
#endif
#include <holo/localization/vision/vslam/common_types.h>
#include <holo/localization/vision/vslam/mapping/common_types.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @ingroup localization
 * @brief loop detector class
 */

class LoopDetector
{
public:
    /**
     * @brief define parameters
     */
    struct Parameters
    {
#ifdef HOLO_LOOP_WITH_NETVLAD
        /// @brief define superpoint extractor parameters
        const deep::NetVlad::Parameters netvlad_params;
#endif

        /// @brief method used to query candidate loop
        const std::string loop_detection_method;

#ifdef HOLO_LOOP_WITH_NETVLAD
        /// @brief constructor
        Parameters(const deep::NetVlad::Parameters& _netvlad_params,
                   const std::string                _loop_detection_method = "byPose")
          : netvlad_params(_netvlad_params), loop_detection_method(_loop_detection_method)
        {
        }
#else
        /// @brief constructor
        Parameters(const std::string _loop_detection_method = "byPose") : loop_detection_method(_loop_detection_method)
        {
        }
#endif

        /**
         * @brief output stream parameters
         *
         * @param os std::ostream&
         * @param parameters
         * @return std::ostream&
         */
        friend std::ostream& operator<<(std::ostream& os, const Parameters& parameters)
        {
            os << "LoopDetectorParameters:"
               << "\n  loop detection method = " << parameters.loop_detection_method << "\n";
            return os;
        }

        /**
         * @brief load from yaml
         *
         * @param node
         * @return Parameters
         */
        static Parameters LoadFromYaml(const holo::yaml::Node& node);

        /**
         * @brief static example parameters for unit test
         *
         * @return Parameters
         */
        static Parameters Example();
    };

    /**
     * @brief define candidate loop frame
     */
    struct CandidatesLoop
    {
        /// @brief train frame.<frame id, camera index>
        std::vector<std::pair<uint64_t, uint16_t>> train_frames;

        /// @brief query frame.<frame id, camera index>
        std::pair<uint64_t, uint16_t> query_frame;

        /// @brief similarity score
        std::vector<Scalar> scores;
    };

    /**
     * @brief constructor
     *
     * @param parameters parameters
     * @param frames_database the frame database
     */
    LoopDetector(const Parameters& parameters, const FramesDatabase& frames_database);

    /**
     * @brief destructor
     */
    ~LoopDetector()
    {
    }

    /**
     * @brief query candidate loop into database
     *
     * @param query_frame query frame
     * @param query_camera_id query camera id in query frame
     * @param query_number number of candidate
     * @return candidate loop frames
     */
    CandidatesLoop Run(const Frame& query_frame, uint16_t query_camera_id, uint32_t query_number) const;

private:
    /**
     * @brief query candidate loop into database
     *
     * @param query_frame query frame
     * @param query_camera_id query camera id in query frame
     * @param query_number number of candidate
     * @return candidate loop frames
     */
    CandidatesLoop QueryCandidateByPose(const Frame& query_frame, uint16_t query_camera_id,
                                        uint32_t query_number) const;

#ifdef HOLO_LOOP_WITH_NETVLAD
    /**
     * @brief query candidate loop into database
     *
     * @param query_frame query frame
     * @param query_camera_id query camera id in query frame
     * @param query_number number of candidate
     * @return candidate loop frames
     */
    CandidatesLoop QueryCandidateByNetvlad(const Frame& query_frame, uint16_t query_camera_id,
                                           uint32_t query_number) const;

    /**
     * @brief create netvlad database
     * @param frames_database frames database
     */
    void CreateNetvladDatabase(const FramesDatabase& frames_database);
#endif

    /**
     * @brief preprocess the mat of image feature (include pow, reduce, expand)

     * @param image_feature_mat the original image feature mat
     * @param expand_cols the col number of mat will be expanded
     * @return  image feature mat whinch is preprocessed
     */
    cv::Mat ImageFeatureMatPreprocess(const cv::Mat& image_feature_mat, uint64_t expand_cols) const;

    /// @brief parameteres
    const Parameters parameters_;

    /// @brief frame database.
    const FramesDatabase& frames_database_;

    /// @brief netvlad features database
    cv::Mat netvlad_database_;

    /// @brief netvlad features expand database
    cv::Mat netvlad_database_expand_;

    /// @brief record frame and multi camera information to construct the bow_database_
    /// first: frame id, second: camera id
    std::vector<std::pair<uint64_t, uint16_t>> frame_id_and_camera_id_;

#ifdef HOLO_LOOP_WITH_NETVLAD
    /// @brief  netvlad_extractor
    std::shared_ptr<deep::NetVlad> netvlad_extractor_;
#endif
};  // class LoopDetector

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_MAPPING_LOOP_DETECTOR_H_
