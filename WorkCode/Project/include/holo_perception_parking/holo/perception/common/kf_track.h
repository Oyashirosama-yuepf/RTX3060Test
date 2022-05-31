/*!
 *  \brief implement track class
 *  \author pengcheng
 *  \date 20190627
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#ifndef HOLO_PERCEPTION_COMMON_TRACK_BASE_H_
#define HOLO_PERCEPTION_COMMON_TRACK_BASE_H_

#include <opencv2/opencv.hpp>
#include <memory>
#include <vector>
#include <list>
#include <set>
#include <holo/obstacle/obstacle_base.h>
#include <holo/perception/tracking/impl/hungarian_optimizer.hpp>
#include <holo/common/timestamp.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/numerics/vector.h>

namespace holo
{
namespace perception
{
template<typename Scale>
class KFTrackBase 
{
public:
    typedef ObstacleBaseT<Scale> ObstacleBase;
    typedef std::shared_ptr<ObstacleBase> ObstacleBasePtr;

    enum Status
    {
        NEW,    // New track is frist created, not enough confidence confirm tracking target
        NORMAL, // Normal track has been created a lot time, enough confidence cofirm the tracking target
        LOST,   // Lost track, miss some frames during tracking, may be tracked again
        DISCARD // Abandon tracking target
    };

    enum KalmanStatus
    {
        STATE_PRE = 1,          //!< predicted state (x'(k)): x(k)=A*x(k-1)+B*u(k)
        STATE_POST,             //!< corrected state (x(k)): x(k)=x'(k)+K(k)*(z(k)-H*x'(k))
        TRANSITION_MATRIX,      //!< state transition matrix (A)
        CONTROL_MATRIX,         //!< control matrix (B) (not used if there is no control)
        MEASUREMENT_MATRIX,     //!< measurement matrix (H)
        PROCESS_NOISE_COV,      //!< process noise covariance matrix (Q)
        MEASUREMENT_NOISE_COV,  //!< measurement noise covariance matrix (R)
        ERROR_COV_PRE,          //!< priori error estimate covariance matrix (P'(k)): P'(k)=A*P(k-1)*At + Q)
        GAIN,                   //!< Kalman gain matrix (K(k)): K(k)=P'(k)*Ht*inv(H*P'(k)*Ht+R)
        ERROR_COV_POST          //!< Kalman gain matrix (K(k)): K(k)=P'(k)*Ht*inv(H*P'(k)*Ht+R)
    };
    
    /**
     * @brief init for Kalman Filter
     * @param kf_state_num Dimensionality of the kalman filter's state.
     * @param kf_measure_num Dimensionality of the kalman filter's measurement.
     * @param Dimensionality of kalman filter's the control vector
     */
    void Init(size_t kf_state_num, size_t kf_measure_num, size_t kf_control_num);

    /**
     * @brief set some of kalman filter's state matrix
     * @param mat a pointer to a float32,which Contains matrix data eg:const float32_t KF_Transition_Mat[] = {
     *                                                                                                          1, 0, delta_t, 0, delta_t * delta_t / 2.0f,
     *                                                                                                          0, 1, 0, delta_t, 0,
     *                                                                                                          0, 0, 1, 0, delta_t,
     *                                                                                                          0, 0, 0, 1, 0,
     *                                                                                                          0, 0, 0, 0, 1
     *                                                                                                        };
     * @param size, the 'sizeof' of data eg: sizeof(KF_Transition_Mat)
     * @status Specify which state matrix to set
     */
    void SetKalmanStatusMatrix(const float32_t* mat, size_t size, KalmanStatus status);

    // kalman filter update 
    /**
     * @brief kalman filter update
     * @param measurement observation of obstacles
     */
    void Update(ObstacleBasePtr& measurement);

    /**
     * @brief convert Obstacle Observation matrix to opencv's Mat format
     * @param Ostb a object of ObstacleBase
     * @param obstc_cv converted opencv's Mat format results
     */
    virtual void  ConvertObstacle2CVMat(const ObstacleBasePtr& obstc, std::shared_ptr<cv::Mat>& mat) = 0; 
 
    /**
     * @brief convert opencv's Mat format to Observation matrix
     * @param obstc_cv a object of opencv's Mat
     * @param obstc converted Obstacle's format
     */
    virtual void ConvertCVMat2Obstacle(const cv::Mat& obstc_cv, ObstacleBasePtr& obstc) = 0;

    /**
     * @brief kalman filter update
     * @param observation of obstacles (opencv's Mat format)
     * @return Kalman filter update result (opencv's Mat format)
     */
    const cv::Mat& Update(cv::Mat& measurement);

    /**
     * @brief kalman filter update 
     */
    void Update();

    /**
     * @brief kalman filter predic 
     * @param control for 'u(k)' of 'x'(k) = x'(k) + B*u(k)', if the control is empty, control matrix (B) not used
     */
    const cv::Mat& Predic(cv::Mat control = cv::Mat());

     /**
    * @brief get current obstacle
    *
    * @return
    */
    inline ObstacleBasePtr GetCurObstaclePtr() const noexcept;

    // get the track created time
    inline const TimeStamp& start_track_time() const noexcept;

    // set the track time of created
    inline void start_track_time(const TimeStamp& time);

    // get the track time of last valid update
    inline const TimeStamp& last_track_time() const noexcept;

    // set the track time of last valid update
    inline void last_track_time(const TimeStamp& time);

    inline void period(const double period);

    inline float64_t period() const noexcept;

    inline float64_t lost_frames(TimeStamp& now);

    inline float64_t lost_frames();

    inline Status status();

    inline void status(const Status s);

    /**
     * @brief get the diff of time between current time and frist track time
     * @param now the current time 
     * @return the diff time
     */
    inline float64_t GetSecFromFristDetect(const TimeStamp& now);

    /**
     * @brief get diff of time between current time and last track time
     * @param now the current time
     * @return the diff time
     */
    inline float64_t GetSecFromLastDetect(const TimeStamp& now);

    /**
     * @brief get the diff of time between current time and frist track time
     * @return the diff time
     */
    inline float64_t GetSecFromFristDetect();

    /**
     * @brief get diff of time between current time and last track time
     * @return the diff time
     */
    inline float64_t GetSecFromLastDetect();

protected:
    // uid
    size_t track_id_;

    // start track time
    TimeStamp start_track_time_;

    // last track time 
    TimeStamp last_track_time_;

    // lost frames form last upated
    float64_t lost_frames_;

    /// period for kalman filter uptate
    float64_t period_;
    // track
    Status status_;

    // current track stage
    ObstacleBasePtr cur_obs_ptr_;

    // period of time between current time and start track time
    float64_t duration_from_start_;

    // period of time between current time and last track time
    float64_t duration_from_last_;

    

private:
    // the opencv's kalman filter
    std::shared_ptr<cv::KalmanFilter> kf_filter_ptr_;

};
template<typename Scale>
class KFTracksBase
{
public:
    typedef ObstacleBaseT<Scale> ObstacleBase;
    typedef std::shared_ptr<ObstacleBase> ObstacleBasePtr;
    typedef ObstaclePtrListT<ObstacleBase> ObstacleBasePtrList;

    typedef KFTrackBase<Scale> KFtrack;
    typedef std::shared_ptr<KFtrack> KFtrackPtr;
   
   /**
    * @brief update detections for a frame
    * @param detections a vector of detections
    * @param now_time the system current time
    */
   void NewFrame(const std::list<ObstacleBasePtr> &detections, const TimeStamp& now_time);

   /**
    * @brief compute the distance between a track and detection
    * @param track a kanman filter track 
    * @param detection a detection
    * @return the distance between the track and detection
    */
   virtual float64_t ComputeDistance(const KFtrackPtr& track, const ObstacleBasePtr& detection)const = 0;

protected:
    

    // @brief Create detections<->tracks distance matrix for data association  
    void CreateDistaceMatrix();

    // @brief update all normal tracks 
    void UpdateDetectedTracks();

    // @brief update all tracks base new frame ,the main update function
    /**
     * @brief update all tracks base new frame,and return the normal tracks. the main function
     * @param tracks the output of normal tracks
     */
    void UpdateTracks(std::list<KFtrackPtr>& tracks);

    // @brief fill all unassociated detections into the list of unasscoiated
    void FillUnassociatedDetetions();

    // @brief create a new track for every unassociated detection and push back to tracks_
    void CreateNewTracks();
    
    // @brief create a new kfTrackBase object base on a detection
    virtual KFtrackPtr CreateNewKFTrack(ObstacleBasePtr& detection) = 0;
    
    // @brief free lost tracks for the object is created by new or malloc 
    virtual void FreeDiscardtracks(){ discard_tracks_.clear();};

    // @brief Eliminate redundant detection,if used ,put the index of detection into redundancy_detection_index_
    virtual void EliminateRedundantDetection(){}

    // @frief funsiom the unassicated detection, if used, put 
    virtual void FusionRedundantDetecttion();

    virtual ~KFTracksBase(){};

    // @brief a normal track max remain time (form last detection time to now) 
    float64_t normal_track_remain_time()const;

    // @brief a new track max remain tiem (from frist time detection time to now) 
    inline float64_t new_track_remain_time() const;

    // @brief a normal track lost detection frames (from last detection time to now) 
    inline float64_t max_lost_frames() const;

    // @brief if  a distance (between track and detection) lower than the 'gate_distance' , the detection may be asscoiated to the track */
    inline float64_t gate_distance() const ;

    inline void gate_distance(const float64_t);

    inline void max_lost_frames(const float64_t);

    inline void new_track_remain_time(const float64_t);

    inline void normal_track_remain_time(const float64_t);

    // @brief List of current detections
    std::list<ObstacleBasePtr> detections_;
    
    // brief List of current detections not associated to any track 
    std::list<ObstacleBasePtr> unasscoiated_detections_;

    // @brief List of fusion detection from unasscoiated detections
    std::list<ObstacleBasePtr> fusion_unasscoiated_detections_;

    // @brief List of all activate tracks 
    std::list<KFtrackPtr> tracks_;

    // @brief List od lost tracks 
    std::list<KFtrackPtr> discard_tracks_;

    // @brief Track ID counter 
    size_t tracks_counter_ = 0;

    // @brief Gate distance for joint likelihood in data association 
    float64_t gate_distance_;

    // @brief Dettections <-> tracks distance matrix data asscoiation 
    cv::Mat_<Scale> distance_matrix_;

    // @brief Detections <-> tracks cost matrix to be used to solve the Global Nearest Neighbor problem 
    holo::MatrixT<Scale> cost_matrix_;

    // @brief asscoiated -> detections 
    holo::VectorT<TAtype> asscoiated_; //int32_t

    // @brief the the index of detections asscoited to track 
    std::set<TAtype> asscoiated_index_;
    
    // @brief the index of Redundancy detection asscoited to track
    std::set<TAtype> redundancy_detection_index_;
      
    // @brief new max remain time , if one new track is not updated in the duration, then the track renounce (move to lost tracks)
    float64_t new_track_remain_time_;

    // @brief new max convert time , if one new track is  updated in the duration, then the track normal 
    float64_t new_track_convert_time_ = 0;
    

    // @brief normal track max remain time, if one  normal track is not updated in the duration. then the track marjed lost(move to lost tracks) 
    float64_t normal_track_remain_time_;

    // @brief max lost frames for one track 
    float64_t max_lost_frames_;

    // @brief lost track max remain time, if one lost track is not updated in the duration(form last update time to now), then the track will be discarded
    float64_t lost_track_remain_time_;

    // the time when update 
    TimeStamp current_time_;

    // the diff betwent Twice recently
    float64_t detal_time_;

};
}
}

#endif

