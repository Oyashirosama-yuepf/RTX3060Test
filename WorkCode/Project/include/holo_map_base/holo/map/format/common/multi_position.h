/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file multi_position.h
 * @brief Auto generated code for MultiPosition format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_COMMON_MULTI_POSITION_H_
#define HOLO_MAP_FORMAT_COMMON_MULTI_POSITION_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/common/multi_position.pb.h>

#include <holo/map/proto/common/position.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/position.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  MultiPosition: public Base
{
public:




private:
    ::std::vector<Position> positions_; 

private:
    void DecodeProto(const ::holo::map::proto::common::MultiPosition& _proto_handler);
    ::holo::map::proto::common::MultiPosition EncodeProto();

public:
    MultiPosition();
    explicit MultiPosition(const ::holo::map::proto::common::MultiPosition& _proto_handler);
    // init all format data
    MultiPosition(const ::std::vector<Position>& _positions);
    ~MultiPosition();

    bool operator==(const ::holo::map::format::MultiPosition& _other) const;
    MultiPosition& operator=(const ::holo::map::proto::common::MultiPosition& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::common::MultiPosition GetProtoHandler()
    {
        return EncodeProto();
    }

    


    const ::std::vector<Position>* GetPtrPositions() const
    {
        return &positions_;
    }
    void SetPositions(const ::std::vector<Position>& _positions)
    {
        positions_ = _positions;
    }


    void ClearPositions()
    {
        positions_.clear();
    }
    void AddPositionsElement(const Position& _value)
    {
        positions_.push_back(_value);
    }
    void UniqueAddPositionsElements(const ::std::vector<Position>& _value)
    {
        UniqueAppend(positions_, _value);
    }









};  // class MultiPosition

typedef ::std::shared_ptr<MultiPosition> PtrMultiPosition;
typedef const ::std::vector<MultiPosition>* ConstRawPtrVecMultiPosition;
typedef ::std::vector<MultiPosition>* RawPtrVecMultiPosition;
typedef ::std::shared_ptr<MultiPosition const> ConstPtrMultiPosition;
typedef ::std::shared_ptr<::std::vector<MultiPosition> const> ConstPtrVecMultiPosition;
typedef ::std::unordered_map<::std::uint64_t, PtrMultiPosition> HashmapMultiPosition;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_COMMON_MULTI_POSITION_H_