/*!
 * \brief source file of visualization functions for factor graph
 * \author Yetong. Zhang, zhangyetong@holomatic.com
 * \date June-14-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <typeinfo>

#include <holo/localization/vision/vslam/json_saver.h>
#include <holo/localization/vision/vslam/pose_only_unit3_factor.h>
#include <holo/localization/vision/vslam/unit3_factor.h>
#include <holo/localization/vision/vslam/velocity_factor.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
/**
 * JsonSaver
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const std::string JsonSaver::kQuote_ = "\"";

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string JsonSaver::Quoted(const std::string& str)
{
    return kQuote_ + str + kQuote_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string JsonSaver::GetVector(const gtsam::Vector& vec)
{
    std::stringstream ss;
    ss << "[";

    for (auto i = 0; i < vec.size(); i++)
    {
        ss << vec[i];

        if (i + 1 < vec.size())
        {
            ss << ", ";
        }
    }

    ss << "]";
    return ss.str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string JsonSaver::JsonDict(const std::vector<AttributeType>& items, const int num_indents)
{
    std::string indents;
    std::string s;

    if (num_indents < 0)  // no indents
    {
        indents = "";
        s       = "{";
    }
    else
    {
        indents = "\n" + std::string(num_indents, ' ');
        s       = std::string(num_indents, ' ') + "{";
    }

    for (const auto& item : items)
    {
        s += indents + item.first + ":" + item.second + ",";
    }

    s.pop_back();  // remove the last comma
    s += indents + "}";
    return s;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string JsonSaver::JsonList(const std::vector<std::string>& items, const int num_indents)
{
    std::string indents;
    std::string s;

    if (num_indents < 0)  // no indents
    {
        indents = "";
        s       = "[";
    }
    else
    {
        indents = "\n" + std::string(num_indents, ' ');
        s       = std::string(num_indents, ' ') + "[";
    }

    for (const auto& item : items)
    {
        s += indents + item + ",";
    }

    s.pop_back();  // remove the last comma
    s += indents + "]";
    return s;
}

/**
 * StorageManager
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const gtsam::KeyFormatter StorageManager::kKeyFormatter_ = gtsam::DefaultKeyFormatter;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StorageManager StorageManager::UpdateValues(const gtsam::Values& values) const
{
    // step1: remove absent variables
    StorageMap updated_storage;

    for (const auto& key_value : storage_)
    {
        if (!values.exists(key_value.first))
        {
            continue;
        }

        updated_storage.emplace(key_value);
    }

    // step2: update existing variables and new variables
    for (const auto& key : values.keys())
    {
        auto it = updated_storage.find(key);

        if (it == updated_storage.end())
        {
            updated_storage.emplace(key, std::vector<ValuePtr>{values.at(key).clone()});
        }
        else
        {
            it->second.push_back(values.at(key).clone());
        }
    }

    return StorageManager(updated_storage);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StorageManager::SaveFactorGraphSequence(const FactorGraph& factor_graph, std::ostream& out_stream,
                                             const gtsam::Values& values) const
{
    gtsam::VariableIndex variable_index(factor_graph);

    // add variables
    std::vector<std::string> variable_strings;
    LocationType             locations = ComputeLocations(variable_index, factor_graph);

    for (gtsam::Key key : factor_graph.keys())
    {
        variable_strings.push_back(GetVariableSequence(key, variable_index, factor_graph, values, locations));
    }

    // add factors
    std::vector<std::string> factor_strings;

    for (size_t i = 0; i < factor_graph.size(); ++i)
    {
        // some factor might be set to nullptr
        if (factor_graph.at(i) == nullptr)
        {
            continue;
        }

        factor_strings.push_back(GetFactor(i, factor_graph, values));
    }

    std::string              s_variables = JsonSaver::JsonList(variable_strings);
    std::string              s_factors   = JsonSaver::JsonList(factor_strings);
    std::vector<std::string> all_strings{s_variables, s_factors};
    std::string              s_all = JsonSaver::JsonList(all_strings);
    out_stream << s_all;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StorageManager::LocationType StorageManager::ComputeLocations(const gtsam::VariableIndex& variable_index,
                                                              const FactorGraph&          factor_graph) const
{
    const auto&  keys = factor_graph.keys();
    LocationType locations;

    for (const auto& key : keys)
    {
        gtsam::Symbol symbol(key);

        if (symbol.chr() == 'x')
        {
            locations.emplace(key, gtsam::Vector3(symbol.index(), 1, 0));
        }
        else if (symbol.chr() == 'v')
        {
            locations.emplace(key, gtsam::Vector3(symbol.index(), 2, 0));
        }
        else if (symbol.chr() == 'b')
        {
            locations.emplace(key, gtsam::Vector3(symbol.index(), 3, 0));
        }
        else if (symbol.chr() == 'l')
        {
            locations.emplace(key, gtsam::Vector3(ComputeLandmarkLocation(key, variable_index, factor_graph), 0, 0));
        }
    }

    return locations;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Scalar StorageManager::ComputeLandmarkLocation(const gtsam::Key&           landmark_key,
                                               const gtsam::VariableIndex& variable_index,
                                               const FactorGraph&          factor_graph) const
{
    Scalar      location     = 0.0;
    Scalar      num_pose     = 0.0;
    const auto& factor_slots = variable_index[landmark_key];

    for (const auto& factor_slot : factor_slots)
    {
        const auto& factor = factor_graph.at(factor_slot);

        if (const vslam::ProjectionFactor* f = dynamic_cast<vslam::ProjectionFactor*>(&(*factor)))
        {
            gtsam::Symbol pose_symbol(f->key1());
            location += pose_symbol.index();
            num_pose++;
        }
    }

    if (num_pose == 0)
    {
        LOG(ERROR) << "StorageManager --- there is no pose connects to "
                   << "landmark " << landmark_key;
    }
    else
    {
        location /= num_pose;
    }

    return location;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string StorageManager::GetLocation(const LocationType& locations, const gtsam::Key& key) const
{
    if (locations.find(key) != locations.end())
    {
        return JsonSaver::GetVector(locations.at(key));
    }

    return std::string("");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string StorageManager::GetVariableSequence(const gtsam::Key& key, const gtsam::VariableIndex& variable_index,
                                                const FactorGraph& factor_graph, const Values& values,
                                                const LocationType& locations) const
{
    std::vector<AttributeType> attributes;

    // name
    std::string name = kKeyFormatter_(key);
    attributes.emplace_back(JsonSaver::Quoted("name"), JsonSaver::Quoted(name));

    if (storage_.find(key) != storage_.end())
    {
        // value
        attributes.emplace_back(JsonSaver::Quoted("value"),
                                JsonSaver::Quoted(GetValue(*(storage_.at(key).back()), true)));

        // value history
        attributes.emplace_back(JsonSaver::Quoted("value_history"), GetValueHistory(key));

        // value type
        attributes.emplace_back(JsonSaver::Quoted("value_types"), GetValueTypes(*(storage_.at(key).back())));

        // save average projection error for landmark
        gtsam::Symbol symbol(key);

        if (symbol.chr() == 'l')
        {
            attributes.emplace_back(
                JsonSaver::Quoted("average_error"),
                JsonSaver::Quoted(GetLandmarkAverageError(key, variable_index, factor_graph, values)));
        }

        // location
        const auto loc_str = GetLocation(locations, key);
        if (loc_str != "")
        {
            attributes.emplace_back(JsonSaver::Quoted("location"), loc_str);
        }
    }

    return JsonSaver::JsonDict(attributes);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string StorageManager::GetValue(const gtsam::Value& value, const bool readable) const
{
    std::stringstream ss;

    // pose variable
    if (const gtsam::GenericValue<gtsam::Pose3>* p = dynamic_cast<const gtsam::GenericValue<gtsam::Pose3>*>(&value))
    {
        std::string readable_translation("[");
        std::string readable_rotation(", ");

        // add information to explain the value for user
        if (readable)
        {
            readable_translation = "Translation: [";
            readable_rotation    = "] Rotation: [";
        }

        const auto& translation = p->value().translation();
        const auto& rpy         = p->value().rotation().rpy();
        ss << readable_translation << translation.x() << ", " << translation.y() << ", " << translation.z()
           << readable_rotation << rpy[0] << ", " << rpy[1] << ", " << rpy[2] << "]";
    }
    // velocity variable
    else if (const gtsam::GenericValue<gtsam::Velocity3>* p =
                 dynamic_cast<const gtsam::GenericValue<gtsam::Velocity3>*>(&value))
    {
        ss << "[" << p->value().x() << ", " << p->value().y() << ", " << p->value().z() << "]";
    }
    // bias variable
    else if (const gtsam::GenericValue<gtsam::imuBias::ConstantBias>* p =
                 dynamic_cast<const gtsam::GenericValue<gtsam::imuBias::ConstantBias>*>(&value))
    {
        std::string readable_acceleration("[");
        std::string readable_angular(", ");

        if (readable)
        {
            readable_acceleration = "Acceleration: [";
            readable_angular      = "] Angular: [";
        }

        const auto& bias = p->value().vector();
        ss << readable_acceleration << bias[0] << ", " << bias[1] << ", " << bias[2] << readable_angular << bias[3]
           << ", " << bias[4] << ", " << bias[5] << "]";
    }
    // landmark variable
    else if (const gtsam::GenericValue<gtsam::Point3>* p =
                 dynamic_cast<const gtsam::GenericValue<gtsam::Point3>*>(&value))
    {
        ss << "[" << p->value().x() << ", " << p->value().y() << ", " << p->value().z() << "]";
    }

    return ss.str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string StorageManager::GetValueHistory(const gtsam::Key& key) const
{
    std::vector<std::string> value_sequence;

    for (const auto value_ptr : storage_.at(key))
    {
        value_sequence.push_back(GetValue(*value_ptr, false));
    }

    return JsonSaver::JsonList(value_sequence, -1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string StorageManager::GetValueTypes(const gtsam::Value& value) const
{
    // pose variable
    std::vector<std::string> value_types;
    if (typeid(value) == typeid(gtsam::GenericValue<gtsam::Pose3>))
    {
        value_types = std::vector<std::string>{"x", "y", "z", "row", "pitch", "yaw"};
    }
    // velocity variable
    else if (typeid(value) == typeid(gtsam::GenericValue<gtsam::Velocity3>))
    {
        value_types = std::vector<std::string>{"vx", "vy", "vz"};
    }
    // bias variable
    else if (typeid(value) == typeid(gtsam::GenericValue<gtsam::imuBias::ConstantBias>))
    {
        value_types =
            std::vector<std::string>{"acc_x", "acc_y", "acc_z", "angular_v_row", "angular_v_pitch", "angular_v_yaw"};
    }
    // landmark variable
    else if (typeid(value) == typeid(gtsam::GenericValue<gtsam::Point3>))
    {
        value_types = std::vector<std::string>{"x", "y", "z"};
    }

    std::vector<std::string> quoted_value_types;
    quoted_value_types.reserve(value_types.size());

    for (auto& value_type : value_types)
    {
        quoted_value_types.push_back(JsonSaver::Quoted(value_type));
    }

    return JsonSaver::JsonList(quoted_value_types, -1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string StorageManager::GetLandmarkAverageError(const gtsam::Key&           landmark_key,
                                                    const gtsam::VariableIndex& variable_index,
                                                    const FactorGraph& factor_graph, const Values& values) const
{
    const auto& factor_slots = variable_index[landmark_key];
    Scalar      error        = 0.0;
    Scalar      num_factor   = 0.0;

    for (const auto& factor_slot : factor_slots)
    {
        const auto& factor = factor_graph.at(factor_slot);

        if (const vslam::ProjectionFactor* f = dynamic_cast<const vslam::ProjectionFactor*>(&(*factor)))
        {
            error += (f->unwhitenedError(values)).norm();
            num_factor++;
        }
    }

    if (num_factor > 0.0)
    {
        error /= num_factor;
    }
    else
    {
        // -1 ->invalid error
        LOG(WARNING) << "StorageManager --- GetLandmarkAverageError "
                     << "there is no ProjectionFactor connects to landmark " << landmark_key;
        error = -1;
    }

    std::stringstream ss;
    ss << error;
    return ss.str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string StorageManager::GetFactor(const size_t idx, const FactorGraph& factor_graph,
                                      const gtsam::Values& values) const
{
    const gtsam::NonlinearFactor::shared_ptr& factor = factor_graph.at(idx);
    std::vector<AttributeType>                attributes;

    // name
    attributes.emplace_back(JsonSaver::Quoted("name"), JsonSaver::Quoted("Factor" + std::to_string(idx)));

    // type
    attributes.emplace_back(JsonSaver::Quoted("type"), JsonSaver::Quoted(GetFactorType(factor)));

    // variables
    const gtsam::KeyVector&  keys = factor->keys();
    std::vector<std::string> variable_names;

    for (gtsam::Key key : keys)
    {
        variable_names.push_back(JsonSaver::Quoted(kKeyFormatter_(key)));
    }
    attributes.emplace_back(JsonSaver::Quoted("variables"), JsonSaver::JsonList(variable_names, -1));

    // measurement
    attributes.emplace_back(JsonSaver::Quoted("measurement"), JsonSaver::Quoted(GetFactorMeasurement(factor)));

    // noise model
    attributes.emplace_back(JsonSaver::Quoted("noise"), JsonSaver::Quoted(GetNoiseModelType(factor)));

    // unwhitened noise model
    attributes.emplace_back(JsonSaver::Quoted("unwhitened_error"),
                            JsonSaver::Quoted(GetUnWhitenedError(factor, values)));

    // whitened noise model
    attributes.emplace_back(JsonSaver::Quoted("whitened_error"), JsonSaver::Quoted(GetWhitenedError(factor, values)));

    // error
    attributes.emplace_back(JsonSaver::Quoted("error"), GetError(factor, values));

    return JsonSaver::JsonDict(attributes);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string StorageManager::GetFactorType(const gtsam::NonlinearFactor::shared_ptr& factor) const
{
    if (dynamic_cast<const vslam::VelocityFactor*>(&(*factor)))
    {
        return "velocity";
    }
    else if (dynamic_cast<const gtsam::ImuFactor*>(&(*factor)))
    {
        return "imu";
    }
    else if (dynamic_cast<const vslam::ProjectionFactor*>(&(*factor)))
    {
        return "generic projection";
    }
    else if (dynamic_cast<const vslam::Unit3Factor*>(&(*factor)))
    {
        return "unit3";
    }
    else if (dynamic_cast<const vslam::ImuBiasFactor*>(&(*factor)))
    {
        return "bias between";
    }
    else if (dynamic_cast<const gtsam::PriorFactor<gtsam::Pose3>*>(&(*factor)))
    {
        return "prior pose";
    }
    else if (dynamic_cast<const gtsam::PriorFactor<gtsam::Vector3>*>(&(*factor)))
    {
        return "prior velocity";
    }
    else if (dynamic_cast<const gtsam::PriorFactor<gtsam::imuBias::ConstantBias>*>(&(*factor)))
    {
        return "prior bias";
    }
    else if (dynamic_cast<const gtsam::PriorFactor<vslam::PoseOnlyUnit3FactorPtr>*>(&(*factor)))
    {
        return "pose only unit3";
    }
    else
    {
        return typeid(*factor).name();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string StorageManager::GetFactorMeasurement(const gtsam::NonlinearFactor::shared_ptr& factor) const
{
    std::stringstream ss;

    if (const vslam::VelocityFactor* f = dynamic_cast<const vslam::VelocityFactor*>(&(*factor)))
    {
        ss << JsonSaver::GetVector(f->GetVelocityMeasurement());
    }
    else if (const gtsam::ImuFactor* f = dynamic_cast<const gtsam::ImuFactor*>(&(*factor)))
    {
        const auto pim = f->preintegratedMeasurements();
        ss << "deltaVij: " << JsonSaver::GetVector(pim.deltaVij())
           << "deltaPij: " << JsonSaver::GetVector(pim.deltaPij())
           << "deltaRPY: " << JsonSaver::GetVector(pim.deltaRij().rpy());
    }
    else if (const vslam::ProjectionFactor* f = dynamic_cast<const vslam::ProjectionFactor*>(&(*factor)))
    {
        ss << f->measured();
    }
    else if (const vslam::PoseOnlyUnit3Factor* f = dynamic_cast<const vslam::PoseOnlyUnit3Factor*>(&(*factor)))
    {
        f->GetFeatureMeasurement();

        ss << "feature: " << f->GetFeatureMeasurement() << " "
           << "landmark: " << f->GetLandmarkMeasurement();
    }
    else if (const vslam::Unit3Factor* f = dynamic_cast<const vslam::Unit3Factor*>(&(*factor)))
    {
        ss << f->GetFeatureMeasurement();
    }
    return ss.str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string StorageManager::GetNoiseModelType(const gtsam::NonlinearFactor::shared_ptr& factor) const
{
    std::stringstream ss;

    if (const gtsam::NoiseModelFactor* noise_factor = dynamic_cast<const gtsam::NoiseModelFactor*>(&(*factor)))
    {
        const gtsam::noiseModel::Base::shared_ptr noise_model = noise_factor->noiseModel();

        // unit
        if (const gtsam::noiseModel::Unit* true_noise_model =
                dynamic_cast<const gtsam::noiseModel::Unit*>(&(*noise_model)))
        {
            ss << "unit " << true_noise_model->isUnit();
        }
        // isotropic
        else if (const gtsam::noiseModel::Isotropic* true_noise_model =
                     dynamic_cast<const gtsam::noiseModel::Isotropic*>(&(*noise_model)))
        {
            ss << boost::format("isotropic dim=%1% sigma=%2%") % true_noise_model->dim() % true_noise_model->sigma();
        }
        // constrained
        else if (const gtsam::noiseModel::Constrained* true_noise_model =
                     dynamic_cast<const gtsam::noiseModel::Constrained*>(&(*noise_model)))
        {
            ss << "constrained mus:" << JsonSaver::GetVector(true_noise_model->mu());
        }
        // diagonal
        else if (const gtsam::noiseModel::Diagonal* true_noise_model =
                     dynamic_cast<const gtsam::noiseModel::Diagonal*>(&(*noise_model)))
        {
            ss << "diagonal sigmas: " << JsonSaver::GetVector(true_noise_model->sigmas());
        }
        // gaussian
        else if (const gtsam::noiseModel::Gaussian* true_noise_model =
                     dynamic_cast<const gtsam::noiseModel::Gaussian*>(&(*noise_model)))
        {
            ss << "gaussian sigmas: " << JsonSaver::GetVector(true_noise_model->sigmas());
        }
        else
        {
            ss << typeid(*noise_model).name();
        }
    }

    return ss.str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string StorageManager::GetUnWhitenedError(const gtsam::NonlinearFactor::shared_ptr& factor,
                                               const Values&                             values) const
{
    std::stringstream ss;

    if (const gtsam::NoiseModelFactor* noise_factor = dynamic_cast<const gtsam::NoiseModelFactor*>(&(*factor)))
    {
        ss << JsonSaver::GetVector(noise_factor->unwhitenedError(values));
    }

    return ss.str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string StorageManager::GetWhitenedError(const gtsam::NonlinearFactor::shared_ptr& factor,
                                             const Values&                             values) const
{
    std::stringstream ss;

    if (const gtsam::NoiseModelFactor* noise_factor = dynamic_cast<const gtsam::NoiseModelFactor*>(&(*factor)))
    {
        ss << JsonSaver::GetVector(noise_factor->whitenedError(values));
    }

    return ss.str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string StorageManager::GetError(const gtsam::NonlinearFactor::shared_ptr& factor, const Values& values) const
{
    std::stringstream ss;
    ss << factor->error(values);
    return ss.str();
}

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo