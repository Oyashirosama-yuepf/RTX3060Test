#ifndef TOPOLOGY_DESCRIPTION_H_
#define TOPOLOGY_DESCRIPTION_H_

#include <cstring>

class TopologyDescription
{
public:
    TopologyDescription(std::string const& value) : desc_{value}, childs{}
    {
    }

    TopologyDescription(std::string&& value) : desc_{std::move(value)}, childs{}
    {
    }

    std::vector<TopologyDescription>& Childs() noexcept
    {
        return childs;
    }

    std::string& Value() noexcept
    {
        return desc_;
    }

    std::vector<TopologyDescription> const& Childs() const noexcept
    {
        return childs;
    }

    std::string const& Value() const noexcept
    {
        return desc_;
    }

    std::string Format(uint32_t indent = 0) const noexcept
    {
        std::string ret;
        ret += std::string(indent, ' ') + desc_ + "\n";
        for(auto const& child : childs)
        {
            ret += child.Format(indent + 2);
        }
        return ret;
    }

private:
    std::string desc_;
    std::vector<TopologyDescription> childs;
};

#endif
