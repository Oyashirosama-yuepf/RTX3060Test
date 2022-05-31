#ifndef HOLO_MAP_ADAPTER_COMMON_TYPES_H_
#define HOLO_MAP_ADAPTER_COMMON_TYPES_H_

#include <holo/map/common/common_type_define.h>

namespace holo
{
namespace map
{
namespace adapter
{

/**
 * @addtogroup adapter
 * @{
 *
 */

#define ENUMERATE_ADAPTER_TYPE          \
    X(ADAPTER_TYPE_ZERO)                \
    X(ADAPTER_TYPE_NAVINFO_SDK_1_2_X)   \
    X(ADAPTER_TYPE_BAIDU_SDK_3_1_X)     \
    X(ADAPTER_TYPE_MAX)

enum class AdapterType : holo::uint8_t
{
#define X(v) v,
    ENUMERATE_ADAPTER_TYPE
#undef X
};

#define ENUMERATE_ADAPTER_MODE_TYPE     \
    X(ADAPTER_MODE_TYPE_ZERO)           \
    X(ADAPTER_MODE_TYPE_POINT)          \
    X(ADAPTER_MODE_TYPE_PROVICE)        \
    X(ADAPTER_MODE_TYPE_RANGE)          \
    X(ADAPTER_MODE_TYPE_TRACK)          \
    X(ADAPTER_MODE_TYPE_CUSTOMER_RANGE) \
    X(ADAPTER_MODE_TYPE_MAX)

enum class AdapterModeType : holo::uint8_t
{
#define X(v) v,
    ENUMERATE_ADAPTER_MODE_TYPE
#undef X
};

#define ENUMERATE_MAP_DATA_INDEX           \
    X(MAP_DATA_INDEX_ZERO)                 \
    X(MAP_DATA_INDEX_BEIJING)              \
    X(MAP_DATA_INDEX_BEIJING_TEST)         \
    X(MAP_DATA_INDEX_SHANGHAI)             \
    X(MAP_DATA_INDEX_SUZHOU)               \
    X(MAP_DATA_INDEX_WUHAN)                \
    X(MAP_DATA_INDEX_GUANGZHOU)            \
    X(MAP_DATA_INDEX_GUANGZHOU_GAC_TEST)   \
    X(MAP_DATA_INDEX_GUANGZHOU_GAC_DEMO)   \
    X(MAP_DATA_INDEX_GUANGDONG)            \
    X(MAP_DATA_INDEX_CHINA_EAST)           \
    X(MAP_DATA_INDEX_CHANGCHUN)            \
    X(MAP_DATA_INDEX_CHENGDU_RAW)          \
    X(MAP_DATA_INDEX_BEIJING_T2_T3)        \
    X(MAP_DATA_INDEX_CITY_GUANGZHOU)       \
    X(MAP_DATA_INDEX_CITY_SHANGHAI)        \
    X(MAP_DATA_INDEX_CITY_SHENZHEN)        \
    X(MAP_DATA_INDEX_CITY_DONGGUAN)        \
    X(MAP_DATA_INDEX_CITY_SUZHOU)          \
    X(MAP_DATA_INDEX_CITY_NANJING)         \
    X(MAP_DATA_INDEX_CITY_TIANJIN)         \
    X(MAP_DATA_INDEX_CITY_CHONGQING)       \
    X(MAP_DATA_INDEX_CITY_CHENGDU)         \
    X(MAP_DATA_INDEX_CITY_BEIJING)         \
    X(MAP_DATA_INDEX_MAX)

enum class MapDataIndex : holo::uint8_t
{
#define X(v) v,
    ENUMERATE_MAP_DATA_INDEX
#undef X
};

#define ENUMERATE_MAP_VERSION_FLAG        \
    X(MAP_MAP_VERSION_ZERO)               \
    X(MAP_MAP_VERSION_ALPHA)              \
    X(MAP_MAP_VERSION_BETA)               \
    X(MAP_MAP_VERSION_RELEASE)            \
    X(MAP_MAP_VERSION_MAX)

enum class MapVersionFlag : holo::uint8_t
{
#define X(v) v,
    ENUMERATE_MAP_VERSION_FLAG
#undef X
};

#define ENUMERATE_MAP_STATUS_FLAG             \
    X(MAP_MAP_STATUS_FLAG_ZERO)               \
    X(MAP_MAP_STATUS_FLAG_RAW)                \
    X(MAP_MAP_STATUS_FLAG_BIAS)               \
    X(MAP_MAP_STATUS_FLAG_DEBIAS)             \
    X(MAP_MAP_STATUS_FLAG_MAX)

enum class MapStatusFlag : holo::uint8_t
{
#define X(v) v,
    ENUMERATE_MAP_STATUS_FLAG
#undef X
};

#define ENUMERATE_ENGINE_STATUS_FLAG    \
    X(MAP_ENGINE_STATUS_OK)             \
    X(MAP_ENGINE_STATUS_FAILED)         \
    X(MAP_ENGINE_STATUS_RETRY)          \
    X(MAP_ENGINE_STATUS_FLAG_MAX)

/**
 * @brief Define status for 3rt-party HD map engine, and dispaly it to
 *        application level.
 */
enum class MapEngineStatus : holo::uint8_t
{
#define X(v) v,
    ENUMERATE_ENGINE_STATUS_FLAG
#undef X
};

namespace utility
{
std::string const& GetAdapterTypeStr(AdapterType const t);

std::string GetAdapterTypeHelper(std::string const& prefix = "", std::string const& suffix = "");

std::string const& GetAdapterModeTypeStr(AdapterModeType const t);

std::string GetAdapterModeTypeHelper(std::string const& prefix = "", std::string const& suffix = "");

std::string const& GetMapDataIndexStr(MapDataIndex const t);

std::string GetMapDataIndexHelper(std::string const& prefix = "", std::string const& suffix = "");

std::string const& GetMapVersionFlagStr(MapVersionFlag const t);

std::string GetMapVersionFlagHelper(std::string const& prefix = "", std::string const& suffix = "");

std::string const& GetMapStatusFlagStr(MapStatusFlag const t);

std::string GetMapStatusFlagHelper(std::string const& prefix = "", std::string const& suffix = "");
} ///< namespace utility



/**
 * @}
 *
 */
} ///< namespace apapter
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_ADAPTER_COMMON_TYPES_H_ */
