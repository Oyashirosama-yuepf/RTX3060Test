/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file map_reason.h
 * @brief Auto generated code for MapReason format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_HFL_MAP_REASON_H_
#define HOLO_MAP_FORMAT_HFL_MAP_REASON_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/hfl/map_reason.pb.h>


#include <holo/map/format/base/base.h>


#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  MapReason: public Base
{
public:

        
    enum Type
    {
        TYPE_UNDEFINED=  0,  
        TYPE_ADDITIONAL=  1,  
        TYPE_DISCARDED_AND_UPDATED=  2,  
    };

    static const ::std::map<::std::string, Type>& ENUMSTR_TYPE() 
    { 
        static const ::std::map<::std::string, Type> data{
        { "UNDEFINED", Type::TYPE_UNDEFINED },
        { "ADDITIONAL", Type::TYPE_ADDITIONAL },
        { "DISCARDED_AND_UPDATED", Type::TYPE_DISCARDED_AND_UPDATED }};
        return data;
    }


private:
    Type type_; 

private:
    void DecodeProto(const ::holo::map::proto::hfl::MapReason& _proto_handler);
    ::holo::map::proto::hfl::MapReason EncodeProto();

public:
    MapReason();
    explicit MapReason(const ::holo::map::proto::hfl::MapReason& _proto_handler);
    // init all format data
    MapReason(const Type& _type);
    ~MapReason();

    bool operator==(const ::holo::map::format::MapReason& _other) const;
    MapReason& operator=(const ::holo::map::proto::hfl::MapReason& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::hfl::MapReason GetProtoHandler()
    {
        return EncodeProto();
    }

    


    const Type& GetType() const
    {
        return type_;
    }
    void SetType(const Type& _type)
    {
        type_ = _type;
    }











};  // class MapReason

typedef ::std::shared_ptr<MapReason> PtrMapReason;
typedef const ::std::vector<MapReason>* ConstRawPtrVecMapReason;
typedef ::std::vector<MapReason>* RawPtrVecMapReason;
typedef ::std::shared_ptr<MapReason const> ConstPtrMapReason;
typedef ::std::shared_ptr<::std::vector<MapReason> const> ConstPtrVecMapReason;
typedef ::std::unordered_map<::std::uint64_t, PtrMapReason> HashmapMapReason;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_HFL_MAP_REASON_H_