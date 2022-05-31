
#ifndef _UTILS_H
#define _UTILS_H

#include <iostream>
#include <vector>

struct FeatureMapRawData
{
    int   pad_l_, pad_r_, pad_t_, pad_b_, channel_, height_, width_, pad_width_, pad_height_, pad_fm_size_;
    int   quantscale_;
    void* buf_;
    int   data_len_;
    FeatureMapRawData()
    {
    }
    FeatureMapRawData(int pad_l, int pad_r, int pad_t, int pad_b, int channel, int height, int width, int quantscale,
                      void* buf)
    {
        pad_l_       = pad_l;
        pad_r_       = pad_r;
        pad_t_       = pad_t;
        pad_b_       = pad_b;
        channel_     = channel;
        height_      = height;
        width_       = width;
        quantscale_  = quantscale;
        buf_         = buf;
        pad_width_   = pad_l + width_ + pad_r_;
        pad_height_  = pad_t_ + height_ + pad_b_;
        pad_fm_size_ = pad_width_ * pad_height_;
        data_len_    = channel_ * pad_fm_size_;
    }
    void PrintData()
    {
        std::cout << pad_l_ << " " << pad_r_ << " " << pad_t_ << " " << pad_b_ << " " << channel_ << " " << height_
                  << " " << width_ << " " << quantscale_ << " " << buf_ << std::endl;
    }
};

struct FeatureTDA4VX_bk
{
    int   x, y;   ///< 2d point detected on image
    float score;  ///< feature score

    /**
     * @brief constructor
     * @param _image_point 2d point coordinate on image
     * @param _optional_descriptor optional descriptor
     * @param _score feature score
     ＊
     */
    FeatureTDA4VX_bk(const int _x, const int _y, const float _score = 1.0) : x(_x), y(_y), score(_score)
    {
    }
};

#endif
