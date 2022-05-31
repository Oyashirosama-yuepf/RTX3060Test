/*!
 *  \brief
 *  \author pengcheng (pengcheng@holomatic.com)
 *  \date 2019-07-03
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_HOLO_PERCEPTION_COMMON_KF_TRACK_HPP
#define HOLO_HOLO_PERCEPTION_COMMON_KF_TRACK_HPP

#include <holo/perception2/common/kf_track.h>
#include <holo/obstacle/shape/obstacle_shape_box.h>
#include <holo/perception2/utils/utility.h>
#include <cmath>

namespace holo
{
namespace perception
{

template<typename Scale>
void KFTrackBase<Scale>::Init(size_t kf_state_num, size_t kf_measure_num, size_t kf_control_num)
{
    kf_filter_ptr_ = std::make_shared<cv::KalmanFilter>(kf_state_num, kf_measure_num, kf_control_num, CV_32F);
}

template<typename Scale>
void KFTrackBase<Scale>::SetKalmanStatusMatrix(const float32_t* mat, size_t size, KalmanStatus status)
{
    switch (status)
    {
    case KalmanStatus::STATE_PRE:
        memcpy(kf_filter_ptr_->statePre.data, mat, size);
        break;
    case KalmanStatus::STATE_POST:
        memcpy(kf_filter_ptr_->statePost.data, mat, size);
        break;
    case KalmanStatus::TRANSITION_MATRIX:
        memcpy(kf_filter_ptr_->transitionMatrix.data, mat, size);
        break;
    case KalmanStatus::CONTROL_MATRIX:
        memcpy(kf_filter_ptr_->controlMatrix.data, mat, size);
        break;
    case KalmanStatus::MEASUREMENT_MATRIX:
        memcpy(kf_filter_ptr_->measurementMatrix.data, mat, size);
        break;
    case KalmanStatus::PROCESS_NOISE_COV:
        memcpy(kf_filter_ptr_->processNoiseCov.data, mat, size);
        break;
    case KalmanStatus::MEASUREMENT_NOISE_COV:
        memcpy(kf_filter_ptr_->measurementNoiseCov.data, mat, size);
        break;
    case KalmanStatus::ERROR_COV_PRE:
        memcpy(kf_filter_ptr_->errorCovPre.data, mat, size);
        break;
    case KalmanStatus::GAIN:
        memcpy(kf_filter_ptr_->gain.data, mat, size);
        break;
    case KalmanStatus::ERROR_COV_POST:
        memcpy(kf_filter_ptr_->errorCovPost.data, mat, size);
        break;
    default:
        break;
    }

}

template<typename Scale>
void KFTrackBase<Scale>::Update(ObstacleBasePtr& measurement)
{
    std::shared_ptr<cv::Mat> mat;
    ConvertObstacle2CVMat(measurement, mat);
    cv::Mat state = kf_filter_ptr_->correct(*mat);
    ConvertCVMat2Obstacle(state, measurement);
    cur_obs_ptr_ = measurement;

}

template<typename Scale>
void KFTrackBase<Scale>::Update()
{
    cv::Mat state_pre = kf_filter_ptr_->statePre;
    cv::Mat state = kf_filter_ptr_->correct(state_pre);
    ConvertCVMat2Obstacle(state, cur_obs_ptr_);
}

template<typename Scale>
const cv::Mat& KFTrackBase<Scale>::Update(cv::Mat& measurement)
{
    return kf_filter_ptr_->correct(measurement);
}

template<typename Scale>
const cv::Mat&  KFTrackBase<Scale>::Predic(cv::Mat control)
{

    return kf_filter_ptr_->predict(control);

}

template<typename Scale>
inline const TimeStamp& KFTrackBase<Scale>::start_track_time() const noexcept
{
    return start_track_time_;
}

template<typename Scale>
inline void KFTrackBase<Scale>::start_track_time(const TimeStamp& time) 
{
    start_track_time_.sec(time.sec());
    start_track_time_.nsec(time.nsec());
}

template<typename Scale>
inline const TimeStamp& KFTrackBase<Scale>::last_track_time() const noexcept
{
    return last_track_time_;
}

template<typename Scale>
inline void KFTrackBase<Scale>::last_track_time(const TimeStamp& time) 
{
    last_track_time_.sec(time.sec());
    last_track_time_.nsec(time.nsec());
}
template<typename Scale>
inline typename KFTrackBase<Scale>::ObstacleBasePtr KFTrackBase<Scale>::GetCurObstaclePtr() const noexcept
{
    cur_obs_ptr_->TrackId(track_id_);
    
    return cur_obs_ptr_;
}

template<typename Scale>
inline void KFTrackBase<Scale>::period(const double period)
{
    period_ = period;
}

template<typename Scale>
inline float64_t KFTrackBase<Scale>:: period() const noexcept
{
    return period_;
}

template<typename Scale>
inline float64_t KFTrackBase<Scale>::lost_frames(TimeStamp& now)
{
    lost_frames_ =  (now - last_track_time_).ToSec() / period_;
    return lost_frames_;
}

template<typename Scale>
inline float64_t KFTrackBase<Scale>::lost_frames()
{
    return lost_frames_;
}

template<typename Scale>
inline typename KFTrackBase<Scale>::Status KFTrackBase<Scale>::status()
{
    return status_;
}

template<typename Scale>
inline void KFTrackBase<Scale>::status(const Status s)
{
    status_ = s;
}

template<typename Scale>
inline float64_t KFTrackBase<Scale>::GetSecFromFristDetect(const TimeStamp& now)
{
    duration_from_start_ = (now - start_track_time_).ToSec();
    return duration_from_start_;
}

template<typename Scale>
inline float64_t KFTrackBase<Scale>::GetSecFromFristDetect()
{
    return duration_from_start_;
}

template<typename Scale>
inline float64_t KFTrackBase<Scale>::GetSecFromLastDetect(const TimeStamp& now)
{
    duration_from_last_ = (now - last_track_time_).ToSec();
    return duration_from_last_;
}

template<typename Scale>
inline float64_t KFTrackBase<Scale>::GetSecFromLastDetect()
{
    return duration_from_last_;
}

template<typename Scale>
void KFTracksBase<Scale>::CreateDistaceMatrix()
{
    distance_matrix_ = cv::Mat_<float32_t>(tracks_.size(), detections_.size());
    
    cost_matrix_ = holo::MatrixT<Scale>(tracks_.size(), detections_.size());
    size_t track = 0;
    for(auto it = tracks_.begin(); it != tracks_.end(); it++)
    {
        size_t measure = 0;
        for(auto dit = detections_.begin(); dit != detections_.end(); dit++)
        {
            distance_matrix_(track, measure) = ComputeDistance(*it, *dit);
            /// remove NaN and inf
            if(std::isnan(distance_matrix_(track, measure)) || (not std::isfinite(distance_matrix_(track, measure)))) distance_matrix_(track, measure) = 2*gate_distance_;
            if(distance_matrix_(track, measure) > gate_distance_)
            {
                cost_matrix_(track, measure) = 10000.0;
                // -debug munkres.optimizer: TODO SunZhenqiang
            }
            else
                cost_matrix_(track, measure) = distance_matrix_(track, measure);
            measure++;
            
        }
        track++;
    }
   
}

template<typename Scale>
void KFTracksBase<Scale>::UpdateDetectedTracks()
{
    int track = 0;
    asscoiated_index_.clear();
    for(auto it = tracks_.begin(); it != tracks_.end(); it++)
    {
        LOG(ERROR) << "all track status  " << (*it)->status() << "  track id  " << (*it)->GetCurObstaclePtr()->TrackId() << "  associated reack bool  " << asscoiated_[track];
        if(0 <= asscoiated_[track])
        {
            TAtype measure_ind = asscoiated_[track];
            auto detections_ptr = detections_.begin();
            advance(detections_ptr,measure_ind);
            ObstacleBasePtr d = *detections_ptr;

            LOG(ERROR) << "----------------- assocoasted tracks --------------";
            LOG(ERROR) << "associated track " << track << "  measure ind " << measure_ind;
            LOG(ERROR) << "track stats  " << (*it)->status();
            LOG(ERROR)<<"track  "<<(*it)->GetCurObstaclePtr()->TrackId()<<" P_x: "<<(*it)->GetCurObstaclePtr()->Position().x()<<
                                                                          " P_y: "<<(*it)->GetCurObstaclePtr()->Position().y()<<
            "  asscoiated to detections id "<<d->TrackId()<<" P_x: "<<d->Position().x()<<" P_y: "<<d->Position().y()<<
            " current time "<<(*it)->GetCurObstaclePtr()->header().stamp() << "distance_matrix : " << distance_matrix_(track, measure_ind);
            LOG(ERROR) << "+++++++++++++++++++++end++++++++++++++++++++++";

            if((d->header().stamp() - (*it)->last_track_time()).ToSec() <= 0 || detal_time_ <= 0)
            {
                track++;
                asscoiated_index_.insert(measure_ind);
                continue;
            }
            else if(  distance_matrix_(track, measure_ind) > gate_distance_ ||
                      asscoiated_index_.end() != asscoiated_index_.find(measure_ind))
            {
                track++;
                asscoiated_index_.insert(measure_ind);
                (*it)->Update();
                continue;
            }
            else
            {
                switch ((*it)->status())
                {
                case KFtrack::Status::NEW:
                    if((*it)->GetSecFromFristDetect(current_time_) > new_track_convert_time_) 
                    (*it)->status(KFtrack::Status::NORMAL);
                    break;
                case KFtrack::Status::LOST:
                    (*it)->status(KFtrack::Status::NORMAL);
                    break;
                default:
                    break;
                }
                (*it)->Update(d);
                (*it)->last_track_time(current_time_);
                asscoiated_index_.insert(measure_ind);
                }
        }
        else
        {
            if(detal_time_ > 0) (*it)->Update();
        }
        
        track++;
    }

}

template<typename Scale>
void KFTracksBase<Scale>::UpdateTracks(std::list<KFtrackPtr>& tracks)
{
    CreateDistaceMatrix();
    
    HungarianOptimizer<Scale> munkres;

    asscoiated_ = munkres.optimizer(cost_matrix_);

    UpdateDetectedTracks();

    EliminateRedundantDetection();

    FillUnassociatedDetetions();

    FusionRedundantDetecttion();

    CreateNewTracks();
    tracks.clear();
    for(auto it = tracks_.begin(); it != tracks_.end(); it++)
    {
        if(KFtrack::Status::NORMAL == (*it)->status() || KFtrack::Status::LOST == (*it)->status())
        // if(KFtrack::Status::NORMAL == (*it)->status() )
        {
            tracks.emplace_back(*it);
        }
    }
}

template<typename Scale>
void KFTracksBase<Scale>::FillUnassociatedDetetions()
{
    unasscoiated_detections_.clear();
    size_t index = 0;
    for(auto it = detections_.begin(); it != detections_.end(); it++)
    {
        if(asscoiated_index_.end() == asscoiated_index_.find(index)  && redundancy_detection_index_.end() == redundancy_detection_index_.find(index))
        {
            unasscoiated_detections_.emplace_back(*it);
        }
        index++;
    } 
}

template<typename Scale>
void KFTracksBase<Scale>::CreateNewTracks()
{
    for(auto it = fusion_unasscoiated_detections_.begin(); it != fusion_unasscoiated_detections_.end(); it++)
    {
       tracks_.emplace_back(CreateNewKFTrack(*it));
    }
}

// template<typename Scale>
// int KFTracksBase<Scale>::CreateNewTrack(ObstacleBase& detection)
// {
//     KFtrack* track = createNewKFTrack(detection);
//     tracks_.emplace_back(track);
//     return tracks_counter_;
// }

template<typename Scale>
void KFTracksBase<Scale>::NewFrame(const std::list<ObstacleBasePtr>& detections, const TimeStamp& now_time)
{
    detections_.clear();
    unasscoiated_detections_.clear();
    FreeDiscardtracks();
    discard_tracks_.clear();
    detections_ = detections;
    TimeStamp now = now_time;
    detal_time_ = (now_time - current_time_).ToSec();
 
    for(auto it = tracks_.begin(); it != tracks_.end();)
    {   
        if((*it) ->status() == KFtrack::Status::NORMAL && (*it)->GetSecFromLastDetect(now) >= normal_track_remain_time_)
        {
            (*it)->status(KFtrack::Status::LOST);
        }
        if(((*it) ->status() == KFtrack::Status::NEW &&  (*it)->GetSecFromLastDetect(now) >= new_track_remain_time_) ||
            ((*it)->status() == KFtrack::Status::LOST && (*it)->GetSecFromLastDetect(now) >= lost_track_remain_time_) ||
            ((*it)->status() == KFtrack::Status::LOST && (*it)->lost_frames() >= max_lost_frames_))
        {
             
            discard_tracks_.emplace_back((*it));
            tracks_.erase(it++);    
        }
        it++;
        
    }
    
    for(auto it = tracks_.begin(); it != tracks_.end(); )
    {
        Scale lost_frames_f = (now-current_time_).ToSec() / (*it)->period();
        int  lost_frames = std::round(lost_frames_f);
        if(0 <=lost_frames )
        {
                for(int index = 0 ; index < int(lost_frames)-1; index++)
            {
                (*it)->Predic();
                (*it)-> Update();
            }
            (*it)->Predic();
        }
        it++;
    }
    current_time_ = now_time;
    
}



template<typename Scale>
void KFTracksBase<Scale>::gate_distance(const float64_t gate_distance)
{
    gate_distance_ = gate_distance;
}

template<typename Scale>
float64_t KFTracksBase<Scale>::gate_distance() const
{
    return gate_distance_;
}

template<typename Scale>
void KFTracksBase<Scale>::new_track_remain_time(const float64_t time)
{
    new_track_remain_time_ = time;
}

template<typename Scale>
float64_t KFTracksBase<Scale>::new_track_remain_time() const
{
    return new_track_remain_time_;
}

template<typename Scale>
void KFTracksBase<Scale>::max_lost_frames(const float64_t frames)
{
    max_lost_frames_ = frames;
}

template<typename Scale>
float64_t KFTracksBase<Scale>::max_lost_frames() const
{
    return max_lost_frames_;
}

template<typename Scale>
void KFTracksBase<Scale>::FusionRedundantDetecttion()
{
    fusion_unasscoiated_detections_.clear();
    fusion_unasscoiated_detections_ = unasscoiated_detections_;
}

template<typename Scale>
void KFTracksBase<Scale>::normal_track_remain_time(const float64_t time)
{
    normal_track_remain_time_ = time;
}

template<typename Scale>
float64_t KFTracksBase<Scale>::normal_track_remain_time()const
{
    return normal_track_remain_time_;
}

}
}

#endif