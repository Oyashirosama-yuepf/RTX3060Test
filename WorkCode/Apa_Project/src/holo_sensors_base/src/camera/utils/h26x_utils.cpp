/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file h26x_utils.cpp.
 * @brief H26X Utils.
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2022-4-18.
 */

#include <holo/sensors/camera/utils/h26x_utils.h>
#include <cstdio>
#include <cstring>
#include <iostream>

namespace holo
{
namespace sensors
{
namespace camera
{
static constexpr uint32_t MASK               = 0xFFFFFF00;
static constexpr uint32_t SPLIT              = 0x100;
static constexpr uint8_t  HEVC_NALU_TYPE     = 0x7E;
static constexpr uint8_t  AVC_NAMU_TYPE      = 0x1F;
static constexpr uint8_t  FORBIDDEN_ZERO     = 0x81;
static constexpr uint8_t  RESERVED_ZERO      = 0xF8;
static constexpr uint8_t  H265_SPS_HEAD_FLAG = 0x42;

static constexpr uint8_t  START_BIT          = 0x03;
static constexpr uint8_t  M_ZERO             = 2;
static constexpr uint8_t  REL_VALUE          = 0x1;

static constexpr uint32_t MAX_ENCODED_DATA   = 3840 * 2160 * 2 + 256;

static constexpr uint32_t NAL_STSA_R         = 5;
static constexpr uint32_t NAL_RADL_N         = 6;
static constexpr uint32_t NAL_RADL_R         = 7;
static constexpr uint32_t NAL_BLA_W_LP       = 16;
static constexpr uint32_t NAL_BLA_W_RADL     = 17;
static constexpr uint32_t NAL_BLA_N_LP       = 18;
static constexpr uint32_t NAL_IDR_W_RADL     = 19;
static constexpr uint32_t NAL_IDR_N_LP       = 20;
static constexpr uint32_t NAL_CRA_NUT        = 21;
static constexpr uint32_t NAL_VPS            = 32;
static constexpr uint32_t NAL_SPS            = 33;
static constexpr uint32_t NAL_PPS            = 34;

static uint8_t getbyte(uint32_t* start_bit, uint8_t* m_data, uint32_t m_len, uint32_t* m_zeros)
{
    if (*start_bit >= m_len)
    {
        return 0;
    }

    uint8_t b = m_data[(*start_bit)++];
    if (b == 0)
    {
        (*m_zeros)++;
        if ((*start_bit < m_len) && ((*m_zeros) == M_ZERO) && (m_data[*start_bit] == START_BIT))
        {
            (*start_bit)++;
            (*m_zeros) = 0;
        }
    }
    else
    {
        (*m_zeros) = 0;
    }

    return b;
};

static uint32_t getbit(int* m_bits, uint8_t* m_byte, uint32_t* start_bit, uint8_t* m_data, uint32_t m_len, uint32_t* m_zeros)
{
    if (*m_bits == 0)
    {
        *m_byte = getbyte(start_bit, m_data, m_len, m_zeros);
        *m_bits = 8;
    }
    *m_bits -= 1;

    return (*m_byte >> *m_bits) & REL_VALUE;
}

static uint32_t getword(int bits, int* m_bits, uint8_t* m_byte, uint32_t* start_bit, uint8_t* m_data, uint32_t m_len, uint32_t* m_zeros)
{
    uint32_t u = 0;
    while (bits > 0)
    {
        u <<= 1;
        u |= getbit(m_bits, m_byte, start_bit, m_data, m_len, m_zeros);
        bits--;
    }

    return u;
}

static uint32_t getue(int* m_bits, uint8_t* m_byte, uint32_t* start_bit, uint8_t* m_data, uint32_t m_len, uint32_t* m_zeros)
{
    int zeros = 0;
    while (*start_bit < m_len && getbit(m_bits, m_byte, start_bit, m_data, m_len, m_zeros) == 0)
    {
        zeros++;
    }

    return getword(zeros, m_bits, m_byte, start_bit, m_data, m_len, m_zeros) + ((1 << zeros) - 1);
}

static bool find_sps_first_byte(uint8_t** buf, uint32_t* len, uint8_t type)
{
    uint8_t* pos = (uint8_t *)memchr(*buf, type, *len);
    if (nullptr == pos)
    {
        return false;
    }

    *len -= pos - *buf;
    *buf = pos;

    return true;
}

static bool adjust_resolution_by_offset(uint32_t* width, uint32_t* hight, uint8_t offset_width, uint8_t offset_hight)
{
    if (offset_width) 
    {
        if ((offset_width * 2) <= *width)
        {
            *width -= offset_width * 2;
        }
        else
        {
            return false;
        }
    }

    if (offset_hight) 
    {
        if ((offset_hight * 2) <= *hight)
        {
            *hight -= offset_hight * 2;
        }
        else
        {
            return false;
        }
    }

    return true;
}

holo::bool_t is_key_frame_h265(uint8_t* pbuf, int buf_size)
{
    unsigned int code = -1;

    for (int i = 0; i < buf_size - 1; i++)
    {
        code = (code << 8) + pbuf[i];
        if ((code & MASK) == SPLIT)
        {
            char nal  = pbuf[i + 1];
            int  type = (code & HEVC_NALU_TYPE) >> 1;

            if (code & FORBIDDEN_ZERO)
                return false;

            if (nal & RESERVED_ZERO)
                return false;

            switch (type)
            {
                case NAL_BLA_W_LP:
                case NAL_BLA_W_RADL:
                case NAL_BLA_N_LP:
                case NAL_IDR_W_RADL:
                case NAL_IDR_N_LP:
                case NAL_CRA_NUT:
                case NAL_VPS:
                case NAL_SPS:
                case NAL_PPS:
                    return true;
                    break;
                default:
                    break;
            }

            return false;
        }
    }

    return false;
}

holo::bool_t is_key_frame_h264(uint8_t* pbuf, int buf_size)
{
    unsigned int code = -1;

    for (int i = 0; i < buf_size - 1; i++)
    {
        code = (code << 8) + pbuf[i];
        if ((code & MASK) == SPLIT)
        {
            int type = code & AVC_NAMU_TYPE;

            switch (type)
            {
                case NAL_STSA_R:
                case NAL_RADL_N:
                case NAL_RADL_R:
                    return true;
                    break;
                default:
                    break;
            }

            return false;
        }
    }

    return false;
}

holo::bool_t get_h265_width_height(uint8_t* pbuf, uint32_t buf_size, uint32_t& width, uint32_t& height)
{
    uint32_t start_bit = 0;
    int      m_bits    = 0;
    uint8_t  m_byte    = 0;
    uint32_t m_zeros   = 0;
    if (!find_sps_first_byte(&pbuf, &buf_size, H265_SPS_HEAD_FLAG))
    {
        return false;
    }

    getword(1, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
    getword(6, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
    getword(6, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
    getword(3, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
    getword(4, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
    uint32_t sps_max_sub_layers_minus1 = getword(3, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
    if (sps_max_sub_layers_minus1 > 6)
    {
        return false;
    }

    getword(1, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);

    {
        getword(2, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
        getword(1, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
        getword(5, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
        getword(32, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
        getword(1, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
        getword(1, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
        getword(1, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
        getword(1, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
        getword(44, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
        getword(8, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);

        uint8_t sub_layer_profile_present_flag[6] = { 0 };
        uint8_t sub_layer_level_present_flag[6] = { 0 };
        uint32_t i;
        for (i = 0; i < sps_max_sub_layers_minus1; i++)
        {
            sub_layer_profile_present_flag[i] = getword(1, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
            sub_layer_level_present_flag[i] = getword(1, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
        }
        if (sps_max_sub_layers_minus1 > 0)
        {
            for (i = sps_max_sub_layers_minus1; i < 8; i++)
            {
                getword(2, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
            }
        }
        for (i = 0; i < sps_max_sub_layers_minus1; i++)
        {
            if (sub_layer_profile_present_flag[i])
            {
                getword(2, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
                getword(1, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
                getword(5, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
                getword(32, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
                getword(1, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
                getword(1, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
                getword(1, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
                getword(1, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
                getword(44, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
            }
            if (sub_layer_level_present_flag[i])
            {
                getword(8, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
            }
        }
    }

    uint64_t sps_seq_parameter_set_id = getue(&m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
    if (sps_seq_parameter_set_id > 15)
    {
        return false;
    }

    uint64_t chroma_format_idc = getue(&m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
    if (sps_seq_parameter_set_id > 3)
    {
        return false;
    }

    if (chroma_format_idc == 3)
    {
        getword(1, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
    }

    width = getue(&m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
    height = getue(&m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);

    if (getword(1, &m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros))
    {
        uint32_t conf_win_left_offset   = getue(&m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);
        uint32_t conf_win_right_offset  = getue(&m_bits, &m_byte, &start_bit, pbuf,buf_size, &m_zeros);
        uint32_t conf_win_top_offset    = getue(&m_bits, &m_byte, &start_bit, pbuf,buf_size, &m_zeros);
        uint32_t conf_win_bottom_offset = getue(&m_bits, &m_byte, &start_bit, pbuf, buf_size, &m_zeros);

        if (!adjust_resolution_by_offset(&width, &height, conf_win_left_offset + conf_win_right_offset, conf_win_top_offset + conf_win_bottom_offset)) 
        {
        }
    }

    return true;
}

}  // namespace camera
}  // namespace sensors
}  // namespace holo
