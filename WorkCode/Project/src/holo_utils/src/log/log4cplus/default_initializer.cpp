#include <holo/log/hololog.h>
#include <holo/log/log4cplus/default_initializer.h>

namespace holo
{
namespace log
{
namespace log4cplus
{
DefaultInitializer::DefaultInitializer()
{
    HoloLogger::Initialize();
}

DefaultInitializer::~DefaultInitializer()
{
    HoloLogger::Shutdown();
}

}  // namespace log4cplus
}  // namespace log
}  // namespace holo
