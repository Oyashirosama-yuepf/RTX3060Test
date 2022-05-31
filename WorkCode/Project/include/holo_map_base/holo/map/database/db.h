/*!
 *  \brief BASE CLASS DATABASE
 *  \author jiangdianqin(jiangdianqin@holomaitc.com)
 *  \date 2017-04-04
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */
#ifndef HOLO_MAP_DATABASE_RETRIEVER_DB
#define HOLO_MAP_DATABASE_RETRIEVER_DB
#include <holo/map/common/common_type_define.h>
#include <holo/map/format/base/base.h>
namespace holo
{
namespace map
{
template <typename DataType>
class DB
{
protected:
    typedef std::shared_ptr<DataType> DataType_Ptr;

public:
    /**
     * @brief DB constructor
     */
    DB() = default;
    /**
     * @brief DB destructor
     */
    virtual ~DB() = default;
    /**
     * @brief Open a new DB,suit for file DB
     *
     * @param[in]  _data_db_path db file path
     * @return true   Open db handle success
     * @return false  Otherwise
     */
    virtual bool Open(const char* _data_db_path) = 0;
    /**
     * @brief Create a Table
     *
     * @return true          Create Table success
     * @return false         Otherwise
     */
    virtual bool CreateTable() = 0;
    /**
     * @brief Create a Index object
     *
     * @return true   Create index successfully
     * @return false  Otherwise
     */
    virtual bool CreateIndex() = 0;
    /**
     * @brief Write a record into db
     *
     * @param[in]  zKey    key assignments
     * @param[in]  value   value assignments
     * @return true    write success
     * @return false   otherwise
     */
    virtual bool Write(const MapFeatureIdType _zKey,
                       const std::shared_ptr<DataType>& _value_ptr) = 0;
    /**
     * @brief Read a record from db
     *
     * @note If a target data is not in database actually, it will return
     *       false.
     * @param[in]   key      key assignments
     * @param[out]  value    out value
     * @return true     read success
     * @return false    otherwis
     */
    virtual bool Read(MapFeatureIdType const key,
                      std::shared_ptr<DataType> const & value) = 0;

    /**
     * @brief Read a record from db
     * 
     * @note If a target data is not in database actually, it will return
     *       true, but the valid will be set false.
     * @param[in]  key  key assignments
     * @param[out] value out value
     * @param[out] valid Whether or not the _value_ptr is valid.
     * @return true No error, if the target object not in database 
     *              actually, valid will be false, if should check it.
     * @return false An error occurs in this function.
     */
    virtual bool ReadV2(MapFeatureIdType const key,
                        std::shared_ptr<DataType> const& value,
                        bool& valid) = 0;

    /**
     * @brief Update a record from db
     *
     * @param[in] _zKey
     * @param[in] _value_ptr
     * @return true
     * @return false
     */
    virtual bool Update(const MapFeatureIdType _zKey,
                        const std::shared_ptr<DataType>& _value_ptr) = 0;
    /**
     * @brief Delete a record from db
     *
     * @param[in] _zKey
     * @param[in] _value_ptr
     * @return true
     * @return false
     */
    virtual bool Delete(const MapFeatureIdType _zKey) = 0;
    /**
     * @brief judge if a recors exist
     * 
     * @param _zkey 
     * @return true record exist
     * @return false record doesn't exist 
     */
    virtual bool Exist(const MapFeatureIdType _zkey) = 0;
    /**
     * @brief  Close db
     *
     * @return true  close success
     * @return false otherwise
     */
    virtual bool Close() = 0;
};  // class DB
}  // namespace map
}  // namespace holo
#endif
