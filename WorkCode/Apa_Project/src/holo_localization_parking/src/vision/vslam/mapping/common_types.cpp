/*!
 * \brief common types class implementation file in visual mapping
 * \author Feng. Li, lifeng@holomatic.com
 * \date Mar-13-2020
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

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
FramesDatabase::FramesDatabase() : is_from_multi_database_merging_(false)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FramesDatabase::FramesDatabase(const std::vector<FramesDatabase>& frames_databases)
  : is_from_multi_database_merging_(true)
{
    for (uint64_t i = 0; i < frames_databases.size(); i++)
    {
        for (const auto frame : frames_databases[i].GetAllFrames())
        {
            if (frames_database_.count(frame.first))
            {
                LOG(ERROR) << "FramesDatabase --- frame " << frame.first << " has already existed in this database.\n";
                throw std::runtime_error("FramesDatabase --- construct framesdatabase failed.");
            }

            frames_database_.emplace(frame.first, frame.second);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FramesDatabase::AddFrame(const Frame& frame)
{
    frames_database_.emplace(frame.frame_id, frame);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FramesDatabase::Exists(const uint64_t frame_id) const
{
    return frames_database_.count(frame_id);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Frame& FramesDatabase::GetFrame(const uint64_t frame_id) const
{
    if (!Exists(frame_id))
    {
        LOG(ERROR) << "FramesDatabase --- frame " << frame_id << " does not exist in this database.\n";
        throw std::runtime_error("FramesDatabase --- query frame failed. you should call Exists() first to check if "
                                 "exist in this database.");
    }

    return frames_database_.at(frame_id);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint64_t FramesDatabase::Size() const
{
    return frames_database_.size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int16_t FramesDatabase::GetDescriptorDimension() const
{
    if (IsEmpty())
    {
        return -1;
    }

    const auto& frame = frames_database_.begin()->second;

    if (frame.multi_camera_data.empty())
    {
        return -1;
    }

    const auto& desc = frame.multi_camera_data.at(0).features.at(0).optional_descriptor;

    if (!desc)
    {
        return -1;
    }

    return desc->cols;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FramesDatabase::IsEmpty() const
{
    return frames_database_.empty();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const std::map<uint64_t, Frame>& FramesDatabase::GetAllFrames() const
{
    return frames_database_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::map<uint64_t, Frame>& FramesDatabase::GetAllFrames()
{
    return frames_database_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FramesDatabase::IsFromMultiDatabaseMerging() const
{
    return is_from_multi_database_merging_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TracksDatabase::TracksDatabase()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TracksDatabase::TracksDatabase(const std::vector<TracksDatabase>& tracks_databases)
{
    for (uint64_t i = 0; i < tracks_databases.size(); i++)
    {
        for (const auto& track : tracks_databases[i].GetAllTracks())
        {
            if (tracks_database_.count(track.first))
            {
                LOG(ERROR) << "TracksDatabase --- track " << track.first << " has already existed in this database.\n";
                throw std::runtime_error("TracksDatabase --- construct tracksdatabase failed.");
            }
            tracks_database_.emplace(track.first, track.second);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TracksDatabase::AddFeatureTrack(const FeatureTrack& track)
{
    const auto& landmark = track.GetLandmark();

    if (!landmark)
    {
        return;
    }

    if (Exists(landmark->Id()))
    {
        throw std::runtime_error(
            "TracksDatabase --- failed to add track. given track already exists in this database, you "
            "may need function UpdateFeatureTrack().");
    }

    tracks_database_.emplace(landmark->Id(), track);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TracksDatabase::AddFeatureTracks(const std::vector<FeatureTrack>& tracks)
{
    for (const auto& track : tracks)
    {
        AddFeatureTrack(track);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TracksDatabase::UpdateFeatureTrack(const uint64_t landmark_id, uint64_t frame_id, const Feature& feature)
{
    if (!Exists(landmark_id))
    {
        throw std::runtime_error(
            "TracksDatabase --- update track failed. given track does not exists in this database, you "
            "should call AddFeatureTrack first.");
    }

    tracks_database_.at(landmark_id).AddNewestMeasurement(frame_id, feature);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TracksDatabase::UpdateFeatureTrack(const uint64_t landmark_id, const FeatureTrack& track)
{
    if (!Exists(landmark_id))
    {
        throw std::runtime_error(
            "TracksDatabase --- update track failed. given track does not exists in this database, you "
            "should call AddFeatureTrack first.");
    }

    Erase(landmark_id);
    tracks_database_.emplace(landmark_id, track);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TracksDatabase::Erase(const uint64_t landmark_id)
{
    if (!Exists(landmark_id))
    {
        return;
    }

    tracks_database_.erase(landmark_id);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TracksDatabase::Exists(const uint64_t landmark_id) const
{
    return tracks_database_.count(landmark_id);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const FeatureTrack& TracksDatabase::GetTrack(const uint64_t landmark_id) const
{
    if (!Exists(landmark_id))
    {
        LOG(ERROR) << "FramesDatabase --- landmark " << landmark_id << " does not exist in this database.\n";
        throw std::runtime_error("FramesDatabase --- query track failed. you should call Exists() first to check if "
                                 "exist in this database.");
    }

    return tracks_database_.at(landmark_id);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int16_t TracksDatabase::GetDescriptorDimension() const
{
    if (IsEmpty())
    {
        return -1;
    }

    const auto& track = tracks_database_.begin()->second;
    const auto& desc  = track.OldestMeasurement().second.begin()->second.optional_descriptor;
    if (!desc)
    {
        return -1;
    }

    return desc->cols;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint64_t TracksDatabase::Size() const
{
    return tracks_database_.size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const std::unordered_map<uint64_t, FeatureTrack>& TracksDatabase::GetAllTracks() const
{
    return tracks_database_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TracksDatabase::IsEmpty() const
{
    return tracks_database_.empty();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ParkingSlotTracksDatabase::ParkingSlotTracksDatabase()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ParkingSlotTracksDatabase::ParkingSlotTracksDatabase(const ParkingSlotTracksDatabase& parking_slot_tracks_database)
{
    parking_slot_tracks_database_ = parking_slot_tracks_database.GetAllParkingSlotTracks();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParkingSlotTracksDatabase::AddParkingSlotTrack(const semantic::ParkingSlotTrack& parking_slot_track)
{
    parking_slot_tracks_database_.push_back(parking_slot_track);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParkingSlotTracksDatabase::AddParkingSlotTracks(const std::vector<semantic::ParkingSlotTrack>& parking_slot_tracks)
{
    parking_slot_tracks_database_.insert(parking_slot_tracks_database_.end(), parking_slot_tracks.begin(),
                                         parking_slot_tracks.end());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint64_t ParkingSlotTracksDatabase::Size() const
{
    return parking_slot_tracks_database_.size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const std::vector<semantic::ParkingSlotTrack>& ParkingSlotTracksDatabase::GetAllParkingSlotTracks() const
{
    return parking_slot_tracks_database_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ParkingSlotTracksDatabase::IsEmpty() const
{
    return parking_slot_tracks_database_.empty();
}

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo