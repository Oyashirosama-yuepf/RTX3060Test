#ifndef HOLO_METADATA_IMPL_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_IMPL_TYPE_DESCRIPTION_H_

#include <yaml-cpp/yaml.h>
#include <cstdint>
#include <memory>
#include <vector>

namespace holo
{
namespace metadata
{
enum class Type : uint32_t
{
    BOOLEAN,
    CHAR,
    INT8,
    INT16,
    INT32,
    INT64,
    UINT8,
    UINT16,
    UINT32,
    UINT64,
    FLOAT32,
    FLOAT64,

    ENUMERATE,
    BITMASK,
    BITFIELD,

    STRING,
    ARRAY,
    ARRAY2D,

    SEQUENCE,
    SEQUENCE2D,

    STRUCT,
    TYPE_REFERENCE,
    VALUE_REFERENCE,

    INVALID,
};

class TypeDescription : public std::enable_shared_from_this<TypeDescription>
{
public:
    using MemberPair   = std::pair<std::string, std::shared_ptr<TypeDescription>>;
    using TemplatePair = std::pair<std::string, std::shared_ptr<TypeDescription>>;
    using PtrType      = std::shared_ptr<TypeDescription>;
    using ConstPtrType = std::shared_ptr<TypeDescription const>;

    static size_t const TAB_SIZE = 4U;

    Type GetType() const noexcept
    {
        return type_;
    }

    virtual uint32_t GetSize() const noexcept
    {
        return 0U;
    }

    virtual uint32_t GetAlignment() const noexcept
    {
        return align_;
    }

    void SetAlignment(uint32_t value) noexcept
    {
        align_ = value;
    }

    bool IsBigEndian() const noexcept
    {
        return big_endian_;
    }

    virtual std::string GetName() const noexcept
    {
        return type_name_;
    }

    virtual std::string GetFullName() const noexcept
    {
        return type_name_;
    }

    virtual PtrType GetDereferencedType()
    {
        return this->shared_from_this();
    }

    virtual std::vector<MemberPair> GetMembers() const noexcept
    {
        return {};
    }

    virtual std::vector<TemplatePair> GetTemplates() const noexcept
    {
        return {};
    }

    void SetParent(std::weak_ptr<TypeDescription> const parent)
    {
        parent_ = parent;
    }

    PtrType GetParent()
    {
        return parent_.lock();
    }

    bool HasParent() noexcept
    {
        return parent_.expired();
    }

    ConstPtrType GetParent() const noexcept
    {
        return std::const_pointer_cast<TypeDescription>(parent_.lock());
    }

    virtual std::string PrintToString(size_t indent) const noexcept
    {
        return std::string(indent, ' ') + GetName();
    }

    virtual YAML::Node ToYaml() const noexcept
    {
        YAML::Node node;
        node["type"]       = TypeToString(type_);
        node["align"]      = align_;
        node["big_endian"] = big_endian_;
        node["type_name"]  = type_name_;
        return node;
    }

    TypeDescription(Type type, std::string const& type_name, uint32_t align, bool big_endian)
      : type_(type), align_(align), big_endian_(big_endian), type_name_(type_name)
    {
    }

    static std::string TypeToString(Type value);
    static Type        StringToType(std::string const& value);

protected:
    virtual ~TypeDescription()
    {
    }

    Type                           type_;
    uint32_t                       align_;
    bool                           big_endian_;
    std::string                    type_name_;
    std::weak_ptr<TypeDescription> parent_;  ///< reference to parent type
};

template <typename T, size_t ALIGN = 4U, bool IS_BIG_ENDIAN = true>
struct TypeDescriptionResolver;

}  // namespace metadata
}  // namespace holo

#endif
