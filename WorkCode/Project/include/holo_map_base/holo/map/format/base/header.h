/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file header.h
 * @brief Auto generated code for Header format
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date 2022-05-16
 */

#ifndef HOLO_MAP_FORMAT_BASE_HEADER_H_
#define HOLO_MAP_FORMAT_BASE_HEADER_H_

#include <vector>
#include <unordered_map>

#include <holo/map/proto/base/header.pb.h>

#include <holo/map/proto/common/geo_box.pb.h>

#include <holo/map/format/base/base.h>

#include <holo/map/format/common/geo_box.h>

#include <holo/map/common/across_zone_utility.h>

namespace holo
{
namespace map
{
namespace format
{

class  Header: public Base
{
public:

        
    enum Endianness
    {
        ENDIANNESS_UNDEFINED=  0,  
        ENDIANNESS_LITTLE_ENDIAN=  1,  
        ENDIANNESS_BIG_ENDIAN=  2,  
    };

        
    enum CoordinateReferenceSystem
    {
        COORDINATE_REFERENCE_SYSTEM_UNDEFINED=  0,  
        COORDINATE_REFERENCE_SYSTEM_GEOGRAPHICAL_COORDINATE_SYSTEM=  1,  
        COORDINATE_REFERENCE_SYSTEM_PROJECT_COORDINATE_SYSTEM=  2,  
    };

        
    enum DataSource
    {
        DATA_SOURCE_UNDEFINED=  0,  
        DATA_SOURCE_SHAPEFILE=  1,  
        DATA_SOURCE_NAVINFO_PILOT=  2,  
        DATA_SOURCE_BOTH=  3,  
    };

    static const ::std::map<::std::string, Endianness>& ENUMSTR_ENDIANNESS() 
    { 
        static const ::std::map<::std::string, Endianness> data{
        { "UNDEFINED", Endianness::ENDIANNESS_UNDEFINED },
        { "LITTLE_ENDIAN", Endianness::ENDIANNESS_LITTLE_ENDIAN },
        { "BIG_ENDIAN", Endianness::ENDIANNESS_BIG_ENDIAN }};
        return data;
    }

    static const ::std::map<::std::string, CoordinateReferenceSystem>& ENUMSTR_COORDINATEREFERENCESYSTEM() 
    { 
        static const ::std::map<::std::string, CoordinateReferenceSystem> data{
        { "UNDEFINED", CoordinateReferenceSystem::COORDINATE_REFERENCE_SYSTEM_UNDEFINED },
        { "GEOGRAPHICAL_COORDINATE_SYSTEM", CoordinateReferenceSystem::COORDINATE_REFERENCE_SYSTEM_GEOGRAPHICAL_COORDINATE_SYSTEM },
        { "PROJECT_COORDINATE_SYSTEM", CoordinateReferenceSystem::COORDINATE_REFERENCE_SYSTEM_PROJECT_COORDINATE_SYSTEM }};
        return data;
    }

    static const ::std::map<::std::string, DataSource>& ENUMSTR_DATASOURCE() 
    { 
        static const ::std::map<::std::string, DataSource> data{
        { "UNDEFINED", DataSource::DATA_SOURCE_UNDEFINED },
        { "SHAPEFILE", DataSource::DATA_SOURCE_SHAPEFILE },
        { "NAVINFO_PILOT", DataSource::DATA_SOURCE_NAVINFO_PILOT },
        { "BOTH", DataSource::DATA_SOURCE_BOTH }};
        return data;
    }


private:
    ::std::string name_; 
    ::std::uint64_t version_; 
    ::std::string date_; 
    Endianness endianness_; 
    CoordinateReferenceSystem coordinate_reference_system_; 
    DataSource data_source_; 
    ::std::vector<::std::uint64_t> tile_ids_; 

private:
    void DecodeProto(const ::holo::map::proto::base::Header& _proto_handler);
    ::holo::map::proto::base::Header EncodeProto();

public:
    Header();
    explicit Header(const ::holo::map::proto::base::Header& _proto_handler);
    // init all format data
    Header(const ::std::string& _name,const ::std::uint64_t _version,const ::std::string& _date,const Endianness& _endianness,const CoordinateReferenceSystem& _coordinate_reference_system,const DataSource& _data_source,const ::std::vector<::std::uint64_t>& _tile_ids);
    ~Header();

    bool operator==(const ::holo::map::format::Header& _other) const;
    Header& operator=(const ::holo::map::proto::base::Header& _proto_handler);

    static ::std::string GetClassName();
    ::std::uint64_t GetPrimaryKey() const override;
    const DataBlock GetDataBlock() override;
    void SetDataBlock(const DataBlock& _data_block) override;

    ::holo::map::proto::base::Header GetProtoHandler()
    {
        return EncodeProto();
    }

    


    const ::std::string& GetName() const
    {
        return name_;
    }
    void SetName(const ::std::string& _name)
    {
        name_ = _name;
    }

    ::std::uint64_t GetVersion() const
    {
        return version_;
    }
    void SetVersion(const ::std::uint64_t _version)
    {
        version_ = _version;
    }

    const ::std::string& GetDate() const
    {
        return date_;
    }
    void SetDate(const ::std::string& _date)
    {
        date_ = _date;
    }

    const Endianness& GetEndianness() const
    {
        return endianness_;
    }
    void SetEndianness(const Endianness& _endianness)
    {
        endianness_ = _endianness;
    }

    const CoordinateReferenceSystem& GetCoordinateReferenceSystem() const
    {
        return coordinate_reference_system_;
    }
    void SetCoordinateReferenceSystem(const CoordinateReferenceSystem& _coordinate_reference_system)
    {
        coordinate_reference_system_ = _coordinate_reference_system;
    }

    const DataSource& GetDataSource() const
    {
        return data_source_;
    }
    void SetDataSource(const DataSource& _data_source)
    {
        data_source_ = _data_source;
    }

    const ::std::vector<::std::uint64_t>* GetPtrTileIds() const
    {
        return &tile_ids_;
    }
    void SetTileIds(const ::std::vector<::std::uint64_t>& _tile_ids)
    {
        tile_ids_ = _tile_ids;
    }


    void ClearTileIds()
    {
        tile_ids_.clear();
    }
    void AddTileIdsElement(const ::std::uint64_t& _value)
    {
        tile_ids_.push_back(_value);
    }
    void UniqueAddTileIdsElements(const ::std::vector<::std::uint64_t>& _value)
    {
        UniqueAppend(tile_ids_, _value);
    }









};  // class Header

typedef ::std::shared_ptr<Header> PtrHeader;
typedef const ::std::vector<Header>* ConstRawPtrVecHeader;
typedef ::std::vector<Header>* RawPtrVecHeader;
typedef ::std::shared_ptr<Header const> ConstPtrHeader;
typedef ::std::shared_ptr<::std::vector<Header> const> ConstPtrVecHeader;
typedef ::std::unordered_map<::std::uint64_t, PtrHeader> HashmapHeader;

}  // namespace format
}  // namespace map 
}  // namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_HEADER_H_