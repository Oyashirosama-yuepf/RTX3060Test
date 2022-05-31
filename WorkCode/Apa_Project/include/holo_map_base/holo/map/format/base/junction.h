/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file junction.h
 * @brief Auto generated code for Junction format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_BASE_JUNCTION_H_
#define HOLO_MAP_FORMAT_BASE_JUNCTION_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/base/junction.pb.h>


#include <holo/map/format/base/base.h>


#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  Junction: public Base
{
public:




private:
    ::std::uint64_t junction_id_; 
    ::std::vector<::std::uint64_t> internal_lanes_; 
    ::std::vector<::std::uint64_t> internal_links_; 
    ::std::vector<::std::uint64_t> connected_links_; 

private:
    void DecodeProto(const ::holo::map::proto::base::Junction& _proto_handler);
    ::holo::map::proto::base::Junction EncodeProto();

public:
    Junction();
    explicit Junction(const ::holo::map::proto::base::Junction& _proto_handler);
    // init all format data
    Junction(const ::std::uint64_t _junction_id,const ::std::vector<::std::uint64_t>& _internal_lanes,const ::std::vector<::std::uint64_t>& _internal_links,const ::std::vector<::std::uint64_t>& _connected_links);
    ~Junction();

    bool operator==(const ::holo::map::format::Junction& _other) const;
    Junction& operator=(const ::holo::map::proto::base::Junction& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::base::Junction GetProtoHandler()
    {
        return EncodeProto();
    }

    


    ::std::uint64_t GetJunctionId() const
    {
        return junction_id_;
    }
    void SetJunctionId(const ::std::uint64_t _junction_id)
    {
        junction_id_ = _junction_id;
    }

    const ::std::vector<::std::uint64_t>* GetPtrInternalLanes() const
    {
        return &internal_lanes_;
    }
    void SetInternalLanes(const ::std::vector<::std::uint64_t>& _internal_lanes)
    {
        internal_lanes_ = _internal_lanes;
    }

    const ::std::vector<::std::uint64_t>* GetPtrInternalLinks() const
    {
        return &internal_links_;
    }
    void SetInternalLinks(const ::std::vector<::std::uint64_t>& _internal_links)
    {
        internal_links_ = _internal_links;
    }

    const ::std::vector<::std::uint64_t>* GetPtrConnectedLinks() const
    {
        return &connected_links_;
    }
    void SetConnectedLinks(const ::std::vector<::std::uint64_t>& _connected_links)
    {
        connected_links_ = _connected_links;
    }


    void ClearInternalLanes()
    {
        internal_lanes_.clear();
    }
    void AddInternalLanesElement(const ::std::uint64_t& _value)
    {
        internal_lanes_.push_back(_value);
    }
    void UniqueAddInternalLanesElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(internal_lanes_, _value);
    }

    void ClearInternalLinks()
    {
        internal_links_.clear();
    }
    void AddInternalLinksElement(const ::std::uint64_t& _value)
    {
        internal_links_.push_back(_value);
    }
    void UniqueAddInternalLinksElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(internal_links_, _value);
    }

    void ClearConnectedLinks()
    {
        connected_links_.clear();
    }
    void AddConnectedLinksElement(const ::std::uint64_t& _value)
    {
        connected_links_.push_back(_value);
    }
    void UniqueAddConnectedLinksElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(connected_links_, _value);
    }









};  // class Junction

typedef ::std::shared_ptr<Junction> PtrJunction;
typedef const ::std::vector<Junction>* ConstRawPtrVecJunction;
typedef ::std::vector<Junction>* RawPtrVecJunction;
typedef ::std::shared_ptr<Junction const> ConstPtrJunction;
typedef ::std::shared_ptr<::std::vector<Junction> const> ConstPtrVecJunction;
typedef ::std::unordered_map<::std::uint64_t, PtrJunction> HashmapJunction;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_JUNCTION_H_