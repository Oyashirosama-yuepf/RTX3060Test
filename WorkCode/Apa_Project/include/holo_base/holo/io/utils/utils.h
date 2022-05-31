#ifndef HOLO_IO_UTILS_UTILS_H_
#define HOLO_IO_UTILS_UTILS_H_

#include <string>

namespace YAML
{
bool IsDigit(std::string str) noexcept
{
    if (str.find("0x") == 0)
    {
        for (uint16_t i = 2; i < str.length(); ++i)
        {
            if (('0' > str[i] || '9' < str[i]) && ('A' > str[i] || 'F' < str[i]) && ('a' > str[i] || 'f' < str[i]))
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        for (uint16_t i = 0; i < str.length(); ++i)
        {
            if (!isdigit(str[i]))
            {
                return false;
            }
        }
        return true;
    }
}
};  // namespace YAML
#endif