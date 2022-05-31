#include <holo/log/glog/default_initializer.h>
#include <holo/log/hololog.h>

namespace holo
{
namespace log
{
namespace glog
{
DefaultInitializer::DefaultInitializer()
{
    HoloLogger::Initialize();
}

DefaultInitializer::~DefaultInitializer()
{
    HoloLogger::Shutdown();
}

}  // namespace glog
}  // namespace log
}  // namespace holo
