#include <glog/logging.h>
#include <holo/parking/map/parking_map_io.h>
#include <fstream>

namespace holo
{
namespace parking
{
namespace map
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ParkingMapIO::LoadPrebuildMap(const std::string& map_file_name, Map& map)
{
    std::ifstream fin(map_file_name);

    if (!fin)
    {
        LOG(ERROR) << "LocalizationVSLAM --- LoadMap, could not open " << map_file_name;
        return false;
    }

    // total landmarks number
    uint64_t landmark_num;
    fin.read((char*)&landmark_num, sizeof(uint64_t));

    // descriptor dimension
    uint16_t descriptor_dimension;
    fin.read((char*)&descriptor_dimension, sizeof(uint16_t));

    // read data one by one
    map.reserve(landmark_num);

    for (uint64_t i = 0; i < landmark_num; i++)
    {
        // load descriptor
        cv::Mat descriptor;
        descriptor.create(1, descriptor_dimension, CV_32FC1);

        for (uint16_t j = 0; j < descriptor_dimension; j++)
        {
            fin.read((char*)&descriptor.at<float32_t>(0, j), sizeof(float32_t));
        }

        // load position
        Scalar x, y, z;
        fin.read((char*)&x, sizeof(Scalar));
        fin.read((char*)&y, sizeof(Scalar));
        fin.read((char*)&z, sizeof(Scalar));
        Point3 position(x, y, z);

        // load direction
        Scalar direction_x, direction_y, direction_z;
        fin.read((char*)&direction_x, sizeof(Scalar));
        fin.read((char*)&direction_y, sizeof(Scalar));
        fin.read((char*)&direction_z, sizeof(Scalar));
        Vector3 direction(direction_x, direction_y, direction_z);

        // load reference camera pose
        Scalar t_x, t_y, t_z, q_w, q_x, q_y, q_z;
        fin.read((char*)&t_x, sizeof(Scalar));
        fin.read((char*)&t_y, sizeof(Scalar));
        fin.read((char*)&t_z, sizeof(Scalar));
        fin.read((char*)&q_w, sizeof(Scalar));
        fin.read((char*)&q_x, sizeof(Scalar));
        fin.read((char*)&q_y, sizeof(Scalar));
        fin.read((char*)&q_z, sizeof(Scalar));
        Pose3 pose(Rot3(Quaternion(q_w, q_x, q_y, q_z).ToRotationMatrix()), Point3(t_x, t_y, t_z));

        // load reference frame id
        uint64_t reference_frame_id;
        fin.read((char*)&reference_frame_id, sizeof(uint64_t));

        // load score
        Scalar score;
        fin.read((char*)&score, sizeof(Scalar));

        // load covariance
        Matrix3 covariance;
        fin.read((char*)&(covariance(0, 0)), sizeof(Scalar));
        fin.read((char*)&(covariance(0, 1)), sizeof(Scalar));
        fin.read((char*)&(covariance(0, 2)), sizeof(Scalar));

        fin.read((char*)&(covariance(1, 0)), sizeof(Scalar));
        fin.read((char*)&(covariance(1, 1)), sizeof(Scalar));
        fin.read((char*)&(covariance(1, 2)), sizeof(Scalar));

        fin.read((char*)&(covariance(2, 0)), sizeof(Scalar));
        fin.read((char*)&(covariance(2, 1)), sizeof(Scalar));
        fin.read((char*)&(covariance(2, 2)), sizeof(Scalar));

        // load semantic label
        SemanticLabel semantic_label;
        fin.read((char*)&semantic_label, sizeof(SemanticLabel));

        // load life long states
        uint64_t states_num;
        fin.read((char*)&states_num, sizeof(uint64_t));
        std::vector<MapPointState> states;
        states.reserve(states_num);

        for (uint64_t i = 0; i < states_num; i++)
        {
            MapPointState state;
            fin.read((char*)&state, sizeof(MapPointState));
            states.push_back(state);
        }
        states.push_back(MapPointState::CANDIDATE);

        // load remember rate
        Scalar remember_rate;
        fin.read((char*)&remember_rate, sizeof(Scalar));

        // create new map point
        MapPoint mp;
        mp.descriptor         = descriptor;
        mp.position           = position;
        mp.direction          = direction;
        mp.covariance         = covariance;
        mp.reference_pose     = pose;
        mp.reference_frame_id = reference_frame_id;
        mp.score              = score;
        mp.life_long_states   = states;
        mp.remember_rate      = remember_rate;
        mp.semantic_label     = semantic_label;

        map.emplace_back(std::make_shared<MapPoint>(mp));
    }
    fin.close();

    if (!map.size())
    {
        LOG(ERROR) << "ParkingMapIO --- LoadMap: the total landmarks num is zero, there must be something wrong !!!";
        return false;
    }
    LOG(INFO) << " ParkingMapIO --- LoadMap: successfully load prebuilt map, total landmarks num: " << map.size()
              << "\n";
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ParkingMapIO::LoadKeyFramesDatabase(const std::string& keyframes_file_name, KeyFramesDatabase& keyframes_database)
{
    LOG(INFO) << "ParkingMapIO --- trying to load frames from: " << keyframes_file_name << "\n";
    std::ifstream fin(keyframes_file_name);

    if (!fin)
    {
        LOG(ERROR) << "ParkingMapIO --- LoadKeyFramesDatabase: could not open " << keyframes_file_name;
        return false;
    }

    uint16_t frame_num;
    fin.read((char*)&frame_num, sizeof(uint16_t));

    uint16_t descriptor_dimension;
    fin.read((char*)&descriptor_dimension, sizeof(uint16_t));

    for (uint16_t i = 0; i < frame_num; i++)
    {
        uint64_t frame_id;
        fin.read((char*)&frame_id, sizeof(uint64_t));

        uint16_t camera_number;
        fin.read((char*)&camera_number, sizeof(uint16_t));

        // read pose
        Pose3 vehicle_pose;
        {
            float64_t x, y, z, q_w, q_x, q_y, q_z;
            fin.read((char*)&x, sizeof(Scalar));
            fin.read((char*)&y, sizeof(Scalar));
            fin.read((char*)&z, sizeof(Scalar));
            fin.read((char*)&q_w, sizeof(Scalar));
            fin.read((char*)&q_x, sizeof(Scalar));
            fin.read((char*)&q_y, sizeof(Scalar));
            fin.read((char*)&q_z, sizeof(Scalar));
            Vector3    translation(x, y, z);
            Quaternion rotation(q_w, q_x, q_y, q_z);
            vehicle_pose = Pose3(Rot3(rotation.ToRotationMatrix()), Point3(translation));
        }
        KeyFrame keyframe(frame_id, vehicle_pose, camera_number);

        for (uint16_t camera_index = 0; camera_index < camera_number; camera_index++)
        {
            uint16_t camera_id;
            fin.read((char*)&camera_id, sizeof(uint16_t));

            float64_t x, y, z, q_w, q_x, q_y, q_z;
            fin.read((char*)&x, sizeof(Scalar));
            fin.read((char*)&y, sizeof(Scalar));
            fin.read((char*)&z, sizeof(Scalar));
            fin.read((char*)&q_w, sizeof(Scalar));
            fin.read((char*)&q_x, sizeof(Scalar));
            fin.read((char*)&q_y, sizeof(Scalar));
            fin.read((char*)&q_z, sizeof(Scalar));
            Vector3    translation(x, y, z);
            Quaternion rotation(q_w, q_x, q_y, q_z);
            Pose3      pose(Rot3(rotation.ToRotationMatrix()), Point3(translation));

            uint16_t feature_num;
            fin.read((char*)&feature_num, sizeof(uint16_t));

            Features             features;
            std::vector<int64_t> associated_landmarks;
            std::vector<Point3>  mappoints;
            features.reserve(feature_num);
            associated_landmarks.reserve(feature_num);
            mappoints.reserve(feature_num);

            for (uint16_t j = 0; j < feature_num; j++)
            {
                Scalar pt_x, pt_y;
                fin.read((char*)&pt_x, sizeof(Scalar));
                fin.read((char*)&pt_y, sizeof(Scalar));

                Scalar ptn_x, ptn_y, ptn_z;
                fin.read((char*)&ptn_x, sizeof(Scalar));
                fin.read((char*)&ptn_y, sizeof(Scalar));
                fin.read((char*)&ptn_z, sizeof(Scalar));

                // read semantic label
                SemanticLabel semantic_label;
                fin.read((char*)&semantic_label, sizeof(SemanticLabel));

                cv::Mat descriptors;
                descriptors.create(1, descriptor_dimension, CV_32FC1);

                for (uint16_t k = 0; k < descriptor_dimension; k++)
                {
                    fin.read((char*)&descriptors.at<float32_t>(0, k), sizeof(float32_t));
                }

                Scalar score;
                fin.read((char*)&score, sizeof(Scalar));

                int64_t lm_id;
                fin.read((char*)&lm_id, sizeof(int64_t));

                features.emplace_back(cv::Point2f(pt_x, pt_y), descriptors, Point3(ptn_x, ptn_y, ptn_z), camera_id,
                                      score, semantic_label);
                associated_landmarks.emplace_back(lm_id);

                Scalar ptw_x, ptw_y, ptw_z;
                fin.read((char*)&ptw_x, sizeof(Scalar));
                fin.read((char*)&ptw_y, sizeof(Scalar));
                fin.read((char*)&ptw_z, sizeof(Scalar));
                mappoints.emplace_back(ptw_x, ptw_y, ptw_z);
            }

            keyframe.multi_camera_data[camera_id].pose                 = pose;
            keyframe.multi_camera_data[camera_id].features             = features;
            keyframe.multi_camera_data[camera_id].associated_landmarks = associated_landmarks;
            keyframe.multi_camera_data[camera_id].mappoints            = mappoints;
        }

        keyframes_database.emplace(keyframe.frame_id, keyframe);
    }

    if (!keyframes_database.size())
    {
        LOG(ERROR) << "ParkingMapIO --- LoadKeyFramesDatabase: the total keyframe's num is zero, there must be "
                      "something wrong !!!";
        return false;
    }

    LOG(INFO) << "ParkingMapIO --- LoadKeyFramesDatabase: load keyframe done. total frames: "
              << keyframes_database.size();
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ParkingMapIO::LoadParkingSlotDatabase(const std::string& parking_slot_file_name,
                                           ParkingSlotData&   parking_slot_data)
{
    std::vector<holo::common::ParkingSlot> parking_slot_database;
    std::ifstream                          fin(parking_slot_file_name);

    if (!fin)
    {
        LOG(ERROR) << "MapDatabaseManager --- LoadParkingSlotDatabase, could not open " << parking_slot_file_name;
        return false;
    }

    // total parking slot number
    uint64_t slot_num;
    fin.read((char*)&slot_num, sizeof(uint64_t));

    for (uint64_t i = 0; i < slot_num; ++i)
    {
        holo::common::ParkingSlot parking_slot;

        uint64_t slot_id;
        fin.read((char*)&slot_id, sizeof(uint64_t));
        parking_slot.id = slot_id;

        bool_t is_valid;
        fin.read((char*)&is_valid, sizeof(bool_t));
        parking_slot.is_valid = is_valid;

        Scalar vertex0_x, vertex0_y, vertex0_z;
        fin.read((char*)&vertex0_x, sizeof(Scalar));
        fin.read((char*)&vertex0_y, sizeof(Scalar));
        fin.read((char*)&vertex0_z, sizeof(Scalar));
        parking_slot.vertices[0] = Point3(vertex0_x, vertex0_y, vertex0_z);

        Scalar vertex1_x, vertex1_y, vertex1_z;
        fin.read((char*)&vertex1_x, sizeof(Scalar));
        fin.read((char*)&vertex1_y, sizeof(Scalar));
        fin.read((char*)&vertex1_z, sizeof(Scalar));
        parking_slot.vertices[1] = Point3(vertex1_x, vertex1_y, vertex1_z);

        bool_t is_rear_vertex_available;
        fin.read((char*)&is_rear_vertex_available, sizeof(bool_t));
        parking_slot.is_center_vertex_available = is_rear_vertex_available;
        if (is_rear_vertex_available)
        {
            Scalar vertex2_x, vertex2_y, vertex2_z;
            fin.read((char*)&vertex2_x, sizeof(Scalar));
            fin.read((char*)&vertex2_y, sizeof(Scalar));
            fin.read((char*)&vertex2_z, sizeof(Scalar));
            parking_slot.vertices[2] = Point3(vertex2_x, vertex2_y, vertex2_z);

            Scalar vertex3_x, vertex3_y, vertex3_z;
            fin.read((char*)&vertex3_x, sizeof(Scalar));
            fin.read((char*)&vertex3_y, sizeof(Scalar));
            fin.read((char*)&vertex3_z, sizeof(Scalar));
            parking_slot.vertices[3] = Point3(vertex3_x, vertex3_y, vertex3_z);
        }

        parking_slot_database.push_back(parking_slot);
    }
    parking_slot_data.parking_slot_database = parking_slot_database;

    bool_t is_geted_target_parking_slot;
    fin.read((char*)&is_geted_target_parking_slot, sizeof(bool_t));

    if (is_geted_target_parking_slot)
    {
        uint64_t target_parking_slot_id;
        fin.read((char*)&target_parking_slot_id, sizeof(uint64_t));
        parking_slot_data.target_parking_slot_id = target_parking_slot_id;
    }
    else
    {
        fin.close();
        LOG(ERROR) << "MapDatabaseManager --- LoadParkingSlotDatabase,  can't get target parking slot id";
        return false;
    }

    fin.close();
    LOG(INFO) << " ParkingMapIO --- successfully load parking slot map, total parking slots num: " << slot_num << "\n";
    return true;
}

}  // namespace map
}  // namespace parking
}  // namespace holo
