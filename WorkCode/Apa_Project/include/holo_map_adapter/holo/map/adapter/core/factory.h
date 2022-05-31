#ifndef HOLO_MAP_ADAPTER_CORE_FACTORY_H__
#define HOLO_MAP_ADAPTER_CORE_FACTORY_H__


#include <holo/map/adapter/base/adapter_base.h>
#include <holo/map/adapter/common/types.h>
#include <holo/map/adapter/core/writer.h>

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

class Factory
{
public:
    using AdapterSPtrType       = std::shared_ptr<AdapterBase>;
    using InitializerSPtrType   = std::shared_ptr<InitializerBase>;
    using InputerSptrType       = std::shared_ptr<InputerBase>;
    using OutputerSptrType      = std::shared_ptr<OutputerBase>;

    using WriterSPtrType = std::shared_ptr<Writer>;

    Factory() = delete;
    virtual ~Factory() = delete;

    static AdapterSPtrType CreateAdapter(AdapterType const t);
    static InitializerSPtrType CreateInitializer(AdapterSPtrType ptr);
    static InputerSptrType CreateInputer(AdapterSPtrType ptr);
    static OutputerSptrType CreateOutputer(AdapterSPtrType ptr);

    
    static WriterSPtrType CreateWriter();

}; ///< End of class Factory

/**
 * @}
 *
 */
} ///< namespace apapter
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_ADAPTER_CORE_FACTORY_H__ */
