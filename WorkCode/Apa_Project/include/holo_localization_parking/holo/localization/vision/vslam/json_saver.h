/*!
 * \brief header file of visualization functions for factor graph
 * \author Yetong. Zhang, zhangyetong@holomatic.com
 * \date June-14-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_JSON_SAVER_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_JSON_SAVER_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

#include <holo/localization/vision/vslam/common_types.h>
#include <holo/localization/vision/vslam/factor_graph.h>

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
 * @brief A tool to export optimization values and factor graph in json format.
 * @details The format is as follows: [[{}, {}, ...], [{}, {}, ...]]. The first list contains variables, and the second
 * list contains factors. Each variable/list is represented as a dictionary, with each of its attribute as an element of
 * the dictionary. The attributes for variables include: [name, value, value_history, value_type, average_error,
 * location]. The attributes for factors include [name, type, variables, measurement, noise, error, whitened_error,
 * unwhitened_error]
 *
 */
class JsonSaver
{
public:
    /**
     * @brief handy type define
     */
    typedef std::pair<std::string, std::string> AttributeType;

    /**
     * @brief constructor
     */
    JsonSaver()
    {
    }

    /**
     * @brief destructor
     */
    ~JsonSaver()
    {
    }

    /**
     * @brief add double quotes to string
     *
     * @param[in] str input string
     * @return a string with double quotes
     */
    static std::string Quoted(const std::string& str);

    /**
     * @brief convert vector to a list in json format
     *
     * @param[in] vec gtsam vector
     * @return a string representing vector in json format
     */
    static std::string GetVector(const gtsam::Vector& vec);

    /**
     * @brief combine key value pairs into a dict in json format
     *
     * @param[in] items key value paris
     * @param[in] num_indents number of indents for each item, -1 for no
     * indent and no newline
     * @return a string representing dict in json format
     */
    static std::string JsonDict(const std::vector<AttributeType>& items, const int num_indents = 0);

    /**
     * @brief combine items into a list in json format
     *
     * @param[in] items vector of items
     * @param[in] num_indents number of indents for each item, -1 for no
     * indent and no newline
     * @return a string representing list in json format
     */
    static std::string JsonList(const std::vector<std::string>& items, const int num_indents = 0);

protected:
    const static std::string kQuote_;
};  // JsonSaver

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Store history of the values and write to a json file
 */
class StorageManager
{
public:
    /**
     * @brief handy type define
     */
    typedef JsonSaver::AttributeType                              AttributeType;
    typedef boost::shared_ptr<gtsam::Value>                       ValuePtr;
    typedef std::unordered_map<gtsam::Key, std::vector<ValuePtr>> StorageMap;
    typedef std::unordered_map<gtsam::Key, gtsam::Vector3>        LocationType;

    /**
     * @brief constructor
     */
    StorageManager(const StorageMap& storage = StorageMap()) : storage_(storage)
    {
    }

    /**
     * @brief destructor
     */
    ~StorageManager()
    {
    }

    /**
     * @brief update values in storage
     *
     * @param[in] values gtsam values of variables in the current step
     * @return a new StorageManager whose values are updated
     */
    StorageManager UpdateValues(const gtsam::Values& values) const;

    /**
     * @brief output the json format factor graph (sequence) to ostream
     *
     * @param[in] factor_graph gtsam factor graph
     * @param[in] out_stream output stream
     * @param[in] values gtsam values of variables
     */
    void SaveFactorGraphSequence(const FactorGraph& factor_graph, std::ostream& out_stream,
                                 const gtsam::Values& values = gtsam::Values()) const;

protected:
    /**
     * @brief compute locations for each variable
     *
     * @param[in] variable_index gtsam variable index
     * @param[in] factor_graph gtsam factor graph
     * @return a map store each variable localization <gtsam::Key, gtsam::Vector3>
     */
    LocationType ComputeLocations(const gtsam::VariableIndex& variable_index, const FactorGraph& factor_graph) const;

    /**
     * @brief compute location of the given landmark
     * @details for example if the given landmark connects to pose X2, X3, X4 if location is (2 + 3 + 4) / 3
     *
     * @param[in] landmark_key gtsam key of the given landmark
     * @param[in] variable_index gtsam VariableIndex
     * @param[in] factor_graph gtsam factor graph
     * @return location
     */
    Scalar ComputeLandmarkLocation(const gtsam::Key& landmark_key, const gtsam::VariableIndex& variable_index,
                                   const FactorGraph& factor_graph) const;

    /**
     * @brief get the location of the variable
     *
     * @param[in] locations manually specified locations
     * @param[in] key gtsam key
     * @return a string displaying the location
     */
    std::string GetLocation(const LocationType& locations, const gtsam::Key& key) const;

    /**
     * @brief get the variable in json format as a string
     *
     * @param[in] key corresponding key of variable
     * @param[in] variable_index gtsam variable index
     * @param[in] factor_graph factor graph to compute average error for landmark
     * @param[in] values values to compute average error for landmark
     * @param[in] locations locations of the value when display it with html
     * @return a string displaying the variable in json
     */
    std::string GetVariableSequence(const gtsam::Key& key, const gtsam::VariableIndex& variable_index,
                                    const FactorGraph& factor_graph, const Values& values,
                                    const LocationType& locations) const;

    /**
     * @brief get the gtsam variable value as a string
     *
     * @param[in] value gtsam variable value
     * @param[in] readable whether add extra information to explain the value
     * @return a string displaying the value
     */
    std::string GetValue(const gtsam::Value& value, const bool readable) const;

    /**
     * @brief get the history of values e.g. [[x_t0, y_t0, z_t0], [x_t1, y_t1,
     * z_t1], [x_t2, y_t2, z_t2]]
     *
     * @param[in] key key for the variable
     * @return the history values of the variable
     */
    std::string GetValueHistory(const gtsam::Key& key) const;

    /**
     * @brief get names of the types of the value, e.g. ["x", "y", "z"]
     * @param[in] value gtsam variable value
     * @return a string displaying the value types
     */
    std::string GetValueTypes(const gtsam::Value& value) const;

    /**
     * @brief get the average error of the projection factor which connected to a landmark
     *
     * @param[in] landmark_key gtsam landmark key that projection factor connected to
     * @param[in] variable_index gtsam variable index
     * @param[in] factor_graph gtsam factor graph
     * @param[in] values gtsam values of variables
     * @return a string displaying the average error
     */
    std::string GetLandmarkAverageError(const gtsam::Key& landmark_key, const gtsam::VariableIndex& variable_index,
                                        const FactorGraph& factor_graph, const Values& values) const;

    /**
     * @brief get the factor in json format as a string
     *
     * @param[in] idx index of factor
     * @param[in] factor_graph  factor graph
     * @param[in] values values
     * @return a string displaying the factor in json
     */
    std::string GetFactor(const size_t idx, const FactorGraph& factor_graph, const gtsam::Values& values) const;

    /**
     * @brief get factor type as a string
     * @param[in] factor gtsam factor pointer
     * @return a string representing the factor type
     */
    std::string GetFactorType(const gtsam::NonlinearFactor::shared_ptr& factor) const;

    /**
     * @brief get measurements of the factor as a string
     * @param[in] factor gtsam factor pointer
     * @return a string displaying the measurement
     */
    std::string GetFactorMeasurement(const gtsam::NonlinearFactor::shared_ptr& factor) const;

    /**
     * @brief get the gtsam noise model type of the factor as a string
     *
     * @param[in] factor gtsam factor pointer
     * @return a string displaying the noise model type
     */
    std::string GetNoiseModelType(const gtsam::NonlinearFactor::shared_ptr& factor) const;

    /**
     * @brief get the unwhitened error of the factor as a string
     *
     * @param[in] factor gtsam factor pointer
     * @param[in] values gtsam values of variables
     * @return a string displaying the unwhitened error
     */
    std::string GetUnWhitenedError(const gtsam::NonlinearFactor::shared_ptr& factor, const Values& values) const;

    /**
     * @brief get the whitened error of the factor as a string
     *
     * @param[in] factor gtsam factor pointer
     * @param[in] values gtsam values of variables
     * @return a string displaying the whitened error
     */
    std::string GetWhitenedError(const gtsam::NonlinearFactor::shared_ptr& factor, const Values& values) const;

    /**
     * @brief get the error of the factor as a string
     * @param[in] factor gtsam factor pointer
     * @param[in] values gtsam values of variables
     * @return a string displaying the error
     */
    std::string GetError(const gtsam::NonlinearFactor::shared_ptr& factor, const Values& values) const;

private:
    // store history values
    StorageMap storage_;

    // format gtsam::Key to a std::string
    const static gtsam::KeyFormatter kKeyFormatter_;
};  // StorageManager

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_JSON_SAVER_H_