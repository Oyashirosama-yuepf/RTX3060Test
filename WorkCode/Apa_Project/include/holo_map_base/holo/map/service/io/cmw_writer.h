/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file cmw_writer.h
 * @brief Concrete session writer based on cmw message channel.
 * @author wanghaiyang@holomatic.com
 * @date "2020-11-12"
 */

#ifndef HOLO_MAP_SERVICE_IO_CMW_WRITER_H_
#define HOLO_MAP_SERVICE_IO_CMW_WRITER_H_

#include <memory>
#include <queue>

#include <holo/map/service/io/writer.h>
#include <holo/map/common/classes/auto_spin_mutex.h>
#include <holo_cmw/CMW/CMW.h>
#include <holo_cmw/message/message.h>

namespace holo
{
namespace map
{
namespace service
{
namespace io
{

/**
 * @addtogroup io
 * @{
 *
 */

/**
 * @brief Concrete writer based on CMW message queue, write session data to CME message queue.
 */
class CMWWriter : public WriterBase
{
public:
    /**
     * @brief Constructor.
     * 
     * @param[in] cmw An initialized CMW handle.
     * @param[in] topic Topic name.
     */
    CMWWriter(holo_cmw::CMW& cmw, std::string const& topic) : cmw_(cmw)
    {
        this->pub_session_ = cmw_.AddPublisher<holo_cmw::CMW::DataPackageTopicType>(topic, 1);
    }

    /**
     * @brief Descontructor.
     */
    virtual ~CMWWriter()
    {
    }

    /**
     * @brief Write session data to message queue.
     * 
     * @param[in] session Session data.
     */
    void Write(DataPackageType const& session)
    {
        ++this->counter_;

        holo_cmw::CMW::DataPackageTopicType msg;
        holo_cmw::Convert(session, msg);
        this->pub_session_.Write(msg);

        if (this->verbose_)
        {
            LOG(INFO) << "CMWWriter::Write debug, counter=" << this->counter_ << " token_id=" << session.GetTokenId()
                      << " session_id=" << session.GetSequenceId() << " item_count=" << session.GetCount()
                      << " data_size=" << session.GetDataSize();
        }
    }

    /**
     * @brief Whether or not current writer has been exited.
     * 
     * @return Always return false, and this writer always valid.
     */
    virtual holo::bool_t IsExit() const override
    {
        return false;
    }

    /**
     * @brief Access the writer status info.
     * 
     * @return Status info with json format.
     */
    virtual std::string Status() override
    {
        std::stringstream stream;
        stream << "{\"counter\":" << this->counter_ << ", \"token_id\":" << this->token_id_ << "}";
        return stream.str();
    }
private:
    holo_cmw::CMW&                      cmw_;           ///< Message queue handle, must be initialized outside.
    holo_cmw::CMW::DataPackagePublisher pub_session_;   ///< Publisher handle.
}; ///< End of class CMWWriter.

/**
 * @}
 *
 */

} ///< namespace io
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_IO_CMW_WRITER_H_ */
