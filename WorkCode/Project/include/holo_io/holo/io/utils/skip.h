/*!
 *  \brief skip object used with istream to match an expected input string.
 *  \author zhangjiannan(zhangjiannan@holomaitc.ai)
 *  \date Jul 17, 2017
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#ifndef HOLO_IO_UTILS_SKIP_H_
#define HOLO_IO_UTILS_SKIP_H_

#include <ios>
#include <iostream>

namespace holo_io
{

struct skip
{
    const char* text;
    skip(const char* text) :
        text(text)
    {
    }
};

std::istream& operator >>(std::istream& stream, const skip& x);

}

#endif
